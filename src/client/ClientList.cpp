/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientList.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:46:41 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/02 04:05:10 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
# include <stdexcept>
#include <unistd.h>
#include "ClientList.hpp"

ClientList::ClientList(MsgHandler &msgHandler,
	std::vector<struct pollfd> &pollFds) : _msgHandler(msgHandler),
	_pollFds(pollFds), _clients(), _userToClient(), _nickToClient() { }

ClientList::ClientList(ClientList &src) : _msgHandler(src._msgHandler),
	_pollFds(src._pollFds), _clients(src._clients),
	_userToClient(src._userToClient), _nickToClient(src._nickToClient) { }

ClientList::~ClientList(void) { }

ClientList &ClientList::operator=(ClientList &src) {
	if (this == &src)
		return *this;

	_clients = src._clients;
	_userToClient = src._userToClient;
	_nickToClient = src._nickToClient;

	return *this;
}

// Getters
std::map<int, Client>::iterator ClientList::getClient(int fd) {
	return _clients.find(fd);
}
std::map<int, Client>::iterator ClientList::getClientByNick(const std::string &nick) {
	std::map<std::string, std::map<int, Client>::iterator>::iterator it;

	it = _nickToClient.find(nick);

	if (it == _nickToClient.end())
		return _clients.end();

	return it->second;
}

std::map<int, Client>::iterator ClientList::getClientByUser(const std::string &user) {
	std::map<std::string, std::map<int, Client>::iterator>::iterator it;

	it = _userToClient.find(user);

	if (it == _userToClient.end())
		return _clients.end();

	return it->second;
}

const std::string ClientList::getNick(int fd) {
	std::map<int, Client>::iterator it = getClient(fd);

	if (it == end())
		return "";

	return it->second.getNick();
}

const std::string ClientList::getUser(int fd) {
	std::map<int, Client>::iterator it = getClient(fd);

	if (it == end())
		return "";

	return it->second.getUser();
}

int ClientList::getFDByNick(const std::string &nick) {
	std::map<int, Client>::iterator it = getClientByNick(nick);

	if (it == end())
		return -1;

	return it->second.getFD();
}

int ClientList::getFDByUser(const std::string &user) {
	std::map<int, Client>::iterator it = getClientByUser(user);

	if (it == end())
		return -1;

	return it->second.getFD();
}

std::map<int, Client>::iterator ClientList::end(void) { return _clients.end(); }

// Setters
t_numCode ClientList::setNick(int fd, const std::string &newNick) {

	if (newNick.empty())
		return ERR_NONICKNAMEGIVEN;

	if (!isValidNick(newNick))
		return ERR_ERRONEUSNICKNAME;

	std::map<int, Client>::iterator it = getClient(fd);

	if (it == end())
		throw std::invalid_argument("Unknown user");

	it->second.setNick(newNick);

	Client::t_status status = it->second.getStatus();

	if (status == Client::DISCONNECTED || status == Client::UNKNOWN)
		throw std::invalid_argument("Invalid user status");

	if (status == Client::CONNECTED)
		throw std::invalid_argument("User must be authenticated first");

	if (_nickToClient.find(newNick) != _nickToClient.end())
		return ERR_NICKNAMEINUSE;

	else if (status == Client::AUTHENTICATED)
		it->second.setStatus(Client::GOT_NICK);

	else if (status == Client::GOT_USER)
		it->second.setStatus(Client::REGISTERED);

	if (!it->second.getNick().empty())
		_nickToClient.erase(it->second.getNick());

	_nickToClient.insert(std::pair<std::string,
		std::map<int, Client>::iterator>(newNick, it));
	return NO_CODE;
}

t_numCode ClientList::setUser(int fd, const std::string &newUser) {

	if (newUser.empty())
		return ERR_NEEDMOREPARAMS;

	if (!isValidUser(newUser))
		throw std::invalid_argument("Invalid user format");

	std::map<int, Client>::iterator it = getClient(fd);

	if (it == end())
		throw std::invalid_argument("Unknown user");

	it->second.setUser(newUser);

	Client::t_status status = it->second.getStatus();

	if (status == Client::DISCONNECTED || status == Client::UNKNOWN)
		throw std::invalid_argument("Invalid user status");

	if (status == Client::CONNECTED)
		throw std::invalid_argument("User must be authenticated first");

	if (status == Client::REGISTERED)
		return ERR_ALREADYREGISTERED;

	else if (status == Client::AUTHENTICATED)
		it->second.setStatus(Client::GOT_USER);

	else if (status == Client::GOT_NICK)
		it->second.setStatus(Client::REGISTERED);

	if (!it->second.getUser().empty())
		_userToClient.erase(it->second.getUser());

	_userToClient.insert(std::pair<std::string,
		std::map<int, Client>::iterator>(newUser, it));
	return NO_CODE;
}

