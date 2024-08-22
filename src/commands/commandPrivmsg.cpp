/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandPrivmsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:40:49 by macarval          #+#    #+#             */
/*   Updated: 2024/08/22 10:00:29 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "IrcServer.hpp"

void Commands::commandPrivMsg( void )
{
	if (validSetup() && initValidation(3))
	{
		std::string	recipient = _args[1];
		std::string	message = getMessage(2);
		bool		isChannel = isItChannel(recipient);

		if (!validArg(recipient) || !validMessage(message))
			return ;

		if (!isChannel)
		{
			if (!sendMessage(_clients.getFDByNick(recipient), message))
				printInfo(errorNoSuchNick(recipient));
		}
		else if (validChannelName(recipient) && verifyChannel(recipient))
			sendMessageChannel(recipient, message);
	}
}

bool Commands::isItChannel(const std::string &channelName)
{
	if ((channelName[0] == '#' || channelName[0] == '&'))
		return true;
	return false;
}

bool Commands::sendMessage(int clientFd, const std::string &message)
{
	if (clientFd == -1)
		return false;

	std::string from = _clients.getNick(_fd);
	std::string full = " PRIVMSG " + from + " :" + message;

	if (message.find("unknown command") != std::string::npos)
		_server.getMsgHandler().sendMessage(clientFd, message);
	else
		_server.getMsgHandler().sendMessage(clientFd, from, full);

	return true;
}

void Commands::sendMessageChannel(std::string &recipient, std::string &message)
{
	std::map<std::string, Channel>::iterator channel = _channels.get(recipient);
	std::string from = _clients.getClient(_fd)->second.getFullId();

	if (channel == _channels.end())
		printInfo(errorNoSuchChannel(recipient));
	else if ((channel->second.getChannelMode(Channel::NO_OUT_MSG)
		&& !_clients.getClient(_fd)->second.isInChannel(recipient))
		|| (channel->second.getChannelMode(Channel::MODERATED)
		&& !channel->second.getUserMode(_fd, Channel::CHANOP)
		&& !channel->second.getUserMode(_fd, Channel::VOICE)))
		printInfo(errorCannotSendToChan(recipient));
	else if (!sendMessage(_channels.get(recipient), message, from))
		printInfo(errorNoSuchChannel(recipient));
}

bool Commands::sendMessage(std::map<std::string, Channel>::iterator channel,
						   std::string &message, std::string &from)
{
	if (channel == _channels.end())
		return false;

	std::string channelName = channel->second.getName();
	if (_args[0] == PRIVMSG)
	{
		std::string full = " PRIVMSG " + channelName + " :" + message;
		channel->second.sendToAll(from, full);
	}
	else
		channel->second.sendToAll(from, message);

	return true;
}
