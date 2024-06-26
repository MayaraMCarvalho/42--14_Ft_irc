/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:25:52 by macarval          #+#    #+#             */
/*   Updated: 2024/06/26 17:49:09 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::initialVerify(std::string &message, size_t num, std::string usage)
{
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (_args.size() < num) // verificar se melhor usar !=
	{
		message = RED + "Error " + codeToString(ERR_NEEDMOREPARAMS) +
			": Number of invalid arguments\n" + usage + RESET;
	}
	else if (_args[0] != QUIT)
	{
		bool isUser = (_args[0] == USER);
		bool isNick = (_args[0] == NICK);
		int status = it->second.getStatus();
		bool isAuth = (status == Client::AUTHENTICATED);
		bool isGotNick = (status == Client::GOT_NICK);
		bool isGotUser = (status == Client::GOT_USER);
		bool isReg = (status == Client::REGISTERED);

		if ((isUser || isNick) && !isAuth && !isGotNick && !isGotUser && !isReg)
			message = RED + "Error: Unauthenticated client\n" + RESET;
		else if ((!isAuth && !isReg)
			&& ((isUser && !isGotNick) || (isNick && !isGotUser)))
			message = RED + "Error: Registration must be completed\n" + RESET;
		else if (!isUser && !isNick && !isReg)
			message = RED + "Error: You need to register the client first\n" + RESET;
		else
			return true;
	}
	else
		return true;
	return false;
}

bool Commands::validArg(std::string &arg)
{
	std::map<int, Client>::iterator it = _clients.getClientByNick(arg);
	std::string error = "";

	if (arg.empty())
		error = RED + "Error: Empty parameter\n" + RESET;
	else if (arg.size() > MAX_LENGTH)
		error = RED + "Error: Too long\n" + RESET;
	else if (!(arg.find_first_not_of(ALPHA_NUM_SET) == std::string::npos))
		error = RED + "Error: Prohibited characters found\n" + RESET;
	else if (_args[0] == NICK && it != _clients.end())
	{
		error = RED + "Error " + codeToString(ERR_NICKCOLLISION) +
			": Nickname already exists\n" + RESET;
	}
	else
		return true;

	it = _clients.getClient(_fd);
	it->second.sendMessage(error);
	std::cout << error << std::endl;

	return false;
}

bool Commands::validChannel(std::string &channel, std::string &error)
{
	if (!channel.empty())
	{
		if (channel[0] != '#')
		{
			error = RED + "Error: Non-standard channel name\n" + RESET;
			return false;
		}
		else
			channel.erase(0, 1);
	}
	return true;
}

bool Commands::validMessage(std::string &message)
{
	std::string error = "";
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (!message.empty())
	{
		if (message[0] != ':')
			error = RED + "Error: Non-standard message\n" + RESET;
		else
		{
			message.erase(0, 1);
			return true;
		}
	}
	it->second.sendMessage(error);
	std::cout << error << std::endl;

	return false;
}
