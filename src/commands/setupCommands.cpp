/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupCommands.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:51:34 by macarval          #+#    #+#             */
/*   Updated: 2024/07/02 10:25:02 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandPass( void )
{
	Client client = _clients.getClient(_fd)->second;

	if (_args.size() != 2)
	{
		printError(
			errorNeedMoreParams("Not enough parameters\nUsage: PASS <password>\n"));
	}
	else if (client.getStatus() == Client::REGISTERED)
		printError(errorAlredyRegister());
	else
	{
		std::string pass = _args[1];
		if (pass == _serverPass)
		{
			client.setStatus(Client::AUTHENTICATED);
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
			printError(RED + "Error " + codeToStr(ERR_NICKNAMEINUSE) +
				"\n" + _args[0] + ": Nickname is already in use\n" + RESET);
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
		message = RED + "Error " + codeToStr(errorCode) + "\n" + RESET;

	printError(message);
}

void Commands::commandUser( void )
{
	if (initialVerify(2, "USER <user> ...\n"))
	{
		std::string user = _args[1];

		if (!validArg(user))
			return ;

		if (_clients.getClient(_fd)->second.getStatus() != Client::REGISTERED)
			saveUser(user);
		else
			printError(errorAlredyRegister());
	}
}

void Commands::saveUser(std::string &user)
{
	t_numCode errorCode = NO_CODE;
	std::string message;

	errorCode = _clients.setUser(_fd, user);

	message = GREEN + "User saved successfully!\n" + RESET;
	if (errorCode != NO_CODE)
		message = RED + "Error " + codeToStr(errorCode) + "\n" + RESET;

	printError(message);
}
