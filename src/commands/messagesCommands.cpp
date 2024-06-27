/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messagesCommands.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:40:49 by macarval          #+#    #+#             */
/*   Updated: 2024/06/27 18:04:19 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "IrcServer.hpp"

void Commands::commandPrivMsg( void )
{
	if (initialVerify(3, "PRIVMSG <recipient> :<message>\n"))
	{
		std::string recipient = _args[1];
		std::string message = getMessage(2);
		bool isChannel = validChannel(recipient);

		if (!validArg(recipient) || !validMessage(message))
			return ;

		if (!isChannel)
		{
			if (!sendMessage(_clients.getFDByNick(recipient), message))
				printError(RED + "Error: User not found\n" + RESET);
		}
		else
		{
			if (!sendMessage( _channels.get(recipient), message))
				printError(RED + "Error: channel not found\n" + RESET);
		}
	}
}

bool Commands::sendMessage(int clientFd, const std::string &message)
{
	if (clientFd == -1)
		return false;

	IRCServer::sendMessage(clientFd, getFullMessage(message));

	return true;
}

bool Commands::sendMessage(std::map<std::string, Channel>::iterator channel, std::string &message)
{
	if (channel == _channels.end())
		return false;

	channel->second.sendToAll(getFullMessage(message));

	return true;
}

std::string Commands::getFullMessage(const std::string &message)
{
	return BBLUE + "Message received from " +
		BYELLOW + _clients.getNick(_fd) + BPURPLE +
		"\n" + message + RESET;
}
