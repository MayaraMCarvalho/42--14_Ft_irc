/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:58:55 by macarval          #+#    #+#             */
/*   Updated: 2024/07/10 06:03:57 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrcServer.hpp"
#include "Commands.hpp"
#include <cerrno>
#include <cstdio>
#include <sys/types.h>
#include <netdb.h>

IRCServer* IRCServer::_instance = NULL;

// Constructor & Destructor ===================================================
IRCServer::~IRCServer(void) {}

IRCServer::IRCServer(const std::string &port, const std::string &password)
	: _port(port), _password(password), _serverFd(-1), _bot("ChatBot"),
	_msgHandler(), _clients(_msgHandler, _pollFds), _channels(_clients,
	_msgHandler), _shouldExit(false)
{
	_instance = this;
}

// Getters ====================================================================
ClientList& IRCServer::getClients( void ) { return _clients; }

ChannelList& IRCServer::getChannels( void ) { return _channels; }

const std::string& IRCServer::getPassword( void ) { return _password; }

// Setters ====================================================================

// Methods ====================================================================

void IRCServer::setupServer(void)
{
	struct sockaddr_in address;
	int	opt;

	std::memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(std::atoi(_port.c_str()));

	_serverFd = socket(AF_INET, SOCK_STREAM, 0);

	if (_serverFd < 0)
		throw std::runtime_error("Failed to create socket");

	opt = 1;
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("Failed to set socket options");

	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Unable to set non-blocking mode on client file descriptor (fcntl)");
	if (bind(_serverFd, (struct sockaddr *)&address, sizeof(address)) < 0)
		throw std::runtime_error("Failed to bind socket");

	if (listen(_serverFd, 10) < 0)
		throw std::runtime_error("Failed to listen on socket");

	struct pollfd pfd = {_serverFd, POLLIN | POLLOUT, STDIN_FILENO};
	_pollFds.push_back(pfd);
}

void IRCServer::signalHandler(int signal)
{
	if (signal == SIGINT || signal == SIGTERM || signal == SIGTSTP)
	{
		ChannelList	channels = _instance->_channels;
		ClientList	clients = _instance->_clients;
		_instance->_shouldExit = true;

		for (std::map<int, Client>::iterator it = clients.begin();
			it != clients.end(); ++it)
			it->second.sendMessage(BRED + "The server was disconnected!" + RESET);
		std::cout << BGREEN << std::endl;
		std::cout << "Exiting gracefully!" << RESET << std::endl;
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

	while (!_shouldExit)
	{
		sigset_t		pendingSignals;

		if (sigpending(&pendingSignals) == 0)
		{
			if (sigismember(&pendingSignals, SIGINT)
			|| sigismember(&pendingSignals, SIGTERM)
			|| sigismember(&pendingSignals, SIGTSTP))
				break;
		}

		pollCount = poll(_pollFds.data(), _pollFds.size(), 0);
		if (pollCount < 0)
		{
			if (errno == EINTR)
				continue;
			else
				throw std::runtime_error("Poll error");
		}


		if (_pollFds[0].revents & POLLIN)
			acceptNewClient();

		for (size_t fdIdx = 1; fdIdx < _pollFds.size();) {
			int fd = _pollFds[fdIdx].fd;
			if (_pollFds[fdIdx].revents & POLLIN &&
					!handleClientMessage(_pollFds[fdIdx].fd)) {
				disconnectClient(fd, fdIdx);
				continue;
			}

			if (_pollFds[fdIdx].revents & POLLOUT) {
				ssize_t strLen = _msgHandler.sendLength(fd);

				if (strLen > 0) {
					try {
						ssize_t	nbytes = send(fd,
							_msgHandler.sendPop(fd).c_str(),strLen, 0);

						if (nbytes <= 0) {
							std::cerr << RED << "Write error on client "
								<< BYELLOW << fd << std::endl << RESET;
							disconnectClient(fd, fdIdx);
							continue;
						}
						_msgHandler.removeSendChars(fd, nbytes);
					} catch (std::out_of_range &e) {
						std::cerr << RED
						<< "Out of range exception caught while processing "
						<< "message queue" << RESET << std::endl;
					}
				}
			}
			++fdIdx;
		}
	}
}

void IRCServer::acceptNewClient(void)
{
	int	clientFd;
	struct sockaddr_in clientAddress;
	socklen_t clientLen = sizeof(clientAddress);
	clientFd = accept(_serverFd, (struct sockaddr *)&clientAddress, &clientLen);

	if (clientFd < 0) {
		std::cerr << "Failed to accept new client" << std::endl;
		return;
	}

	if (fcntl(clientFd, F_SETFL, O_NONBLOCK)) {
		throw std::runtime_error("Unable to set non-blocking mode on client file descriptor (fcntl)");
	}

	_clients.add(clientFd);
	struct pollfd pfd = {clientFd, POLLIN | POLLOUT, 0};
	_pollFds.push_back(pfd);

	std::cout << BLUE << "New client connected: ";
	std::cout << BYELLOW << clientFd << RESET << std::endl;

	std::map<int, Client>::iterator it = _clients.getClient(clientFd);
	std::string message = BPURPLE +
		"NOTICE * :*** Welcome to the IRC server ***" + RESET;
	it->second.sendMessage(message);
}

bool IRCServer::handleClientMessage(int clientFd)
{
	char	buffer[MAX_MSG_LENGTH + 1];
	ssize_t	nbytes;

	std::memset(buffer, 0, sizeof(buffer));
	nbytes = recv(clientFd, buffer, sizeof(buffer) - 1, 0); // read client data

	if (nbytes < 0) {
		std::cerr << RED << "Read error on client: " << BYELLOW << clientFd
			<< RESET << std::endl;
		return false;
	}
	else if (nbytes == 0) {
		std::cerr << "Client disconnected: " << BYELLOW << clientFd
			<< RESET << std::endl;
		return false;
	}

	buffer[nbytes] = '\0';
	std::cout << CYAN;
	std::cout << "Received message from client " << clientFd;
	std::cout << ": " << BYELLOW << buffer << RESET << std::endl;

	if (!_msgHandler.recvPush(clientFd, buffer))
	{
		std::cerr << "Receive message queue is full" << RESET << std::endl;
		return false;
	}

	Commands	commands(*this);

	return commands.extractCommands(clientFd);
}

void IRCServer::handleFileTransfer(int clientFd, const std::string &command)
{
	std::istringstream	iss(command);
	std::string			cmd, file_name;
	int					receiver_fd;

	iss >> cmd >> receiver_fd >> file_name;
	_fileTransfer.requestTransfer(clientFd, receiver_fd, file_name); // starts file transfer
}

std::string IRCServer::getHostName(const char *ip, const char *port) {
	struct addrinfo *addrInfo;
	std::string hostName;

	if (getaddrinfo(ip, port, NULL, &addrInfo))
		return ip;

	hostName = addrInfo->ai_canonname;
	freeaddrinfo(addrInfo);
	return hostName;
}

void IRCServer::disconnectClient(int fd) {
	size_t fdIdx;

	for (fdIdx = 1; fdIdx < _pollFds.size(); ++fdIdx) {

		if (fd == _pollFds[fdIdx].fd) {
			break;
		}
	}
	disconnectClient(fd, _pollFds[fdIdx].fd);
}

void IRCServer::disconnectClient(int fd, size_t fdIdx) {
	_clients.removeClientFD(fd);
	_channels.partDisconnectedClient(fd);
	_pollFds.erase(_pollFds.begin() + fdIdx);
	close(fd);
}

void IRCServer::handleClientSideDisconnect(int fd) {
	disconnectClient(fd);
}

MsgHandler &IRCServer::getMsgHandler(void) { return _msgHandler; }

// Exceptions =================================================================
