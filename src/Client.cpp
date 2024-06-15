/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:43:45 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/12 03:43:48 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Channel.hpp"

Client::Client() : _nick(""), _user(""), _host(""), _fd(-1), _channels(),
	_modeFlags(Client::NO_MODE), _status(Client::UNKNOWN) { }

Client::Client(int fd) : _nick(""), _user(""), _host(""), _fd(fd),
	_channels(), _modeFlags(Client::NO_MODE), _status(Client::UNKNOWN) { }

Client::Client(Client &src) : _nick(src._nick), _user(src._user),
	_host(src._host), _fd(src._fd), _channels(src._channels),
	_modeFlags(src._modeFlags), _status(src._status) { }

Client::~Client(void) {
	std::map<std::string, Channel*>::iterator it;
	for(it = _channels.begin(); it != _channels.end(); ++it)
		it->second->removeClient(_fd);
}

Client &Client::operator=(Client &src) {
	if (this == &src)
		return *this;

	_nick = src._nick;
	_user = src._user;
	_host = src._host;
	_fd = src._fd;
	_channels = src._channels;
	_modeFlags = src._modeFlags;
	_status = src._status;

	return *this;
}

// Getters
std::string Client::getNick(void) { return _nick; }

std::string Client::getUser(void) { return _user; }

std::string Client::getHost(void) { return _host; }

std::string Client::getFullId(void) {
	return _nick + '!' + _user + '@' + _host;
}

int Client::getFD(void) {  { return _fd; }}

std::map<std::string, Channel*> &Client::getChannelList(void) {
	return _channels;
}

Client::t_status Client::getStatus(void) { return _status; }

bool Client::getMode(t_mode mode) { return (_modeFlags & mode) != 0; }

int Client::getModeFlags(void) { return _modeFlags; }

// Setters
void Client::setNick(std::string nick) { _nick = nick; }

void Client::setUser(std::string user) { _user = user; }

void Client::setHost(std::string host) { _host = host; }

void Client::setModeFlags(int modeFlags) { _modeFlags = modeFlags; }

void Client::setMode(std::string modeStr) {

	int newModeFlags;

	if (modeStr.length() != 2)
		return;

	if (modeStr[1] == 'a')
		newModeFlags = AWAY;
	else if (modeStr[1] == 'i')
		newModeFlags = INVISIBLE;
	else if (modeStr[1] == 'w')
		newModeFlags = WALLOPS;
	else if (modeStr[1] == 'r')
		newModeFlags = RESTRICTED;
	else if (modeStr[1] == 'o')
		newModeFlags = OPERATOR;
	else if (modeStr[1] == 'O')
		newModeFlags = LOCAL_OP;
	else if (modeStr[1] == 's')
		newModeFlags = RECV_NOTICES;
	else
		return;

	if (modeStr[0] == '+')
		_modeFlags |= newModeFlags;
	else if (modeStr[0] == '-')
		_modeFlags &= (~newModeFlags);
}
void Client::setStatus(t_status status) { _status = status; }

// Channel functions
bool Client::isInChannel(std::string channelStr) {
	return _channels.find(channelStr) != _channels.end();
}
void Client::addChannel(Channel &channel)
{
	_channels.insert(
		std::pair<std::string, Channel>(channel.getName(), channel));
}
void Client::removeChannel(std::string channelStr) {
	_channels.erase(channelStr);
}
