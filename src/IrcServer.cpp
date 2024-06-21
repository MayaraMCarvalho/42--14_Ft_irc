/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:58:55 by macarval          #+#    #+#             */
/*   Updated: 2024/06/21 09:08:10 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/IrcServer.hpp"
#include "../include/Channel.hpp"
#include "../include/Commands.hpp"

// Constructor & Destructor ===================================================
IRCServer::IRCServer(void) {}

IRCServer::~IRCServer(void) {}

IRCServer::IRCServer(const std::string &port, const std::string &password)
	: _port(port), _password(password), _serverFd(-1), _bot("ChatBot"),
	_clients(), _channels(&_clients) {}

// Getters ====================================================================

// Setters ====================================================================

// Methods ====================================================================

void IRCServer::setupServer(void)
{
	int	opt;

	_serverFd = socket(AF_INET, SOCK_STREAM, 0);

	if (_serverFd < 0)
		throw std::runtime_error("Failed to create socket");

	opt = 1;
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("Failed to set socket options");

	struct sockaddr_in address;
	std::memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(std::atoi(_port.c_str()));

	if (bind(_serverFd, (struct sockaddr *)&address, sizeof(address)) < 0)
		throw std::runtime_error("Failed to bind socket");
	if (listen(_serverFd, 10) < 0)
		throw std::runtime_error("Failed to listen on socket");

	fcntl(_serverFd, F_SETFL, O_NONBLOCK);
	struct pollfd pfd = {_serverFd, POLLIN, STDIN_FILENO};
	_pollFds.push_back(pfd);
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
	int	pollCount;

	setupServer();
	setupSignalHandlers();
	std::cout << GREEN << "Server running on port ";
	std::cout << BYELLOW << _port << RESET << std::endl;

	while (true)
	{
		pollCount = poll(_pollFds.data(), _pollFds.size(), -1);
		if (pollCount < 0)
			throw std::runtime_error("Poll error");

		if (_pollFds[0].revents & POLLIN)
			acceptNewClient();

		for (size_t i = 1; i < _pollFds.size(); ++i)
		{
			if (_pollFds[i].revents & POLLIN)
				handleClientMessage(_pollFds[i].fd);
		}
	}
}

void IRCServer::acceptNewClient(void)
{
	int	clientFd;

	struct sockaddr_in clientAddress;
	socklen_t clientLen = sizeof(clientAddress);
	clientFd = accept(_serverFd, (struct sockaddr *)&clientAddress, &clientLen);

	if (clientFd < 0)
	{
		if (errno != EWOULDBLOCK)
			std::cerr << "Failed to accept new client" << std::endl;
		return;
	}

	fcntl(clientFd, F_SETFL, O_NONBLOCK);


	_clients.add(clientFd, &clientAddress.sin_addr);

	_channels.join(clientFd, "default");
	struct pollfd pfd = {clientFd, POLLIN, 0};
	_pollFds.push_back(pfd);

	std::cout << BLUE << "New client connected: ";
	std::cout << BYELLOW << clientFd << RESET << std::endl;

	std::map<int, Client>::iterator it = _clients.getClient(clientFd);
	std::string message = BPURPLE + "-------------------------------\n" +
		"------ Welcome to ft_IRC ------\n" +
		"-------------------------------\n" + RESET;
	it->second.sendMessage(message);
}

void IRCServer::handleClientMessage(int clientFd)
{
	char	buffer[512];
	ssize_t	nbytes;

	std::memset(buffer, 0, sizeof(buffer));
	nbytes = read(clientFd, buffer, sizeof(buffer) - 1); // read client data

	if (nbytes <= 0)
	{
		std::cout << RED;
		if (nbytes < 0 && errno != EWOULDBLOCK)
			std::cerr << "Read error on client " << clientFd << std::endl;
		else if (nbytes == 0)
			std::cout << "Client disconnected: " << BYELLOW << clientFd << std::endl;
		std::cout << RESET;
		removeClient(clientFd);
		return;
	}

	buffer[nbytes] = '\0';
	std::string message(buffer);

	//
	if (!message.empty() && message[message.length() - 1] == '\n')
		message.erase(message.length() - 1);
	//

	std::cout << CYAN;
	std::cout << "Received message from client " << clientFd;
	std::cout << ": " << BYELLOW << message << RESET << std::endl;

	//
	//
	//
	Commands commands(this->_clients, this->_channels, clientFd);
	bool isCommand = false;
	if (!message.empty() && commands.isCommand(message))
	{
		isCommand = true;
	}
	//
	else if (message.substr(0, 5) == "/file")
		handleFileTransfer(clientFd, message);
	else
		_bot.respondToMessage(clientFd, message); // call for the bot to respond

	std::map<std::string, Channel>::iterator it = _channels.get("default");

	if (!isCommand)
	{
		if (it != _channels.end())
			it->second.sendToAll(message);
		else
			std::cerr << "Failed to send message to channel default" << std::endl;
	}
}

void IRCServer::removeClient(int clientFd)
{
	close(clientFd);

	_channels.partDisconnectedClient(clientFd);

	for (std::vector<struct pollfd>::iterator it = _pollFds.begin(); it != _pollFds.end(); ++it)
	{
		if (it->fd == clientFd)
		{
			_pollFds.erase(it);
			break;
		}
	}

	_clients.remove(clientFd);
}

void IRCServer::sendMessage(int clientFd, const std::string &message)
{
	ssize_t	nbytes;

	std::string fullMessage = message + "\n";
	nbytes = write(clientFd, fullMessage.c_str(), fullMessage.length());
	if (nbytes < 0)
	{
		std::cerr << RED << "Write error on client " << clientFd << std::endl;
		std::cout << RESET;
	}
}

void IRCServer::handleFileTransfer(int clientFd, const std::string &command)
{
	std::istringstream	iss(command);
	std::string			cmd, fileName;
	int					receiverFd;

	iss >> cmd >> receiverFd >> fileName;
	_fileTransfer.requestTransfer(clientFd, receiverFd, fileName); // starts file transfer
}

// Exceptions =================================================================
