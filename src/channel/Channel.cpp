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

Channel::Channel(void) : _name("#default"), _topic(""), _key(""),
	_users(), _channelModeFlags(NO_CMODE), _limit(-1) { }

Channel::Channel(const std::string &name) : _name(name), _topic(""), _key(""),
_users(), _channelModeFlags(NO_CMODE), _limit(-1) { }

Channel::Channel(const Channel &src) : _name(src._name), _topic(src._topic),
	_key(src._key), _users(src._users),
	_channelModeFlags(src._channelModeFlags), _limit(src._limit) { }

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
const std::string &Channel::getName(void) { return _name; }

const std::string &Channel::getTopic(void) { return _topic; }

const std::string &Channel::getKey(void) {	return _key; }

int	Channel::getUserLimit(void) { return _limit; }

int	Channel::getNumUsers(void) { return _users.size(); }

bool Channel::getChannelMode(t_cmode mode) {
	return (_channelModeFlags & mode) != 0;
}

int Channel::getChannelModeFlags(void) { return _channelModeFlags; }

bool Channel::getUserMode(const int userFD, const t_umode mode) {
	return (getUserModeFlags(userFD) & mode) != 0;
}

int Channel::getUserModeFlags(const int userFD) {
	std::map<int, int>::iterator it = _users.find(userFD);

	// TODO: add exception
	if (it == _users.end())
		return NO_UMODE;

	return it->second;
}

bool Channel::userIsInChannel(const int userFD) {
	std::map<int, int>::iterator it = _users.find(userFD);

	return (it != _users.end());
}

bool Channel::userCanJoin(const int userFD) {
	// TODO: mask checks
	(void)userFD;
	return true;
}

bool Channel::empty(void) { return _users.empty(); }

// Setters
void Channel::setTopic(const std::string &topic) { _topic = topic; }

void Channel::setKey(const std::string &key) { _key = key; }

void Channel::setUserLimit(const int limit) {_limit = limit; }

void Channel::setChannelMode(const std::string &modeStr) {
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

void Channel::setChannelModeFlags(const int modeFlags) {
	_channelModeFlags = modeFlags;
}

void Channel::setUserMode(const int userFD, const std::string &modeStr) {
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

void Channel::setUserModeFlags(const int userFD, const int modeFlags) {
	std::map<int, int>::iterator it = _users.find(userFD);

	// TODO: add exception
	if (it == _users.end())
		return;

	it->second = modeFlags;
}

void Channel::addUser(const int fd, const int userModeFlags) {
	// TODO: add exception
	if (!userCanJoin(fd))
		return;

	_users.insert(std::pair<int, int>(fd, userModeFlags));
}

void Channel::removeUser(const int fd) {
	_users.erase(fd);
}

std::map<int, int>::iterator Channel::usersBegin(void) {
	return _users.begin();
}

std::map<int, int>::iterator Channel::usersEnd(void) {
	return _users.end();
}

bool Channel::userHasInvite(const std::string &nick) {
	return (_invites.find(nick) != _invites.end());
}

void Channel::addInvite(const std::string &nick) { _invites.insert(nick); }

void Channel::removeInvite(const std::string &nick) { _invites.erase(nick); }
