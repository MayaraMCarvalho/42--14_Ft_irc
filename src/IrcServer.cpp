/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:58:55 by macarval          #+#    #+#             */
/*   Updated: 2024/06/25 03:34:37 by gmachado         ###   ########.fr       */
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
		exit(EXIT_SUCCESS); // <-memory leak
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
	std::cout << "Server running on port " << _port << std::endl;

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
	client_fd = accept(_server_fd, (struct sockaddr *)&client_address,
		&client_len);

	if (client_fd < 0)
	{
		if (errno != EWOULDBLOCK)
			std::cerr << "Failed to accept new client" << std::endl;
		return;
	}

	fcntl(client_fd, F_SETFL, O_NONBLOCK);
	_clients.add(client_fd, &client_address.sin_addr);

	_channels.join(client_fd, "default", "");
	struct pollfd pfd = {client_fd, POLLIN, 0};
	_poll_fds.push_back(pfd);

	std::cout << "New client connected: " << client_fd << std::endl;
}

t_numCode IRCServer::authenticate(int userFD, std::string password) {
	std::map<int, Client>::iterator userIt = _clients.getClient(userFD);

	if (userIt == _clients.end())
		throw std::invalid_argument("Unknown user");

	Client::t_status status = userIt->second.getStatus();

	if (status == Client::DISCONNECTED || status == Client::UNKNOWN)
		throw std::invalid_argument("Invalid user status");

	if (status != Client::CONNECTED)
		throw std::invalid_argument("Already authenticated");

	if (password != _password)
		return ERR_PASSWDMISMATCH;

	userIt->second.setStatus(Client::AUTHENTICATED);
	return NO_CODE;
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
		removeClient(client_fd);
		return;
	}

	buffer[nbytes] = '\0';
	std::string message(buffer);
	std::cout << "Received message from client " << client_fd << ": " << message << std::endl;


	//
	Commands commands;
	if (commands.isCommand(message))
	{
		std::cout << PURPLE << "this command\n" << RESET << std::endl;//deletar
	}

	//
	else if (message.substr(0, 5) == "/file")
		handleFileTransfer(client_fd, message);
	else
		_bot.respondToMessage(client_fd, message); // call for the bot to respond

	std::map<std::string, Channel>::iterator it = _channels.get("default");

	if (it != _channels.end())
		sendToChannel(it->second.getName(), message);
	else
		std::cerr << "Failed to send message to channel default" << std::endl;
}

void IRCServer::removeClient(int client_fd)
{
	close(client_fd);

	_channels.partDisconnectedClient(client_fd);

	for (std::vector<struct pollfd>::iterator it = _poll_fds.begin();
		it != _poll_fds.end(); ++it)
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
		std::cerr << "Write error on client " << client_fd << std::endl;
}

void IRCServer::sendToChannel(const std::string &chanStr,
						const std::string &message)
{
	std::map<std::string, Channel>::iterator chanIt = _channels.get(chanStr);

	// TODO: Add exception
	if (chanIt == _channels.end())
		return;

	for (std::map<int, int>::iterator it = chanIt->second.usersBegin();
		it != chanIt->second.usersEnd(); ++it)
	{
		std::cerr << "Sending message " << message << " to "
			<< it->first << std::endl;
		sendMessage(it->first, message);
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
