/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsgHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 03:32:58 by gmachado          #+#    #+#             */
/*   Updated: 2024/08/21 23:34:39 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include "MsgHandler.hpp"
#include "Client.hpp"
#include "Channel.hpp"
# include "Codes.hpp"

MsgHandler::MsgHandler(MsgHandler &src) : _host(src._host) , _sendQueues(),
	_recvQueues(), _logger(src._logger) { }

MsgHandler::MsgHandler(std::string host, Logger &logger) : _host(host),
	_sendQueues(), _recvQueues(), _logger(logger) { }

MsgHandler::MsgHandler(Logger &logger) : _host("defaulthost"),
	_sendQueues(), _recvQueues(), _logger(logger) { }

MsgHandler::~MsgHandler(void) { }

MsgHandler &MsgHandler::operator=(MsgHandler &src) {
	if (this == &src)
		return *this;

	_host = src._host;
	_recvQueues = src._recvQueues;
	_sendQueues = src._sendQueues;
	return *this;
}

std::string &MsgHandler::getHost(void) { return _host; }

Logger &MsgHandler::getLogger(void) { return _logger; }

void MsgHandler::setHost(std::string host) { _host = host; }

void MsgHandler::sendMessage(int fd, const std::string &msg) {
	sendMessage(fd, _host, msg);
}

void MsgHandler::sendMessage(int fd, const std::string &from,
		const std::string &msg) {
	std::string fullMsg(":" + from + " " + msg + "\r\n");

	sendPush(fd, fullMsg);
}

std::string &MsgHandler::sendPop(int fd) {
	std::map<int, std::string>::iterator it = _sendQueues.find(fd);

	if (it == _sendQueues.end() || it->second.empty())
		throw std::out_of_range("");

	return it->second;
}

bool MsgHandler::sendPush(int fd, std::string msg) {
	std::map<int, std::string>::iterator it = _sendQueues.find(fd);
	std::pair<std::map<int, std::string>::iterator, bool> inserted;

	if (it == _sendQueues.end())
	{
		if (msg.length() > MAX_SEND_QUEUE_LENGTH)
			return false;
		inserted = _sendQueues.insert(
			std::make_pair<int, std::string>(fd, msg));

		if (!inserted.second)
			return false;

		return true;
	}

	if (it->second.length() + msg.length() > MAX_SEND_QUEUE_LENGTH)
		return false;

	it->second += msg;
	return true;
}

void MsgHandler::removeSendChars(int fd, ssize_t numChars) {
	std::map<int, std::string>::iterator it = _sendQueues.find(fd);

	if (it != _sendQueues.end())
		it->second = it->second.substr(numChars);
}

ssize_t MsgHandler::sendLength(int fd) {
	std::map<int, std::string>::iterator it = _sendQueues.find(fd);

	if (it == _sendQueues.end())
		return 0;

	return it->second.length();
}

bool MsgHandler::recvPush(int fd, std::string msg) {
	std::map<int, std::string>::iterator it = _recvQueues.find(fd);
	std::pair<std::map<int, std::string>::iterator, bool> inserted;

	if (it == _recvQueues.end())
	{
		if (msg.length() > MAX_RECV_QUEUE_LENGTH)
			return false;
		inserted = _recvQueues.insert(
			std::make_pair<int, std::string>(fd, msg));

		if (!inserted.second)
			return false;

		return true;
	}

	if (it->second.length() + msg.length() > MAX_RECV_QUEUE_LENGTH)
			return false;

	(it->second) += msg;
	return true;
}

std::string &MsgHandler::recvPop(int fd) {
	std::map<int, std::string>::iterator it = _recvQueues.find(fd);

	if (it == _recvQueues.end() || it->second.empty())
		throw std::out_of_range("");

	return it->second;
}

ssize_t MsgHandler::recvLength(int fd) {
	std::map<int, std::string>::iterator it = _recvQueues.find(fd);

	if (it == _recvQueues.end())
		return 0;

	return it->second.length();
}

void MsgHandler::resetQueues(int fd) {
	std::map<int, std::string>::iterator recvIt = _recvQueues.find(fd);
	std::map<int, std::string>::iterator sendIt = _sendQueues.find(fd);

	if (recvIt != _recvQueues.end())
		_recvQueues.erase(recvIt);

	if (sendIt != _sendQueues.end())
		_sendQueues.erase(sendIt);
}

// Numeric error replies

std::string MsgHandler::errNeedMoreParams(const std::string &client,
		const std::string &command) {
	std::ostringstream ss;

	ss << ERR_NEEDMOREPARAMS << ' ' << client << ' ' << command
		<< " :Not enough parameters";
	return ss.str();
}

std::string MsgHandler::errAlreadyRegistered(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_ALREADYREGISTERED << ' ' << client << " :You may not reregister";
	return ss.str();
}

std::string MsgHandler::errPasswordMismatch(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_PASSWDMISMATCH << ' ' << client << " :Password incorrect";
	return ss.str();
}

std::string MsgHandler::errErroneusNickname(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_ERRONEUSNICKNAME << ' ' << client << " :Erroneus nickname";
	return ss.str();
}

std::string MsgHandler::errNoNickNameGiven(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_NONICKNAMEGIVEN << ' ' << client << " :No nickname given";
	return ss.str();
}

std::string MsgHandler::errNicknameInUse(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_NICKNAMEINUSE << ' ' << client << " :Nickname is already in use";
	return ss.str();
}

std::string MsgHandler::errNoOrigin(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_NOORIGIN << ' ' << client << " :No origin specified";
	return ss.str();
}

std::string MsgHandler::errNoSuchChannel(const std::string &client,
		const std::string &channel) {
	std::ostringstream ss;

	ss << ERR_NOSUCHCHANNEL << ' ' << client << ' ' << channel
		<< " :No such channel";
	return ss.str();
}

std::string MsgHandler::errNoSuchNick(const std::string &client,
			const std::string &nick) {
	std::ostringstream ss;

	ss << ERR_NOSUCHNICK << ' ' << client << ' ' << nick
		<< " :No such nick";
	return ss.str();
}

std::string MsgHandler::errTooManyChannels(const std::string &client,
		const std::string &channel) {
	std::ostringstream ss;

	ss << ERR_TOOMANYCHANNELS << ' ' << client << ' ' << channel
		<< " :You have joined too many channels";
	return ss.str();
}

std::string MsgHandler::errBadChannelKey(const std::string &client,
		const std::string &channel) {
	std::ostringstream ss;

	ss << ERR_BADCHANNELKEY << ' ' << client << ' ' << channel
		<< " :Cannot join channel (+k)";
	return ss.str();
}

std::string MsgHandler::errBannedFromChan(const std::string &client,
		const std::string &channel) {
	std::ostringstream ss;

	ss << ERR_BANNEDFROMCHAN << ' ' << client << ' ' << channel
		<< " :Cannot join channel (+b)";
	return ss.str();
}

std::string MsgHandler::errChannelIsFull(const std::string &client,
		const std::string &channel) {
	std::ostringstream ss;

	ss << ERR_CHANNELISFULL << ' ' << client << ' ' << channel
		<< " :Cannot join channel (+l)";
	return ss.str();
}

std::string MsgHandler::errInputTooLong(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_INPUTTOOLONG << ' ' << client
		<< " :Input line was too long";
	return ss.str();
}

std::string MsgHandler::errInviteOnlyChan(const std::string &client,
		const std::string &channel) {
	std::ostringstream ss;

	ss << ERR_INVITEONLYCHAN << ' ' << client << ' ' << channel
		<< " :Cannot join channel (+i)";
	return ss.str();
}

std::string MsgHandler::errBadChanMask(const std::string &channel) {
	std::ostringstream ss;

	ss << ERR_BADCHANMASK << ' ' << channel
		<< " :Bad Channel Mask";
	return ss.str();
}

std::string MsgHandler::errCannotSendToChan(const std::string &client,
			const std::string &channel) {
	std::ostringstream ss;

	ss << ERR_CANNOTSENDTOCHAN << ' ' << client << ' ' << channel
		<< " :Cannot send to channel";
	return ss.str();
}

std::string MsgHandler::errNoRecipient(const std::string &client,
			const std::string &command) {
	std::ostringstream ss;

	ss << ERR_NORECIPIENT << ' ' << client
		<< " :No recipient given (" << command << ")";
	return ss.str();
}

std::string MsgHandler::errNoTextToSend(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_NOTEXTTOSEND << ' ' << client
		<< " :No text to send";
	return ss.str();
}

std::string MsgHandler::errNotOnChannel(const std::string &client,
		const std::string &channel) {
	std::ostringstream ss;

	ss << ERR_NOTONCHANNEL << ' ' << client << ' ' << channel
		<< " :You're not on that channel";
	return ss.str();
}

std::string MsgHandler::errNotRegistered(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_NOTREGISTERED << ' ' << client
		<< " :You have not registered";
	return ss.str();
}

std::string MsgHandler::errChanOPrivIsNeeded(const std::string &client,
		const std::string &channel) {
	std::ostringstream ss;

	ss << ERR_CHANOPRIVSNEEDED << ' ' << client << ' ' << channel
		<< " :You're not channel operator";
	return ss.str();
}

std::string MsgHandler::errInvalidModeParam(const std::string &client,
			const std::string &target, const char mode,
			const std::string &param, const std::string &description) {
	std::ostringstream ss;

	ss << ERR_INVALIDMODEPARAM << ' ' << client << ' ' << target
		<< ' ' << mode << ' ' << param << " :" << description;
	return ss.str();
}

std::string MsgHandler::errUModeUnknownFlag(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_UMODEUNKNOWNFLAG << ' ' << client
		<< " :Unknown MODE flag";
	return ss.str();
}

std::string MsgHandler::errUnknownCommand(const std::string &client,
		const std::string &command, const std::string &info) {
	std::ostringstream ss;

	ss << ERR_UNKNOWNCOMMAND << ' ' << client
		<< ' ' << command << " :" << info;
	return ss.str();
}

std::string MsgHandler::errUnknownCommand(const std::string &client,
		const std::string &command, const std::string &subcommand,
		const std::string &info) {
	std::ostringstream ss;

	ss << ERR_UNKNOWNCOMMAND << ' ' << client
		<< ' ' << command << ' ' << subcommand << " :" << info;
	return ss.str();
}

std::string MsgHandler::errUnknownMode(const std::string &client,
		const char mode) {
	std::ostringstream ss;

	ss << ERR_UNKNOWNMODE<< ' ' << client << ' ' << mode
		<< " :is unknown mode char to me";
	return ss.str();
}

std::string MsgHandler::errUserOnChannel(const std::string &client,
			const std::string &channel, const std::string &nick) {
	std::ostringstream ss;

	ss << ERR_USERONCHANNEL << ' ' << client << ' ' << nick
		<< ' ' << channel << " :is already on channel";
	return ss.str();
}

std::string MsgHandler::errUserNotInChannel(const std::string &client,
			const std::string &channel, const std::string &nick) {
	std::ostringstream ss;

	ss << ERR_USERNOTINCHANNEL << ' ' << client << ' ' << nick
		<< ' ' << channel << " :They aren't on that channel";
	return ss.str();
}

std::string MsgHandler::errUsersDontMatch(const std::string &client) {
	std::ostringstream ss;

	ss << ERR_USERSDONTMATCH << ' ' << client
		<< " :Cant change mode for other users";
	return ss.str();
}

// Numeric normal replies

std::string MsgHandler::rplWelcome(const std::string &client) {
	std::ostringstream ss;

	ss << RPL_WELCOME << ' ' << client << " :Welcome to "
		<< _host << " IRC server!";
	return ss.str();
}

std::string MsgHandler::rplEndOfNames(const std::string &client,
		const std::string &channel) {
	std::ostringstream ss;

	ss << RPL_ENDOFNAMES << ' ' << client << ' ' << channel
		<< " :End of /NAMES list";
	return ss.str();
}

std::string MsgHandler::rplNamReply(const std::string &client,
		const std::string &channel, const std::string &clientList,
	const char symbol) {
	std::ostringstream ss;

	ss << RPL_NAMREPLY << ' ' << client << ' ' << symbol << ' ' << channel
		<< ' ' << clientList;
	return ss.str();
}

std::string MsgHandler::rplTopic(const std::string &client,
		const std::string &channel, const std::string &topic) {
	std::ostringstream ss;

	ss << RPL_TOPIC << ' ' << client << ' ' << channel
		<< " :" << topic;
	return ss.str();
}

std::string MsgHandler::rplNoTopic(const std::string &client,
			const std::string &channel) {
	std::ostringstream ss;

	ss << RPL_NOTOPIC << ' ' << client << ' ' << channel
		<< " :No topic is set";
	return ss.str();
}

std::string MsgHandler::rplList(const std::string &client,
	const std::string &channel, const std::string &topic,
	const int numUsers) {
	std::ostringstream ss;


	ss << RPL_LIST << ' ' << client << ' ' << channel
		<< ' ' << numUsers;

	if (!topic.empty())
		ss << " :" << topic;

	return ss.str();
}

std::string MsgHandler::rplListEnd(const std::string &client) {
	std::ostringstream ss;

	ss << RPL_LISTEND << ' ' << client
		<< " :End of /LIST";
	return ss.str();
}

std::string MsgHandler::rplInviting(const std::string &client,
			const std::string &channel, const std::string &nick) {
	std::ostringstream ss;

	ss << RPL_INVITING << ' ' << client << ' ' << nick
		<< ' ' << channel;
	return ss.str();
}

std::string MsgHandler::rplUModeIs(const std::string &client,
			const int userModes) {
	std::ostringstream ss;

	ss << RPL_UMODEIS << ' ' << client;

	if (userModes & ~Client::AWAY)
		ss << " +";

	if (userModes & Client::INVISIBLE)
		ss << 'i';

	if (userModes & Client::OPERATOR)
		ss << 'o';

	if (userModes & Client::LOCAL_OP)
		ss << 'O';

	if (userModes & Client::LOCAL_OP)
		ss << 'r';

	if (userModes & Client::RECV_NOTICES)
		ss << 's';

	if (userModes & Client::WALLOPS)
		ss << 'w';

	return ss.str();
}

std::string MsgHandler::rplChannelModeIs(const std::string &client,
			const int chanModes) {
	std::ostringstream ss;

	ss << RPL_CHANNELMODEIS << ' ' << client;

	if (chanModes & ~Channel::SAFE)
		ss << " +";

	if (chanModes & Channel::ANONYMOUS)
		ss << 'a';

	if (chanModes & Channel::INVITEONLY)
		ss << 'i';

	if (chanModes & Channel::HAS_KEY)
		ss << 'k';

	if (chanModes & Channel::ULIMIT)
		ss << 'l';

	if (chanModes & Channel::MODERATED)
		ss << 'm';

	if (chanModes & Channel::NO_OUT_MSG)
		ss << 'n';

	if (chanModes & Channel::PRIVATE)
		ss << 'p';

	if (chanModes & Channel::QUIET)
		ss << 'q';

	if (chanModes & Channel::SECRET)
		ss << 's';

	if (chanModes & Channel::OP_TOPIC)
		ss << 't';

	return ss.str();
}
