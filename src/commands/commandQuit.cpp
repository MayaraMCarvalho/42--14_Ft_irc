/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandQuit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:42:49 by macarval          #+#    #+#             */
/*   Updated: 2024/08/21 15:02:11 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Colors.hpp"
#include "IrcServer.hpp"

void Commands::commandQuit( void )
{
	if (initValidation(1))
	{
		std::string	messageQuit = "";

		if(getQuitMessage(messageQuit))
		{
			for (std::map<std::string, Channel>::iterator it = _channels.begin();
				it != _channels.end(); ++it)
			{
				if (it->second.userIsInChannel(_fd))
					it->second.sendToAll(_clients.getClient(_fd)->second.getFullId(),
										messageQuit);
			}
			quitServer();
		}
	}
}

void Commands::quitServer( void )
{
	std::set<std::string>	list = _clients.getClient(_fd)->second.getChannelList();

	for (std::set<std::string>::const_iterator it = list.begin();
			it != list.end(); ++it)
		_channels.part(_fd, *it);

	_server.disconnectClient(_fd);
	_server.getLogger().info(RED + "Client disconnected: " +
		BYELLOW + itoa(_fd) + RESET);
}

bool Commands::getQuitMessage(std::string &messageQuit)
{
	if (_args.size() > 1)
	{
		std::string message = getMessage(1);
		if (!validMessage(message))
			return false;
		messageQuit = " QUIT: "+  message;
	}
	return true;
}
