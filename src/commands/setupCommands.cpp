/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupCommands.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:51:34 by macarval          #+#    #+#             */
/*   Updated: 2024/06/28 14:25:11 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandPass( void )
{
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (_args.size() != 2)
	{
		printError(RED + "Error: Number of invalid arguments\n" +
			"PASS <password>\n" + RESET);
	}
	else if (it->second.getStatus() == Client::REGISTERED)
	{
		printError(RED + "Error " + codeToString(ERR_ALREADYREGISTERED) +
			": Client has already been registered\n" + RESET);
	}
	else
	{
		std::string pass = _args[1];
		if (pass == _serverPass)
		{
			it->second.setStatus(Client::AUTHENTICATED);
			printError(GREEN + "Your access has been approved!\n" + RESET);
		}
		else
			printError(RED + "Error: Password incorrect\r\n" + RESET);
	}
}

void Commands::commandNick( void )
{
	if (initialVerify(2, "NICK <new_nickname>\n"))
	{
		std::string nick = _args[1];
		if (!validArg(nick))
			return ;

		std::map<int, Client>::iterator exists = _clients.getClientByNick(nick);
		if (exists == _clients.end())
			saveNick(nick);
		else
		{
			printError(RED + "Error " + codeToString(ERR_NICKCOLLISION) +
				": Nickname already exists\n" + RESET);
		}
	}
}

void Commands::saveNick(std::string &nick)
{
	std::string message;
	t_numCode errorCode = NO_CODE;

	errorCode = _clients.setNick(_fd, nick);
	message = GREEN + "Nickname saved successfully!\n" + RESET;
	if (errorCode != NO_CODE)
		message = RED + "Error " + codeToString(errorCode) + "\n" + RESET;

	printError(message);
}


void Commands::commandUser( void )
{
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (initialVerify(2, "USER <user> ...\n"))
	{
		std::string user = _args[1];

		if (!validArg(user))
			return ;

		if (it->second.getStatus() != Client::REGISTERED)
			saveUser(user);
		else
		{
			printError(RED + "Error " + codeToString(ERR_ALREADYREGISTERED) +
				": Client has already been registered\n" + RESET);
		}
	}
}

void Commands::saveUser(std::string &user)
{
	t_numCode errorCode = NO_CODE;
	std::string message;

	errorCode = _clients.setUser(_fd, user);

	message = GREEN + "User saved successfully!\n" + RESET;
	if (errorCode != NO_CODE)
		message = RED + "Error " + codeToString(errorCode) + "\n" + RESET;

	printError(message);
}
