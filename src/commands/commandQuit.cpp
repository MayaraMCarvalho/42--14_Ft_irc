/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandQuit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:42:49 by macarval          #+#    #+#             */
/*   Updated: 2024/07/02 16:39:15 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "IrcServer.hpp"

void Commands::commandQuit( void )
{
	if (initialVerify(1, "QUIT <message(optional)>\n"))
	{
		std::string prefix = RED + "Client " + BYELLOW + toString(_fd)
			+ RED + " left the channel ";
		std::string quitMessage = getQuitMessage();

		for (std::map<std::string, Channel>::iterator it = _channels.begin();
			it != _channels.end(); ++it)
		{
			if (it->second.userIsInChannel(_fd))
				it->second.sendToAll(prefix + BCYAN + it->second.getName()
					+ quitMessage);
		}
		quitServer();
	}
}

void Commands::quitServer( void )
{
	_server.removeClient(_fd);
	std::cout << RED << "Client disconnected: ";
	std::cout << BYELLOW << _fd << RESET << std::endl;
}

std::string Commands::getQuitMessage( void )
{
	std::string messageQuit = "";

	if (_args.size() > 1)
	{
		std::string message = getMessage(1);
		if (validMessage(message))
		{
			messageQuit = BLUE + "\nAnd sent the following farewell message: "
				+ BGREEN + message + RESET;
		}
	}
	return messageQuit;
}
