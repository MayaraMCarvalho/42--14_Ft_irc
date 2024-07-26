/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandPrivmsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:40:49 by macarval          #+#    #+#             */
/*   Updated: 2024/07/26 16:33:44 by macarval         ###   ########.fr       */
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
		else if (validChannelName(recipient))
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

	std::string name = _clients.getNick(clientFd);
	if (message.find("unknown command") != std::string::npos)
		_server.getMsgHandler().sendMessage(clientFd, RED + message + RESET);
	else
		_server.getMsgHandler().sendMessage(clientFd,
											getFullMessage(message, name));

	return true;
}

void Commands::sendMessageChannel(std::string &recipient, std::string &message)
{
	std::map<std::string, Channel>::iterator channel = _channels.get(recipient);


	if (channel == _channels.end())
		printInfo(errorNoSuchChannel(recipient));
	else if ((channel->second.getChannelMode(Channel::NO_OUT_MSG)
		&& !_clients.getClient(_fd)->second.isInChannel(recipient))
		|| (channel->second.getChannelMode(Channel::MODERATED)
		&& !channel->second.getUserMode(_fd, Channel::CHANOP)
		&& !channel->second.getUserMode(_fd, Channel::VOICE)))
		printInfo(errorCannotSendToChan(recipient));
	else if (!sendMessage( _channels.get(recipient), message))
		printInfo(errorNoSuchChannel(recipient));
}

bool Commands::sendMessage(std::map<std::string, Channel>::iterator channel,
						   std::string &message)
{
	if (channel == _channels.end())
		return false;

	std::string name = channel->second.getName();
	if (_args[0] == PRIVMSG)
		channel->second.sendToAll(getFullMessage(message, name));
	else
		channel->second.sendToAll(message);

	return true;
}

std::string Commands::getFullMessage(const std::string &message, std::string &name)
{
	return BBLUE + _clients.getClient(_fd)->second.getFullId() + " PRIVMSG "
			+ BYELLOW + name + BPURPLE + " :" + message + RESET;
}
