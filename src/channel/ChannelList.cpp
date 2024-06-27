/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:46:51 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/27 10:12:24 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelList.hpp"

ChannelList::ChannelList(void) : _channels(), _clients(NULL) { }

ChannelList::ChannelList(ClientList *clients) : _channels(),
	_clients(clients) { }

ChannelList::ChannelList(ChannelList &src) : _channels(src._channels),
	_clients(src._clients) { }

ChannelList::~ChannelList(void) { }

ChannelList &ChannelList::operator=(ChannelList &src) {
	if (this == &src)
		return *this;

	_channels = src._channels;
	return *this;
}

// Getters
std::map<std::string, Channel>::iterator ChannelList::get(std::string name) {
	return _channels.find(name);
}

std::map<std::string, Channel>::iterator ChannelList::begin(void) {
	return _channels.begin();
}

std::map<std::string, Channel>::iterator ChannelList::end(void) {
	return _channels.end();
}

std::map<std::string, Channel>::iterator ChannelList::add(Channel channel) {
	std::pair<std::map<std::string, Channel>::iterator, bool> result;

	result = _channels.insert(
		std::pair<const std::string, Channel>(channel.getName(), channel));

	if (!result.second)
		throw std::exception();

	return result.first;
}

std::map<std::string, Channel>::size_type ChannelList::remove(std::string name)
{
	std::map<std::string, Channel>::size_type removed = _channels.erase(name);

	if (removed == 0)
		throw std::exception();

	return removed;
}

void ChannelList::join(int userFD, const std::string &chanName,
	const std::string &key) {
	if (!_clients)
		return;

	std::map<int, Client>::iterator userIt = _clients->getClient(userFD);

	// TODO: add exception
	if (userIt == _clients->end())
		return;

	std::map<std::string, Channel>::iterator chanIt = get(chanName);

	try {
		if (chanIt == end())
			chanIt = add(Channel(chanName));

		Channel& chan = chanIt->second;
		chan.addUser(userFD, _DEFAULT_FLAGS);
		userIt->second.addChannel(chanName);
		chan.setUserModeFlags(userFD,
			chan.getChannelModeFlags() | Channel::CHANOP);
		return;
	} catch (std::exception &e) {
		std::cerr << RED << "Could not create channel: " << YELLOW
			<< chanName << std::endl;
		std::cout << RESET << std::endl;
		return;
	}

	// TODO: add exception
	if (!userCanJoin(userFD, chanIt->second, key))
		return;

	chanIt->second.addUser(userFD, _DEFAULT_FLAGS);
	userIt->second.addChannel(chanName);
}

void ChannelList::part(int userFD, std::string chanName) {
	if (!_clients)
		return;

	std::map<std::string, Channel>::iterator chanIt = get(chanName);
	std::map<int, Client>::iterator userIt = _clients->getClient(userFD);

	// TODO: add exception
	if (chanIt == end() || userIt == _clients->end())
		return;

	chanIt->second.removeUser(userFD);
	userIt->second.removeChannel(chanName);

	try {
		if (chanIt->second.empty())
			remove(chanName);

	} catch (std::exception &e) {
		std::cerr << RED << "Could not remove channel: " << YELLOW
			<< chanName << std::endl;
		std::cout << RESET << std::endl;
		return;
	}
}

void ChannelList::partDisconnectedClient(int userFD)
{
	if (!_clients)
		return;

	std::set<std::string>::iterator chanIt;
	std::map<int, Client>::iterator userIt = _clients->getClient(userFD);

	if (userIt == _clients->end())
		return;

	std::set<std::string> &chanRef = userIt->second.getChannelList();
	;

	for (chanIt = chanRef.begin();chanIt != chanRef.end();)
	{
		std::set<std::string>::iterator oldChanIt = chanIt++;
		part(userFD, oldChanIt->data());
	}
}

bool ChannelList::userCanJoin(int userFD, Channel &chan,
	const std::string &key) {
	std::map<int, Client>::iterator userIt = _clients->getClient(userFD);

	if (userIt == _clients->end())
		return false;

	if (chan.userIsInChannel(userFD))
		return false;

	if (chan.getKey() != key)
		return false;

	if (chan.getUserLimit() != -1 && chan.getUserLimit() == chan.getNumUsers())
		return false;

	if (chan.getChannelMode(Channel::INVITEONLY) &&
		!chan.userHasInvite(userIt->second.getNick()))
		return false;

	return true;
}
