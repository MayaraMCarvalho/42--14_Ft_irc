/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:25:52 by macarval          #+#    #+#             */
/*   Updated: 2024/06/28 16:59:20 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::initialVerify(size_t num, const std::string &usage)
{
	std::string error;
	if (_args.size() < num) // verificar se melhor usar !=
	{
		error = RED + "Error " + codeToString(ERR_NEEDMOREPARAMS) +
			"\n" + _args[0] + ": Not enough parameters\n" + "Usage: " + usage + RESET;
		if (_args[0] == NICK)
			error = RED + "Error " + codeToString(ERR_NONICKNAMEGIVEN) +
			"\n: No nickname given\n" + "Usage: " + usage + RESET;
		printError(error);
		return false;
	}
	else if (_args[0] != QUIT && getErrors())
		return false;
	else
		return true;
}

bool Commands::getErrors(void)
{
	std::map<int, Client>::iterator it = _clients.getClient(_fd);
	bool isUser = (_args[0] == USER);
	bool isNick = (_args[0] == NICK);
	int status = it->second.getStatus();
	bool isAuth = (status == Client::AUTHENTICATED);
	bool isGotNick = (status == Client::GOT_NICK);
	bool isGotUser = (status == Client::GOT_USER);
	bool isReg = (status == Client::REGISTERED);

	if ((isUser || isNick) && !isAuth && !isGotNick && !isGotUser && !isReg)
		printError(RED + "Error: Unauthenticated client\n" + RESET);
	else if ((!isAuth && !isReg)
		&& ((isUser && !isGotNick) || (isNick && !isGotUser)))
		printError(RED + "Error: Registration must be completed\n" + RESET);
	else if (!isUser && !isNick && !isReg)
		printError(RED + "Error: You need to register the client first\n" + RESET);
	else
		return false;
	return true;

}

bool Commands::validArg(std::string &arg)
{
	std::string error;

	if (arg.empty())
		printError(RED + "Error: Empty parameter\n" + RESET);
	else if (arg.size() > MAX_LENGTH)
		printError(RED + "Error: Too long\n" + RESET);
	else if (!(arg.find_first_not_of(ALPHA_NUM_SET) == std::string::npos))
	{
		if (_args[0] == NICK)
		{
			error = RED + "Error " + codeToString(ERR_NEEDMOREPARAMS) +
			"\n" + _args[0] + ": Erroneus nickname\n" + RESET;
		}
		else
			error = RED + "Error: Prohibited characters found\n" + RESET;
		printError(error);
	}
	else
		return true;

	return false;
}

bool Commands::validChannel(std::string &channel)
{
	if (channel[0] != '#')
	{
		if (_args[0] != PRIVMSG)
			printError(RED + "Error: Non-standard channel name\n" + RESET);
		return false;
	}
	else
		channel.erase(0, 1);
	return true;
}

bool Commands::validMessage(std::string &message)
{
	std::string error = "";

	if (message[0] != ':')
	{
		printError(RED + "Error: Non-standard message\n" + RESET);
		return false;
	}
	else
		message.erase(0, 1);
	return true;
}
