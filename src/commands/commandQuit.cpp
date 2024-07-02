/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandQuit.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:42:49 by macarval          #+#    #+#             */
/*   Updated: 2024/07/01 13:23:27 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "IrcServer.hpp"

void Commands::commandQuit( void )
{
	if (initialVerify(1, "QUIT <message(optional)>\n"))
	{
		std::string message = RED + "Client " + BYELLOW + intToString(_fd)
			+ RED + " left the channel ";

		for (std::map<std::string, Channel>::iterator it = _channels.begin();
			it != _channels.end(); ++it)
		{
			if (it->second.userIsInChannel(_fd))
				it->second.sendToAll(message + BCYAN + it->second.getName()
					+ RESET + getQuitMessage());
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
