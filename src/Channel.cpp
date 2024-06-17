/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:47:00 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/12 03:53:35 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "IrcServer.hpp"

Channel::Channel(void) : _name("#default"), _topic(""), _users(),
	_channelModeFlags(NO_CMODE), _limit(-1) { }

Channel::Channel(std::string name) : _name(name), _topic(""), _users(),
	_channelModeFlags(NO_CMODE), _limit(-1) { }

Channel::Channel(const Channel &src) : _name(src._name), _topic(src._topic),
	_users(src._users), _channelModeFlags(src._channelModeFlags),
	_limit(src._limit) { }

Channel::~Channel(void) { }

Channel &Channel::operator=(const Channel &src) {
	if (this == &src)
		return *this;

	_name = src._name;
	_topic = src._topic;
	_users = src._users;
	_channelModeFlags = src._channelModeFlags;
	_limit = src._limit;

	return *this;
}

// Getters
std::string Channel::getName(void) { return _name; }

std::string Channel::getTopic(void) { return _topic; }

int	Channel::getUserLimit(void) { return _limit; }

bool Channel::getChannelMode(t_cmode mode) {
	return (_channelModeFlags & mode) != 0;
}

int Channel::getChannelModeFlags(void) { return _channelModeFlags; }

bool Channel::getUserMode(int userFD, t_umode mode) {
	return (getUserModeFlags(userFD) & mode) != 0;
}

int Channel::getUserModeFlags(int userFD) {
	std::map<int, int>::iterator it = _users.find(userFD);

	// TODO: add exception
	if (it == _users.end())
		return NO_UMODE;

	return it->second;
}

bool Channel::isUserInChannel(int userFD) {
	std::map<int, int>::iterator it = _users.find(userFD);

	return (it != _users.end());
}

bool Channel::userCanJoin(int userFD) {
	// TODO: mask checks
	(void)userFD;
	return true;
}

// Setters
void Channel::setTopic(std::string topic) { _topic = topic; }

void Channel::setUserLimit(int limit) {_limit = limit; }

void Channel::setChannelMode(std::string modeStr) {
	int newModeFlags;

	if (modeStr.length() != 2)
		return;

	if (modeStr[1] == 'a')
		newModeFlags = ANONYMOUS;
	else if (modeStr[1] == 'i')
		newModeFlags = INVITEONLY;
	else if (modeStr[1] == 'm')
		newModeFlags = MODERATED;
	else if (modeStr[1] == 'n')
		newModeFlags = NO_OUT_MSG;
	else if (modeStr[1] == 'q')
		newModeFlags = QUIET;
	else if (modeStr[1] == 'p')
		newModeFlags = PRIVATE;
	else if (modeStr[1] == 's')
		newModeFlags = SECRET;
	else if (modeStr[1] == 'r')
		newModeFlags = SERV_REOP;
	else if (modeStr[1] == 't')
		newModeFlags = OP_TOPIC;
	else
		return;

	if (modeStr[0] == '+')
		_channelModeFlags |= newModeFlags;
	else if (modeStr[0] == '-')
		_channelModeFlags &= (~newModeFlags);
}

void Channel::setChannelModeFlags(int modeFlags) {
	_channelModeFlags = modeFlags;
}

void Channel::setUserMode(int userFD, std::string modeStr) {
	std::map<int, int>::iterator it = _users.find(userFD);

	// TODO: add exception
	if (it == _users.end())
		return;

	int newModeFlags;

	if (modeStr.length() != 2)
		return;

	if (modeStr[1] == 'O')
		newModeFlags = CREATOR;
	else if (modeStr[1] == 'o')
		newModeFlags = CHANOP;
	else if (modeStr[1] == 'v')
		newModeFlags = VOICE;
	else
		return;

	if (modeStr[0] == '+')
		(it->second) |= newModeFlags;
	else if (modeStr[0] == '-')
		(it->second) &= (~newModeFlags);
}

void Channel::addUser(int fd, int userModeFlags) {
	// TODO: add exception
	if (!userCanJoin(fd))
		return;

	_users.insert(std::pair<int, int>(fd, userModeFlags));
}

void Channel::removeUser(int fd) {
	_users.erase(fd);
}

void Channel::sendToAll(std::string &message)
{
	for (std::map<int, int>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		IRCServer::sendMessage(it->first, message);
	}
}
