/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:19:18 by macarval          #+#    #+#             */
/*   Updated: 2024/07/24 15:55:24 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandMode( void )
{
	if (initValidation(2))
	{
		std::string	who = _args[1];
		bool		isChannel = isItChannel(who);

		if (isChannel)
			commandModeChannel(who);
		else
			commandModeUser(who);
	}
}

void Commands::commandModeChannel(std::string &channelName)
{
	if (validChannelName(channelName) && verifyChannel(channelName))
	{
		if (_args.size() < 3)
			printInfo(getUserModeIs(channelName));
		else
		{
			std::string	mode = _args[2];
			char		signal = mode[0];
			size_t		index = 3;

			if (verifyMode(mode, channelName, "+-aiklmnpqst")
				&& verifyChanOp(channelName))
			{
				Channel channel = _channels.get(channelName)->second;
				for (std::string::const_iterator it = mode.begin() + 1;
					it != mode.end(); ++it)
					applyMode(channelName, std::string(1, signal) + *it, index);
				printInfo(getUserModeIs(channelName));
			}
		}
	}
}

bool Commands::verifyMode(std::string &mode, std::string &who,
						  std::string pattern)
{
	if (mode[0] != '+' && mode[0] != '-')
		printInfo(errorNeedMoreParams());
	else if (mode.find_first_not_of(pattern) != std::string::npos)
		printInfo(errorUnknownMode(who, mode));
	else
		return true;
	return false;
}

void Commands::applyMode(std::string &channelName, std::string mode,
						 size_t &index)
{
	Channel	&channel = _channels.get(channelName)->second;

	if (mode.find_first_not_of("+-okl") != std::string::npos)
	{
		channel.setChannelMode(mode);
		return;
	}

	if (_args.size() <= index)
	{
		if (mode == "-k")
			channel.setKey("");
		else if (mode == "-l")
			channel.setUserLimit(-1);
		else
			printInfo(errorNeedMoreParams());
		return;
	}
	handleModeParameters(mode, channelName, index);
}

void Commands::handleModeParameters(std::string &mode,
									std::string &channelName, size_t &index)
{
	Channel	&channel = _channels.get(channelName)->second;
	std::string	param = _args[index];

	if (mode == "+o" || mode == "-o")
		channel.setUserMode(_clients.getFDByNick(param), mode);
	else if (mode == "+k")
		handleKeyMode(channelName, param);
	else if (mode == "+l")
		channel.setUserLimit(toInt(param));
	++index;
}

void Commands::handleKeyMode(std::string &channelName, std::string &param)
{
	Channel	&channel = _channels.get(channelName)->second;

	if (!_clients.getClientByNick(param)->second.isInChannel(channelName))
		printInfo(errorUserNotInChannel(param, channelName));
	else
	{
		if (channel.getKey().empty())
			channel.setKey(param);
		else
			printInfo(errorKeySet(channelName));
	}


	// else if (/*Tentativa de definir modos em um canal que não suporta modos*/)
	// 	printInfo(ERR_NOCHANMODES);//
	// else
	// 	return true;
}

void Commands::commandModeUser(std::string &nick)
{
	if (validArg(nick) && verifyNick(nick))
	{
		if (_args.size() < 3)
			printInfo(getUserModeIs(nick));
		else
		{
			std::string	mode = _args[2];
			char		signal = mode[0];

			if (verifyMode(mode, nick, "+-aiwroOs"))
			{
				Client client = _clients.getClientByNick(nick)->second;
				for (std::string::const_iterator it = mode.begin() + 1; it != mode.end(); ++it)
					client.setMode(std::string(1, signal) + *it);
				printInfo(getUserModeIs(nick));
			}
		}
	}
}

bool Commands::verifyNick(std::string &nick)
{
	Client client = _clients.getClient(_fd)->second;

	if (_clients.getClientByNick(nick) == _clients.end())
		printInfo(errorNoSuchNick(nick));
	else if (nick != client.getNick()
			 && !client.getMode(Client::OPERATOR))
		printInfo(errorUsersDontMatch());
	else
		return true;
	return false;
}



// 	// //
// 	// else if (/* */)
// 	// 	printInfo();//
// 	// else if (/* */)
// 	// 	printInfo();//
// 	// else if (/* */)
// 	// 	printInfo();//
// 	else
// 		return true;
// 	return false;
