/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:46:51 by gmachado          #+#    #+#             */
/*   Updated: 2024/08/19 15:09:37 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelList.hpp"
#include "Colors.hpp"
#include <iostream>

ChannelList::ChannelList(ClientList &clients, MsgHandler &msgHandler) :
	_channels(), _clients(clients), _msgHandler(msgHandler) { }

ChannelList::ChannelList(ChannelList &src) : _channels(src._channels),
	_clients(src._clients), _msgHandler(src._msgHandler) { }

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

int ChannelList::size(void) {
	int count = 0;
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		++count;
	return count;
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
	std::map<int, Client>::iterator userIt = _clients.getClient(userFD);

	if (userIt == _clients.end())
		return;

	std::map<std::string, Channel>::iterator chanIt = get(chanName);
	bool	isOper = false;

	try {
		if (chanIt == end())
		{
			chanIt = add(Channel(chanName, _msgHandler));
			isOper = true;
		}

		Channel& chan = chanIt->second;
		chan.addUser(userFD, _DEFAULT_FLAGS);
		userIt->second.addChannel(chanName);

		if (isOper)
			chan.setUserModeFlags(userFD,
				chan.getChannelModeFlags() | Channel::CHANOP);

		return;
	} catch (std::exception &e) {
		_msgHandler.getLogger().error(RED + "Could not create channel: " +
			YELLOW + chanName + RESET);
		return;
	}

	if (!userCanJoin(userFD, chanIt->second, key))
		return;

	chanIt->second.addUser(userFD, _DEFAULT_FLAGS);
	userIt->second.addChannel(chanName);
}

void ChannelList::part(int userFD, std::string chanName) {
	std::map<std::string, Channel>::iterator chanIt = get(chanName);
	std::map<int, Client>::iterator userIt = _clients.getClient(userFD);

	if (chanIt == end() || userIt == _clients.end())
		return;

	chanIt->second.removeUser(userFD);
	userIt->second.removeChannel(chanName);

	try {
		if (chanIt->second.empty())
			remove(chanName);

	} catch (std::exception &e) {
		_msgHandler.getLogger().error(RED + "Could not remove channel: " +
			YELLOW + chanName + RESET);
		return;
	}
}

void ChannelList::partDisconnectedClient(int userFD)
{
	std::set<std::string>::iterator chanIt;
	std::map<int, Client>::iterator userIt = _clients.getClient(userFD);

	if (userIt == _clients.end())
		return;

	std::set<std::string> &chanRef = userIt->second.getChannelList();
	;

	for (chanIt = chanRef.begin(); chanIt != chanRef.end();)
	{
		std::set<std::string>::iterator oldChanIt = chanIt++;
		part(userFD, oldChanIt->data());
	}
}

bool ChannelList::userCanJoin(int userFD, Channel &chan,
		const std::string &key) {
	std::map<int, Client>::iterator userIt = _clients.getClient(userFD);

	if (userIt == _clients.end())
		return false;

	if (chan.userIsInChannel(userFD))
		return false;

	if (chan.getKey() != key)
		return false;

	if (chan.getUserLimit() != -1 && chan.getUserLimit() == chan.getNumUsers())
		return false;

	if (chan.getChannelMode(Channel::INVITEONLY) &&
		!userHasInvite(userIt->second.getNick(), chan.getName()))
		return false;

	return true;
}

bool ChannelList::userHasInvite(const std::string &nick,
		const std::string &chan) {
	std::map<std::string, std::set<std::string> >::iterator chanIt;

	chanIt = _invites.find(chan);

	if (chanIt == _invites.end())
		return false;

	if (chanIt->second.find(nick) == chanIt->second.end())
		return false;

	return true;
}

void ChannelList::addInvite(const std::string &nick,
		const std::string &chan) {
	std::map<std::string, std::set<std::string> >::iterator chanIt;
	std::pair<std::string, std::set<std::string> > newSetPair;

	chanIt = _invites.find(chan);

	if (chanIt == _invites.end())
	{
		newSetPair = std::make_pair(chan, std::set<std::string>());
		newSetPair.second.insert(nick);
		_invites.insert(newSetPair);
		return;
	}

	chanIt->second.insert(nick);
}

void ChannelList::removeInvite(const std::string &nick,
		const std::string &chan) {
	std::map<std::string, std::set<std::string> >::iterator chanIt;

	chanIt = _invites.find(chan);

	if (chanIt == _invites.end())
		return;

	chanIt->second.erase(nick);

	if (chanIt->second.empty())
		_invites.erase(chanIt);
}

t_numCode ChannelList::inviteUser(const std::string &inviter,
		const std::string &invitee, const std::string &chan) {
	if (inviter.empty() || invitee.empty() || chan.empty())
		return ERR_NEEDMOREPARAMS;

	std::map<std::string, Channel>::iterator chanIt;

	if (chanIt != _channels.end())
	{
		int inviteeFD = _clients.getFDByNick(invitee);
		Channel &chanRef = chanIt->second;

		if (chanRef.userIsInChannel(inviteeFD))
			return ERR_USERONCHANNEL;

		int inviterFD = _clients.getFDByNick(inviter);

		if (chanRef.userIsInChannel(inviterFD))
			return ERR_NOTONCHANNEL;

		if (chanRef.getChannelMode(Channel::INVITEONLY) &&
			chanRef.getUserMode(inviterFD, Channel::CHANOP))
			return ERR_CHANOPRIVSNEEDED;
	}

	addInvite(invitee, chan);
	return RPL_INVITING;
}
