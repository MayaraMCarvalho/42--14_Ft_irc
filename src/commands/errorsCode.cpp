/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorsCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:30:03 by macarval          #+#    #+#             */
/*   Updated: 2024/07/16 19:09:48 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string Commands::errorNoSuchNick(std::string &recipient, std::string who)
{
	return (RED + toString(ERR_NOSUCHNICK) +
		recipient + ":No such " + who + RESET);
}

std::string Commands::errorNoSuchChannel(std::string &channelName)
{
	return (RED + toString(ERR_NOSUCHCHANNEL) + " " + _clients.getNick(_fd) +
			+ " " + channelName + ":No such channel" + RESET);
}

std::string Commands::errorCannotSendToChan(std::string &channelName)
{
	return (RED + toString(ERR_CANNOTSENDTOCHAN) + " " + _clients.getNick(_fd)
			+ " " + channelName + ":Cannot send to channel" + RESET);
}

std::string Commands::errorTooManyChannels(std::string &channelName)
{
	return (RED + toString(ERR_TOOMANYCHANNELS) + " " + _clients.getNick(_fd) +
			" " + channelName + " :You have joined too many channels" + RESET);
}

std::string Commands::errorNoRecipient( void )
{
	return (RED + toString(ERR_NORECIPIENT) +
					": No recipient given (" + _args[0] + ")" + RESET);
}

std::string Commands::errorNoTextToSend( void )
{
	return (RED + toString(ERR_NOTEXTTOSEND) + ": No text to send" + RESET);
}

std::string Commands::errorNoNicknameGiven( void )
{
	return (RED + toString(ERR_NONICKNAMEGIVEN) +
				": No nickname given" + RESET);
}

std::string Commands::errorErroneusNickname(std::string &arg)
{
	return (RED + toString(ERR_ERRONEUSNICKNAME) + " * " +
			arg + " : Erroneus nickname" + RESET);
}

std::string Commands::errorNicknameInUse(std::string &nick)
{
	return (RED + toString(ERR_NICKNAMEINUSE) + " " +
				nick + " :Nickname is already in use" + RESET);
}

std::string Commands::errorNotOnChannel(std::string &channelName)
{
	return (RED + toString(ERR_NOTONCHANNEL) + " " + _clients.getNick(_fd) +
			+ " " + channelName + ":You're not on that channel" + RESET);
}

std::string Commands::errorNotRegistered( void )
{
	return(RED + toString(ERR_NOTREGISTERED)
			+ " * : You have not registered" + RESET);
}

std::string Commands::errorNeedMoreParams(std::string suffix)
{
	return (RED + toString(ERR_NEEDMOREPARAMS) + " " + _clients.getNick(_fd)
		+ " " + _args[0] + " :" + suffix + RESET);
}

std::string Commands::errorAlredyRegister( void )
{
	return (RED + toString(ERR_ALREADYREGISTERED) + " " +
			_clients.getNick(_fd) + " :You may not reregister" + RESET);
}

std::string Commands::errorPassMismatch( void )
{
	return (RED + toString(ERR_PASSWDMISMATCH)
				+ " * :Password incorrect" + RESET);
}

std::string Commands::errorChannelIsFull(std::string &nick, std::string &channel)
{
	return (RED + toString(ERR_CHANNELISFULL) + " " + nick + " " + channel
			+ " :Cannot join channel " + "(+l)" + RESET);
}

std::string Commands::errorInviteOnlyChan(std::string &nick, std::string &channel)
{
	return (RED + toString(ERR_INVITEONLYCHAN) + " " + nick + " " + channel
			+ " :Cannot join channel " + "(+i)" + RESET);
}

std::string Commands::errorBannedFromChan(std::string &nick, std::string &channel)
{
	return (RED + toString(ERR_BANNEDFROMCHAN) + " " + nick + " " + channel
			+ " :Cannot join channel " + "(+b)" + RESET);
}

std::string Commands::errorBadChannelKey(std::string &nick, std::string &channel)
{
	return (RED + toString(ERR_BADCHANNELKEY) + " " + nick + " " + channel
			+ " :Cannot join channel " + "(+k)" + RESET);
}

std::string Commands::errorBadChanMask(std::string &channelName)
{
	return (RED + toString(ERR_BADCHANMASK) + " " +
		_clients.getNick(_fd) + " " + channelName + " :Bad Channel Mask" + RESET);
}

std::string Commands::errorChanPrivsNeeded(std::string &channelName)
{
	return (RED + toString(ERR_CHANOPRIVSNEEDED) +
			": #" + channelName + ":You're not channel operator" + RESET);
}

// std::string Commands::error...( void )
// {
// 	return (...);
// }
