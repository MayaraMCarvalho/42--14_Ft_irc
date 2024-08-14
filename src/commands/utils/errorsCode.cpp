/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorsCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:30:03 by macarval          #+#    #+#             */
/*   Updated: 2024/08/05 12:09:49 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string Commands::errorUnknownError( void )
{
	return (toString(ERR_UNKNOWNERROR) + " " + _clients.getNick(_fd)
			+ " :Unknown error");
}

std::string Commands::errorNoSuchNick(std::string &recipient)
{
	return (toString(ERR_NOSUCHNICK) + " " + _clients.getNick(_fd)
			+ " " + recipient + " :No such nick");
}

std::string Commands::errorNoSuchChannel(std::string &channelName)
{
	return (toString(ERR_NOSUCHCHANNEL) + " " + _clients.getNick(_fd)
			+ " " + channelName + " :No such channel");
}

std::string Commands::errorCannotSendToChan(std::string &channelName)
{
	return (toString(ERR_CANNOTSENDTOCHAN) + " " + _clients.getNick(_fd)
			+ " " + channelName + " :Cannot send to channel");
}

std::string Commands::errorTooManyChannels(std::string &channelName)
{
	return (toString(ERR_TOOMANYCHANNELS) + " " + clients.getNick(_fd) +
			" " + channelName + " :You have joined too many channels");
}

std::string Commands::errorNoRecipient( void )
{
	return (toString(ERR_NORECIPIENT) + " " + _clients.getNick(_fd)
			+ " :No recipient given");
}

std::string Commands::errorNoTextToSend( void )
{
	return (toString(ERR_NOTEXTTOSEND) + " " + _clients.getNick(_fd)
			+ " :No text to send");
}

std::string Commands::errorInputTooLong( void )
{
	return (toString(ERR_INPUTTOOLONG) + " " + _clients.getNick(_fd)
			+ " :Input line was too long");
}

std::string Commands::errorNoNicknameGiven( void )
{
	return (toString(ERR_NONICKNAMEGIVEN)
			+ " :No nickname given");
}

std::string Commands::errorErroneusNickname(std::string &arg)
{
	return (toString(ERR_ERRONEUSNICKNAME) + " * "
			+ arg + " :Erroneus nickname");
}

std::string Commands::errorNicknameInUse(std::string &nick)
{
	return (toString(ERR_NICKNAMEINUSE) + " " + nick
			+ " :Nickname is already in use");
}

std::string Commands::errorUserNotInChannel(std::string &nick,
											std::string &channelName)
{
	return (toString(ERR_USERNOTINCHANNEL) + " " + nick
			+ " " + channelName + " :They aren't on that channel");
}

std::string Commands::errorNotOnChannel(std::string &channelName)
{
	return (toString(ERR_NOTONCHANNEL) + " " + _clients.getNick(_fd)
			+ " " + channelName + " :You're not on that channel");
}

std::string Commands::errorUserOnChannel(std::string &nick,
										 std::string &channelName)
{
	return (toString(ERR_USERONCHANNEL) + " " + nick + " "
			+ channelName + " :is already on channel");
}

std::string Commands::errorNotRegistered( void )
{
	return(toString(ERR_NOTREGISTERED)
			+ " * :You have not registered");
}

std::string Commands::errorNeedMoreParams( void )
{
	return (toString(ERR_NEEDMOREPARAMS) + " " + _clients.getNick(_fd)
			+ " " + _args[0] + " :Not enough parameters");
}

std::string Commands::errorAlredyRegister( void )
{
	return (toString(ERR_ALREADYREGISTERED) + " "
			+ _clients.getNick(_fd) + " :You may not reregister");
}

std::string Commands::errorPassMismatch( void )
{
	return (toString(ERR_PASSWDMISMATCH)
			+ " * :Password incorrect");
}

std::string Commands::errorKeySet(std::string &channelName)
{
	return (toString(ERR_KEYSET) + " " + _clients.getNick(_fd)
			+ " " + channelName + " :Channel key already set");
}

std::string Commands::errorChannelIsFull(std::string &nick,
										 std::string &channel)
{
	return (toString(ERR_CHANNELISFULL) + " " + nick + " "
			+ channel + " :Cannot join channel " + "(+l)");
}

std::string Commands::errorUnknownMode(std::string &nick, std::string &mode)
{
	return (toString(ERR_UNKNOWNMODE) + " " + nick + " "
			+ mode + " is unknown mode char to me");
}

std::string Commands::errorInviteOnlyChan(std::string &nick,
										  std::string &channel)
{
	return (toString(ERR_INVITEONLYCHAN) + " " + nick + " "
			+ channel + " :Cannot join channel " + "(+i)");
}

std::string Commands::errorBannedFromChan(std::string &nick,
										  std::string &channel)
{
	return (toString(ERR_BANNEDFROMCHAN) + " " + nick + " "
			+ channel + " :Cannot join channel " + "(+b)");
}

std::string Commands::errorBadChannelKey(std::string &nick,
										 std::string &channel)
{
	return (toString(ERR_BADCHANNELKEY) + " " + nick + " "
			+ channel + " :Cannot join channel " + "(+k)");
}

std::string Commands::errorBadChanMask(std::string &channelName)
{
	return (toString(ERR_BADCHANMASK) + " " + _clients.getNick(_fd)
			+ " " + channelName + " :Bad Channel Mask");
}

std::string Commands::errorChanPrivsNeeded(std::string &channelName)
{
	return (toString(ERR_CHANOPRIVSNEEDED) + ": "
			+ channelName + " :You're not channel operator");
}

std::string Commands::errorUModeUnknowFlag(std::string &nick)
{
	return (toString(ERR_UMODEUNKNOWNFLAG) + " " + nick
			+ " :Unknown MODE flag");
}

std::string Commands::errorUsersDontMatch( void )
{
	return (toString(ERR_USERSDONTMATCH) + " " + _clients.getNick(_fd)
			+ " :Cant change mode for other users");
}

// std::string Commands::error...( void )
// {
// 	return (toString(...) + " " + _clients.getNick(_fd)
//			+ "...");
// }
