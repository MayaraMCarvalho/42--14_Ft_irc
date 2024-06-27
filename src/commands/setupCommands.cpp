/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupCommands.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:51:34 by macarval          #+#    #+#             */
/*   Updated: 2024/06/27 17:40:52 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandPass( void )
{
	std::string message;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (_args.size() != 2)
	{
		message = RED + "Error: Number of invalid arguments\n" +
			"PASS <password>\n" + RESET;
	}
	else if (it->second.getStatus() == Client::REGISTERED)
	{
		message = RED + "Error " + codeToString(ERR_ALREADYREGISTERED) +
			": Client has already been registered\n" + RESET;
	}
	else
	{
		std::string pass = _args[1];
		if (pass == _serverPass)
		{
			it->second.setStatus(Client::AUTHENTICATED);
			message = GREEN + "Your access has been approved!\n" + RESET;
		}
		else
			message = RED + "Error: Password incorrect\r\n" + RESET;
	}
	it->second.sendMessage(message);
	std::cout << message << std::endl;
}

void Commands::commandNick( void )
{
	std::string error;

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
			error = RED + "Error " + codeToString(ERR_NICKCOLLISION) +
				": Nickname already exists\n" + RESET;
			printError(error);
		}
	}
}

void Commands::saveNick(std::string &nick)
{
	t_numCode errorCode = NO_CODE;
	std::string message;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	errorCode = _clients.setNick(_fd, nick);

	message = GREEN + "Nickname update successfully: " +
		BYELLOW + it->second.getNick() + "\n" + RESET;
	if (errorCode != NO_CODE)
		message = RED + "Error " + codeToString(errorCode) + "\n" + RESET;

	it->second.sendMessage(message);
	std::cout << message << std::endl;
}


void Commands::commandUser( void )
{
	std::string error;
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
			error = RED + "Error " + codeToString(ERR_ALREADYREGISTERED) +
				": Client has already been registered\n" + RESET;
			printError(error);
		}
	}
}

void Commands::saveUser(std::string &user)
{
	t_numCode errorCode = NO_CODE;
	std::string message;

	errorCode = _clients.setUser(_fd, user);

	message = GREEN + "User update successfully!\n" + RESET;
	if (errorCode != NO_CODE)
		message = RED + "Error " + codeToString(errorCode) + "\n" + RESET;

	printError(message);
}
