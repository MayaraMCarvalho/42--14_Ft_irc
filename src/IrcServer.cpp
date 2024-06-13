/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:58:55 by macarval          #+#    #+#             */
/*   Updated: 2024/06/12 16:07:41 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/IrcServer.hpp"
#include "../include/Channel.hpp"

// Constructor & Destructor ===================================================
IRCServer::IRCServer(void) {}

IRCServer::~IRCServer(void) {}

// Getters ====================================================================

// Setters ====================================================================

// Methods ====================================================================
IRCServer::IRCServer(const std::string &port, const std::string &password)
	: _port(port), _password(password), _server_fd(-1), _bot("ChatBot") {}

void IRCServer::setup_server(void)
{
	// struct	pollfd pfd;
	int	opt;

	_server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (_server_fd < 0)
		throw std::runtime_error("Failed to create socket");

	opt = 1;
	if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("Failed to set socket options");

	struct sockaddr_in address;
	std::memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(std::atoi(_port.c_str()));

	if (bind(_server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		throw std::runtime_error("Failed to bind socket");
	if (listen(_server_fd, 10) < 0)
		throw std::runtime_error("Failed to listen on socket");

	fcntl(_server_fd, F_SETFL, O_NONBLOCK);

	// std::memset(pdf, 0, sizeof(pdf));
	// pdf.fd = _server_fd;
	// pdf.events = POLLIN;
	struct pollfd pfd = {_server_fd, POLLIN, STDIN_FILENO};
	_poll_fds.push_back(pfd);
}

void IRCServer::signalHandler(int signal)
{
	if (signal == SIGINT || signal == SIGTERM || signal == SIGTSTP)
	{
		std::cout << "\nExiting gracefully." << std::endl;
		exit(EXIT_SUCCESS);
	}
}

void IRCServer::setupSignalHandlers(void)
{
	struct sigaction action;
	std::memset(&action, 0, sizeof(action));
	action.sa_handler = signalHandler;

	if (sigaction(SIGINT, &action, NULL) == -1 ||
		sigaction(SIGTERM, &action, NULL) == -1 ||
		sigaction(SIGTSTP, &action, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void IRCServer::run(void)
{
	int	poll_count;

	setup_server();
	setupSignalHandlers();
	std::cout << "Server running on port " << _port << std::endl;

	while (true)
	{
		poll_count = poll(_poll_fds.data(), _poll_fds.size(), -1);
		if (poll_count < 0)
			throw std::runtime_error("Poll error");

		for (size_t i = 0; i < _poll_fds.size(); ++i)
		{
			if (_poll_fds[i].revents & POLLIN)
			{
				if (_poll_fds[i].fd == _server_fd)
					acceptNewClient();
				else
					handleClientMessage(_poll_fds[i].fd);
			}
		}
	}
}

void IRCServer::acceptNewClient(void)
{
	int	client_fd;

	struct sockaddr_in client_address;
	socklen_t client_len = sizeof(client_address);
	client_fd = accept(_server_fd, (struct sockaddr *)&client_address, &client_len);

	if (client_fd < 0)
	{
		if (errno != EWOULDBLOCK)
			std::cerr << "Failed to accept new client" << std::endl;
		return;
	}

	fcntl(client_fd, F_SETFL, O_NONBLOCK);

	_clients[client_fd] = Client(client_fd);
	struct pollfd pfd = {client_fd, POLLIN, 0};
	_poll_fds.push_back(pfd);

	std::cout << "New client connected: " << client_fd << std::endl;
}

void IRCServer::handleClientMessage(int client_fd)
{
	char	buffer[512];
	ssize_t	nbytes;

	std::memset(buffer, 0, sizeof(buffer));
	nbytes = read(client_fd, buffer, sizeof(buffer) - 1); // read client data

	if (nbytes <= 0)
	{
		if (nbytes < 0 && errno != EWOULDBLOCK)
			std::cerr << "Read error on client " << client_fd << std::endl;
		else if (nbytes == 0)
			std::cout << "Client disconnected: " << client_fd << std::endl;
		remove_client(client_fd);
		return;
	}

	buffer[nbytes] = '\0';
	std::string message(buffer);
	std::cout << "Received message from client " << client_fd << ": " << message << std::endl;
	// Channel channel;
	if (message.substr(0, 5) == "/file")
		handle_file_transfer(client_fd, message);
	else
		_bot.respond_to_message(client_fd, message); // call for the bot to respond
	// channel.send_to_all(message);
	//  send_message(client_fd, message);
	if (_channels.find("default") != _channels.end())
		_channels["default"].send_to_all(this, message);
}

void IRCServer::remove_client(int client_fd)
{
	close(client_fd);
	_clients.erase(client_fd);

	for (std::vector<struct pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); ++it)
	{
		if (it->fd == client_fd)
		{
			_poll_fds.erase(it);
			break;
		}
	}

	std::map<std::string, Channel>::iterator it;

	for (it = _channels.begin(); it != _channels.end(); ++it)
		it->second.remove_client(client_fd);
}

void IRCServer::send_message(int client_fd, const std::string &message)
{
	ssize_t	nbytes;

	std::string full_message = message + "\n";
	nbytes = write(client_fd, full_message.c_str(), full_message.length());
	if (nbytes < 0)
		std::cerr << "Write error on client " << client_fd << std::endl;
}

void IRCServer::handle_file_transfer(int client_fd, const std::string &command)
{
	std::istringstream	iss(command);
	std::string			cmd, file_name;
	int					receiver_fd;

	iss >> cmd >> receiver_fd >> file_name;
	_file_transfer.request_transfer(client_fd, receiver_fd, file_name); // inicia a transferencia do arquivo
}

// Exceptions =================================================================
