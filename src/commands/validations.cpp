/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:25:52 by macarval          #+#    #+#             */
/*   Updated: 2024/07/16 15:49:45 by macarval         ###   ########.fr       */
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
		printInfo(RED + error + RESET);
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
		printInfo(RED + "Error: Unauthenticated client" + RESET);
	else if ((!isAuth && !isReg)
		&& ((isUser && !isGotNick) || (isNick && !isGotUser)))
		printInfo(RED + "Error: Registration must be completed" + RESET);
	else if (!isUser && !isNick && !isReg)
		printInfo(RED + "Error: You need to register the client first" + RESET);
	else
		return false;
	return true;

}

bool Commands::validArg(std::string &arg)
{
	std::string	error;

	if (arg.empty())
		printInfo(RED + "Error: Empty parameter" + RESET);
	else if (arg.size() > MAX_LENGTH)
		printInfo(RED + "Error: Too long" + RESET);
	else if (invalidChar(arg))
	{
		if (_args[0] == NICK)
			printInfo(RED + toString(ERR_ERRONEUSNICKNAME) + " * " +
			arg + " : Erroneus nickname" + RESET);
		else if (_args[0] == PRIVMSG)
			printInfo(errorCannotSendToChan(arg));
		else
			printInfo(RED + "Error: Prohibited characters found" + RESET); // Verificar para cada comando
	}
	else
		return true;
	return false;
}

bool Commands::invalidChar(std::string &arg)
{
	if ((_args[0] == INVITE || _args[0] == TOPIC || _args[0] == MODE ||
		(_args[0] == PRIVMSG && arg[0] != '#' && arg[0] != '&')) &&
		!(arg.find_first_not_of(ALPHA_NUM_SET) == std::string::npos))
			return true;
	return false;
}

bool Commands::validChannelName(std::string &channel)
{
	if ((_args[0] != PRIVMSG && channel[0] != '#' && channel[0] != '&') ||
		((channel[0] == '#' || channel[0] != '&')
		&& channel.find_first_not_of(ALPHA_NUM_SET, 1) != std::string::npos))
	{
		printInfo(RED + toString(ERR_BADCHANMASK) + " " +
		_clients.getNick(_fd) + " " + channel + " :Bad Channel Mask" + RESET);
		return false;
	}
	return true;
}

bool Commands::validMessage(std::string &message)
{
	std::string	error = "";

	if (message[0] != ':')
	{
		printInfo(RED + "Error: Non-standard message" + RESET);
		return false;
	}
	message.erase(0, 1);
	return true;
}
