/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:25:52 by macarval          #+#    #+#             */
/*   Updated: 2024/07/04 17:07:45 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::initValidation(size_t numArgs)
{
	std::string	error;

	if (_args.size() < numArgs) // verificar se melhor usar !=
	{
		error = errorNeedMoreParams("Not enough parameters");
		if (_args[0] == NICK)
			error = toString(ERR_NONICKNAMEGIVEN) +
				": No nickname given";
		else if (_args[0] == PRIVMSG)
		{
			error = toString(ERR_NOTEXTTOSEND) + ": No text to send";
			if (_args.size() < 2)
				error = toString(ERR_NORECIPIENT) +
					": No recipient given (" + _args[0] + ")";
		}
		printError(RED + error + RESET);
		return false;
	}
	else if (_args[0] != QUIT && setupDone())
		return false;
	return true;
}

bool Commands::setupDone(void)
{
	bool	isUser = (_args[0] == USER);
	bool	isNick = (_args[0] == NICK);
	int		status = _clients.getClient(_fd)->second.getStatus();
	bool	isAuth = (status == Client::AUTHENTICATED);
	bool	isGotNick = (status == Client::GOT_NICK);
	bool	isGotUser = (status == Client::GOT_USER);
	bool	isReg = (status == Client::REGISTERED);

	if ((isUser || isNick) && !isAuth && !isGotNick && !isGotUser && !isReg)
		printError(RED + "Error: Unauthenticated client" + RESET);
	else if ((!isAuth && !isReg)
		&& ((isUser && !isGotNick) || (isNick && !isGotUser)))
		printError(RED + "Error: Registration must be completed" + RESET);
	else if (!isUser && !isNick && !isReg)
		printError(RED + "Error: You need to register the client first" + RESET);
	else
		return false;
	return true;

}

bool Commands::validArg(std::string &arg)
{
	std::string	error;

	if (arg.empty())
		printError(RED + "Error: Empty parameter" + RESET);
	else if (arg.size() > MAX_LENGTH)
		printError(RED + "Error: Too long" + RESET);
	else if (!(arg.find_first_not_of(ALPHA_NUM_SET) == std::string::npos))
	{
		if (_args[0] == NICK)
			error = RED + toString(ERR_ERRONEUSNICKNAME) +
			arg + ": Erroneus nickname" + RESET;
		else
			error = RED + "Error: Prohibited characters found" + RESET;
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
			printError(RED + toString(ERR_NOSUCHCHANNEL) + " " +
			_clients.getNick(_fd) + " " +  channel + " :No such channel" + RESET);
		return false;
	}
	else
		channel.erase(0, 1);
	return true;
}

bool Commands::validMessage(std::string &message)
{
	std::string	error = "";

	if (message[0] != ':')
	{
		printError(RED + "Error: Non-standard message" + RESET);
		return false;
	}
	message.erase(0, 1);
	return true;
}
