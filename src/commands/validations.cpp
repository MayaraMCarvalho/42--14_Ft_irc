/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:25:52 by macarval          #+#    #+#             */
/*   Updated: 2024/07/25 18:50:20 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::initValidation(size_t numArgs)
{
	std::string	error;

	if (_args.size() < numArgs)
	{
		error = errorNeedMoreParams();
		if (_args[0] == NICK)
			error = errorNoNicknameGiven();
		if (_args[0] == PRIVMSG)
		{
			error = errorNoTextToSend();
			if (_args.size() < 2)
				error = errorNoRecipient();
		}
		printInfo(error);
	}
	else if (_args.size() > numArgs && _args[0] == NICK)
		printInfo(errorErroneusNickname(_args[1]));
	else
		return true;
	return false;
}

bool Commands::validSetup(void)
{
	int		status = _clients.getClient(_fd)->second.getStatus();

	bool	isUser = (_args[0] == USER);
	bool	isNick = (_args[0] == NICK);

	bool	isAuth = (status == Client::AUTHENTICATED);
	bool	isGotNick = (status == Client::GOT_NICK);
	bool	isGotUser = (status == Client::GOT_USER);
	bool	isReg = (status == Client::REGISTERED);

	if (!isReg && ((!isUser && !isNick)
		|| (!isAuth && ((isUser && !isGotNick) || (isNick && !isGotUser)))))
		printInfo(errorNotRegistered());
	else
		return true;
	return false;

}

bool Commands::validArg(std::string &arg)
{
	std::string	error;

	if (arg.empty())
		printInfo(RED + "Error: Empty parameter" + RESET);// Verificar
	else if (arg.size() > MAX_LENGTH)
	{
		if (_args[0] == NICK)
			printInfo(errorErroneusNickname(arg));
		else
			printInfo(RED + "Error: Too long" + RESET); // VERIFICAR
	}
	else if (invalidChar(arg))
	{
		if (_args[0] == NICK)
			printInfo(errorErroneusNickname(arg));
		else
			printInfo(RED + "Error: Prohibited characters found" + RESET); // Verificar para cada comando
	}
	else
		return true;
	return false;
}

bool Commands::invalidChar(std::string &arg)
{
	if ((_args[0] == MODE || _args[0] == PRIVMSG || _args[0] == JOIN
		|| _args[0] == INVITE || _args[0] == TOPIC)
		&& (arg[0] == '#' || arg[0] == '&'))
		return false;
	if (arg.find_first_not_of(ALPHA_NUM_SET) != std::string::npos)
		return true;
	return false;
}

bool Commands::validChannelName(std::string &channel)
{
	if ((channel[0] == '#' || channel[0] == '&')
		&& channel.find_first_not_of(ALPHA_NUM_SET, 1) != std::string::npos)
		printInfo(errorBadChanMask(channel));
	else if (channel[0] != '#' && channel[0] != '&')
		printInfo(errorCannotSendToChan(channel));
	else
		return true;
	return false;
}

bool Commands::validMessage(std::string &message)
{
	std::string	error = "";

	if (message[0] != ':')
	{
		printInfo(RED + "Error: Non-standard message" + RESET);// Verificar
		return false;
	}
	message.erase(0, 1);
	return true;
}
