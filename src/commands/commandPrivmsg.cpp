/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandPrivmsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:40:49 by macarval          #+#    #+#             */
/*   Updated: 2024/07/22 13:24:37 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "IrcServer.hpp"

void Commands::commandPrivMsg( void )
{
	if (initValidation(3))
	{
		std::string recipient = _args[1];
		std::string message = getMessage(2);
		bool isChannel = validChannelName(recipient);

		if (!validArg(recipient) || !validMessage(message))
			return ;

		if (!isChannel)
		{
			if (!sendMessage(_clients.getFDByNick(recipient), message))
				printInfo(errorNoSuchNick(recipient));
		}
		else if (!sendMessage( _channels.get(recipient), message))
				printInfo(errorNoSuchChannel(recipient));
		else if (false) // Acrescentar: Enviado para um usuário que (a) não está em um canal que esteja no modo +n ou (b) não é um chanop (ou modo +v) em um canal que tem o modo +m definido
			printInfo(errorCannotSendToChan(recipient));
	}
}

bool Commands::sendMessage(int clientFd, const std::string &message)
{
	if (clientFd == -1)
		return false;

	_server.getMsgHandler().sendMessage(clientFd, getFullMessage(message));

	return true;
}

bool Commands::sendMessage(std::map<std::string, Channel>::iterator channel,
						   std::string &message)
{
	if (channel == _channels.end())
		return false;

	channel->second.sendToAll(getFullMessage(message));

	return true;
}

std::string Commands::getFullMessage(const std::string &message)
{
	return BBLUE + "Message received from " +
		BYELLOW + _clients.getNick(_fd) + BPURPLE + message + RESET;
}
