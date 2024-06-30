/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsgHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 03:32:58 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/30 04:50:22 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "MsgHandler.hpp"
#include "Client.hpp"
#include "Channel.hpp"
# include "numCode.hpp"

MsgHandler::MsgHandler(void) { }

MsgHandler::MsgHandler(MsgHandler &src) { (void)src; }

MsgHandler::~MsgHandler(void) { }

MsgHandler &MsgHandler::operator=(MsgHandler &src) {
	(void)src;
	return *this;
}

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
