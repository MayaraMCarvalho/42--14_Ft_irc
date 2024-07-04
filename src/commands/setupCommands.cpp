/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupCommands.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:51:34 by macarval          #+#    #+#             */
/*   Updated: 2024/07/04 16:34:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandPass( void )
{
	Client	&client = _clients.getClient(_fd)->second;

	if (_args.size() != 2)
		printError(errorNeedMoreParams("Not enough parameters"));
	else if (client.getStatus() == Client::REGISTERED)
		printError(errorAlredyRegister());
	else
	{
		std::string	pass = _args[1];

		if (pass != _serverPass)
			printError(RED + toString(ERR_PASSWDMISMATCH)
				+ " * :Password incorrect" + RESET);
		else
		{
			client.setStatus(Client::AUTHENTICATED);
			printError(GREEN + _args[0] +
				": Your access has been approved!" + RESET);//Retirar?
		}

	}
}

void Commands::commandNick( void )
{
	if (initValidation(2))
	{
		std::string	nick = _args[1];

		if (!validArg(nick))
			return ;

		std::map<int, Client>::iterator	exist = _clients.getClientByNick(nick);
		if (exist != _clients.end())
		{
			printError(RED + toString(ERR_NICKNAMEINUSE) + " " +
				nick + " :Nickname is already in use" + RESET);
		}
		else
			saveNick(nick);

	}
}

void Commands::saveNick(std::string &nick)
{
	std::string	message;
	t_numCode	errorCode = NO_CODE;

	errorCode = _clients.setNick(_fd, nick);
	message = GREEN + ":" + _args[0] + " " + nick + RESET;
	if (errorCode != NO_CODE)
		message = RED + toString(errorCode) + RESET;
	printError(message);
}

void Commands::commandUser( void )
{
	if (initValidation(5))
	{
		std::string	user = _args[1];
		std::string	userName = getMessage(4);

		if (!validArg(user) || !validMessage(userName))
			return ;
		if (_clients.getClient(_fd)->second.getStatus() == Client::REGISTERED)
			printError(errorAlredyRegister());
		else
			saveUser(user, userName);
	}
}

void Commands::saveUser(std::string &user, std::string &userName)
{
	std::string	message;
	t_numCode	errorCode = NO_CODE;

	errorCode = _clients.setUser(_fd, user);
	Client client = _clients.getClient(_fd)->second;
	if (errorCode == NO_CODE)
	{
		message = GREEN + "001 " + user + " :Welcome to the IRC server" + RESET;
		client.setUserHost(_args[2]);
		client.setUserServer(_args[3]);
		client.setUserName(userName);
	}
	else
		message = RED + toString(errorCode) + RESET;
	printError(message);
}
