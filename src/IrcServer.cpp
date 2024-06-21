/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:58:55 by macarval          #+#    #+#             */
/*   Updated: 2024/06/20 20:45:01 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/IrcServer.hpp"
#include "../include/Channel.hpp"
#include "../include/Commands.hpp"

// Constructor & Destructor ===================================================
IRCServer::IRCServer(void) {}

IRCServer::~IRCServer(void) {}

IRCServer::IRCServer(const std::string &port, const std::string &password)
	: _port(port), _password(password), _server_fd(-1), _bot("ChatBot"),
	_clients(), _channels(&_clients) {}

// Getters ====================================================================

// Setters ====================================================================

// Methods ====================================================================

void IRCServer::setupServer(void)
{
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

	setupServer();
	setupSignalHandlers();
	std::cout << GREEN << "Server running on port ";
	std::cout << BYELLOW << _port << RESET << std::endl;

	while (true)
	{
		poll_count = poll(_poll_fds.data(), _poll_fds.size(), -1);
		if (poll_count < 0)
			throw std::runtime_error("Poll error");

		if (_poll_fds[0].revents & POLLIN)
			acceptNewClient();

		for (size_t i = 1; i < _poll_fds.size(); ++i)
		{
			if (_poll_fds[i].revents & POLLIN)
				handleClientMessage(_poll_fds[i].fd);
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


	_clients.add(client_fd, &client_address.sin_addr);

	_channels.join(client_fd, "default");
	struct pollfd pfd = {client_fd, POLLIN, 0};
	_poll_fds.push_back(pfd);

	std::cout << BLUE << "New client connected: ";
	std::cout << BYELLOW << client_fd << RESET << std::endl;

	std::map<int, Client>::iterator it = _clients.getClient(client_fd);
	std::string message = BPURPLE + "-------------------------------\n" +
		"------ Welcome to ft_IRC ------\n" +
		"-------------------------------\n" + RESET;
	it->second.sendMessage(message);
}

void IRCServer::handleClientMessage(int client_fd)
{
	char	buffer[512];
	ssize_t	nbytes;

	std::memset(buffer, 0, sizeof(buffer));
	nbytes = read(client_fd, buffer, sizeof(buffer) - 1); // read client data

	if (nbytes <= 0)
	{
		std::cout << RED;
		if (nbytes < 0 && errno != EWOULDBLOCK)
			std::cerr << "Read error on client " << client_fd << std::endl;
		else if (nbytes == 0)
			std::cout << "Client disconnected: " << BYELLOW << client_fd << std::endl;
		std::cout << RESET;
		removeClient(client_fd);
		return;
	}

	buffer[nbytes] = '\0';
	std::string message(buffer);

	//
	if (!message.empty() && message[message.length() - 1] == '\n')
		message.erase(message.length() - 1);
	//

	std::cout << CYAN;
	std::cout << "Received message from client " << client_fd;
	std::cout << ": " << BYELLOW << message << RESET << std::endl;

	//
	//
	//
	Commands commands(this->_clients, this->_channels, client_fd);
	bool isCommand = false;
	if (!message.empty() && commands.isCommand(message))
	{
		isCommand = true;
	}
	//
	else if (message.substr(0, 5) == "/file")
		handleFileTransfer(client_fd, message);
	else
		_bot.respondToMessage(client_fd, message); // call for the bot to respond

	std::map<std::string, Channel>::iterator it = _channels.get("default");

	if (!isCommand)
	{
		if (it != _channels.end())
			it->second.sendToAll(message);
		else
			std::cerr << "Failed to send message to channel default" << std::endl;
	}
}

void IRCServer::removeClient(int client_fd)
{
	close(client_fd);

	_channels.partDisconnectedClient(client_fd);

	for (std::vector<struct pollfd>::iterator it = _poll_fds.begin(); it != _poll_fds.end(); ++it)
	{
		if (it->fd == client_fd)
		{
			_poll_fds.erase(it);
			break;
		}
	}

	_clients.remove(client_fd);
}

void IRCServer::sendMessage(int client_fd, const std::string &message)
{
	ssize_t	nbytes;

	std::string full_message = message + "\n";
	nbytes = write(client_fd, full_message.c_str(), full_message.length());
	if (nbytes < 0)
	{
		std::cerr << RED << "Write error on client " << client_fd << std::endl;
		std::cout << RESET;
	}
}

void IRCServer::handleFileTransfer(int client_fd, const std::string &command)
{
	std::istringstream	iss(command);
	std::string			cmd, file_name;
	int					receiver_fd;

	iss >> cmd >> receiver_fd >> file_name;
	_file_transfer.requestTransfer(client_fd, receiver_fd, file_name); // starts file transfer
}

// Exceptions =================================================================
