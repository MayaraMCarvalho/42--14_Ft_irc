/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientList.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:46:41 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/15 05:59:28 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientList.hpp"

ClientList::ClientList(void) : _clients(), _userToClient(), _nickToClient() { }

ClientList::ClientList(ClientList &src) : _clients(src._clients),
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
std::map<int, Client>::iterator ClientList::getClientByNick(std::string nick) {
	std::map<std::string, std::map<int, Client>::iterator>::iterator it;

	it = _nickToClient.find(nick);

	if (it == _nickToClient.end())
		return _clients.end();

	return it->second;
}

std::map<int, Client>::iterator ClientList::getClientByUser(std::string user) {
	std::map<std::string, std::map<int, Client>::iterator>::iterator it;

	it = _userToClient.find(user);

	if (it == _userToClient.end())
		return _clients.end();

	return it->second;
}

std::string ClientList::getNick(int fd) {
	std::map<int, Client>::iterator it = getClient(fd);

	if (it == end())
		return "";

	return it->second.getNick();
}

std::string ClientList::getUser(int fd) {
	std::map<int, Client>::iterator it = getClient(fd);

	if (it == end())
		return "";

	return it->second.getUser();
}

int ClientList::getFDByNick(std::string nick) {
	std::map<int, Client>::iterator it = getClientByNick(nick);

	if (it == end())
		return -1;

	return it->second.getFD();
}

int ClientList::getFDByUser(std::string user) {
	std::map<int, Client>::iterator it = getClientByUser(user);

	if (it == end())
		return -1;

	return it->second.getFD();
}

std::map<int, Client>::iterator ClientList::end(void) { return _clients.end(); }

// Setters
void ClientList::setNick(int fd, std::string nick) {
	std::map<int, Client>::iterator it = getClient(fd);

	if (it == end())
		return;

	it->second.setNick(nick);
}

void ClientList::setUser(int fd, std::string user) {
	std::map<int, Client>::iterator it = getClient(fd);

	if (it == end())
		return;

	it->second.setUser(user);
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

void ClientList::add(int fd, std::string host) {
	Client newClient(fd);

	newClient.setHost(host);
	add(newClient);
}

void ClientList::remove(int fd) {
	std::map<int, Client>::iterator fdIt = getClient(fd);

	if (fdIt == end())
		return;

	_clients.erase(fdIt);
	_nickToClient.erase(fdIt->second.getNick());
	_userToClient.erase(fdIt->second.getUser());
}

void ClientList::removeByNick(std::string nick) {
	std::map<int, Client>::iterator fdIt = getClientByNick(nick);

	if (fdIt == end())
		return;

	_clients.erase(fdIt);
	_nickToClient.erase(fdIt->second.getNick());
	_userToClient.erase(fdIt->second.getUser());
}
void ClientList::removeByUser(std::string user) {
	std::map<int, Client>::iterator fdIt = getClientByUser(user);

	if (fdIt == end())
		return;

	_clients.erase(fdIt);
	_nickToClient.erase(fdIt->second.getNick());
	_userToClient.erase(fdIt->second.getUser());
}

void ClientList::updateNick(int fd, std::string newNick) {
	std::map<int, Client>::iterator it = getClient(fd);

	if (it == end())
		return;

	if (!it->second.getNick().empty())
		_nickToClient.erase(it->second.getNick());

	if (!newNick.empty())
		_nickToClient.insert(std::pair<std::string,
			std::map<int, Client>::iterator>(newNick, it));
}

void ClientList::updateUser(int fd, std::string newUser) {
	std::map<int, Client>::iterator it = getClient(fd);

	if (it == end())
		return;

	if (!it->second.getNick().empty())
		_nickToClient.erase(it->second.getUser());

	if (!newUser.empty())
		_nickToClient.insert(std::pair<std::string,
			std::map<int, Client>::iterator>(newUser, it));
}