void ClientList::add(Client &client) {
	std::pair<std::map<int, Client>::iterator, bool> result;
	bool nickNotEmpty = !client.getNick().empty();
	bool userNotEmpty = !client.getUser().empty();

	if (nickNotEmpty)
	{
		std::map<int, Client>::iterator nickIt =
			getClientByNick(client.getNick());

		// TODO: add exception
		if (nickIt != end())
			return;
	}

	if (userNotEmpty)
	{
		std::map<int, Client>::iterator userIt =
			getClientByUser(client.getUser());

		// TODO: add exception
		if (userIt != end())
			return;
	}

	result =
		_clients.insert(std::pair<int, Client>(client.getFD(), client));

	// TODO: add exception
	if (!result.second)
		return;

	if (nickNotEmpty)
	{
		_nickToClient.insert(std::pair<std::string,
			std::map<int, Client>::iterator>(client.getNick(), result.first));
	}

	if (userNotEmpty)
	{
		_userToClient.insert(std::pair<std::string,
			std::map<int, Client>::iterator>(client.getUser(), result.first));
	}
}

void ClientList::add(int fd) {
	std::string hostname = _msgHandler.getHost();


	add(fd, hostname);
}

void ClientList::add(int fd, const std::string &host) {
	Client newClient(fd, _msgHandler);

	newClient.setHost(host);
	add(newClient);
}

void ClientList::remove(int fd) {
	std::map<int, Client>::iterator fdIt = getClient(fd);

	if (fdIt == end())
		return;

	_nickToClient.erase(fdIt->second.getNick());
	_userToClient.erase(fdIt->second.getUser());
	_clients.erase(fdIt);
}

void ClientList::removeByNick(const std::string &nick) {
	std::map<int, Client>::iterator fdIt = getClientByNick(nick);

	if (fdIt == end())
		return;

	_nickToClient.erase(fdIt->second.getNick());
	_userToClient.erase(fdIt->second.getUser());
	_clients.erase(fdIt);
}

void ClientList::removeByUser(const std::string &user) {
	std::map<int, Client>::iterator fdIt = getClientByUser(user);

	if (fdIt == end())
		return;

	_nickToClient.erase(fdIt->second.getNick());
	_userToClient.erase(fdIt->second.getUser());
	_clients.erase(fdIt);
}

void ClientList::removeClientFD(int clientFd)
{
	close(clientFd);

	for (std::vector<struct pollfd>::iterator it = _pollFds.begin();
		it != _pollFds.end(); ++it)
	{
		if (it->fd == clientFd)
		{
			_pollFds.erase(it);
			break;
		}
	}

	remove(clientFd);
}


bool ClientList::isValidNick(const std::string &nick) {
	if (nick.empty() || nick.length() > 9)
		return false;

	std::string::const_iterator charIt = nick.begin();

	if (!(std::isalpha(*charIt) || isSpecialChar(*charIt)))
		return false;

	for(++charIt; charIt != nick.end(); ++charIt)
	{
		if (!(std::isalnum(*charIt) || isSpecialChar(*charIt) || *charIt == '-'))
			return false;
	}

	return true;
}

bool ClientList::isValidUser(const std::string &user) {
	if (user.empty())
		return false;

	std::string::const_iterator charIt = user.begin();

	for(; charIt != user.end(); ++charIt)
	{
		if (!((*charIt >= 0x01 && *charIt <= 0x09)
			|| (*charIt >= 0x0B && *charIt <= 0x0C)
			|| (*charIt >= 0x0E && *charIt <= 0x1F)
			|| (*charIt >= 0x21 && *charIt <= 0x3F)
			|| (*charIt >= 0x41)))
			return false;
	}

	return true;
}

bool ClientList::isSpecialChar(char ch) {
	return (ch >= 0x5B && ch <= 0x60) || (ch >= 0x7B && ch <= 0x7D);
}
