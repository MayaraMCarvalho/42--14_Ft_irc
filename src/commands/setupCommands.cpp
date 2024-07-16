/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupCommands.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:51:34 by macarval          #+#    #+#             */
/*   Updated: 2024/07/16 19:23:51 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandPass( void )
{
	Client	&client = _clients.getClient(_fd)->second;

	if (_args.size() != 2)
		printInfo(errorNeedMoreParams("Not enough parameters"));
	else if (client.getStatus() == Client::REGISTERED)
		printInfo(errorAlredyRegister());
	else
	{
		std::string	pass = _args[1];

		if (pass != _serverPass)
			printInfo(errorPassMismatch());
		else if (client.getStatus() == Client::CONNECTED)
		{
			client.setStatus(Client::AUTHENTICATED);
			printInfo(GREEN + _args[0] +
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
		t_numCode	errorCode = NO_CODE;

		if (exist != _clients.end())
			printInfo(errorNicknameInUse(nick));
		else
		{
			errorCode = _clients.setNick(_fd, nick);
			if (errorCode == NO_CODE)
				printInfo(GREEN + ":NICK " + nick + RESET);
			else
				printInfo(RED + toString(errorCode) + RESET);
		}
	}
}

void Commands::commandUser( void )
{
	if (initValidation(5))
	{
		std::string	user = _args[1];
		std::string	userName = getMessage(4);

		if (!validArg(user) || !validMessage(userName))
			return ;

		int	status = _clients.getClient(_fd)->second.getStatus();
		if (status == Client::REGISTERED)
			printInfo(errorAlredyRegister());
		else if (status == Client::GOT_NICK)
			saveUser(user, userName);
		else
			printInfo(errorNotRegistered());
	}
}

void Commands::saveUser(std::string &user, std::string &userName)
{
	t_numCode	errorCode = NO_CODE;
	Client &client = _clients.getClient(_fd)->second;

	errorCode = _clients.setUser(_fd, user);
	if (errorCode == NO_CODE)
	{
		client.setUserHost(_args[2]);
		client.setUserServer(_args[3]);
		client.setUserName(userName);
		printInfo(getWelcome(client));
	}
	else
		printInfo(RED + toString(errorCode) + RESET);
}
