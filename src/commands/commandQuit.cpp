/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandQuit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:42:49 by macarval          #+#    #+#             */
/*   Updated: 2024/07/04 15:17:57 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "IrcServer.hpp"

void Commands::commandQuit( void )
{
	if (initValidation(1))
	{
		std::string	messageQuit = "";
		std::string	prefix = RED + "Client " + BYELLOW + toString(_fd)
			+ RED + " left the channel ";

		if(getQuitMessage(messageQuit))
		{
			for (std::map<std::string, Channel>::iterator it = _channels.begin();
				it != _channels.end(); ++it)
			{
				if (it->second.userIsInChannel(_fd))
					it->second.sendToAll(prefix + BCYAN + it->second.getName()
						+ messageQuit);
			}
			quitServer();
		}
	}
}

void Commands::quitServer( void )
{
	_clients.removeClientFD(_fd);
	_channels.partDisconnectedClient(_fd);
	std::cout << RED << "Client disconnected: ";
	std::cout << BYELLOW << _fd << RESET << std::endl;
}

bool Commands::getQuitMessage(std::string &messageQuit)
{
	if (_args.size() > 1)
	{
		std::string message = getMessage(1);
		if (!validMessage(message))
			return false;
		messageQuit = BLUE + " And sent the following farewell message: "
			+ BGREEN + message + RESET;
	}
	return true;
}
