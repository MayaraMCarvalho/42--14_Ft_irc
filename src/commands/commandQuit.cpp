/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandQuit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:42:49 by macarval          #+#    #+#             */
/*   Updated: 2024/08/05 10:42:56 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
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
					it->second.sendToAll(BYELLOW +
					_clients.getClient(_fd)->second.getFullId() + messageQuit);
			}
			quitServer();
		}
	}
}

void Commands::quitServer( void )
{
	_server.disconnectClient(_fd);
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
		messageQuit = BLUE + " QUIT: "
			+ BGREEN + message + RESET;
	}
	return true;
}
