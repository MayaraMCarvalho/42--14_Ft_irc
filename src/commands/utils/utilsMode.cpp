/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsMode.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:24:25 by macarval          #+#    #+#             */
/*   Updated: 2024/08/05 12:12:44 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::verifyMode(std::string &mode, std::string &who,
						  std::string pattern)
{
	if (mode[0] != '+' && mode[0] != '-')
		printInfo(errorNeedMoreParams());
	else if (mode.find_first_not_of(pattern) != std::string::npos)
	{
		if (pattern == "+-aiwroOs")
			printInfo(errorerrorUModeUnknowFlag(who, mode));
		else
			printInfo(errorUnknownMode(who, mode));
	}
	else
		return true;
	return false;
}

void Commands::handleModeParameters(std::string &mode,
									std::string &channelName, size_t &index)
{
	Channel	&channel = _channels.get(channelName)->second;
	std::string	param = _args[index];

	if (mode.find_first_not_of("+-oOv") == std::string::npos)
	{
		std::map<int, Client>::iterator it = _clients.getClientByNick(param);
		if (it == _clients.end())
			printInfo(errorNoSuchNick(param));
		else if (!it->second.isInChannel(channelName))
			printInfo(errorUserNotInChannel(param, channelName));
		else
			channel.setUserMode(_clients.getFDByNick(param), mode);
	}
	else if (mode == "+k")
		handleKeyMode(channelName, param);
	else if (mode == "+l")
		channel.setUserLimit(toInt(param));
	++index;
}

void Commands::handleKeyMode(std::string &channelName, std::string &param)
{
	Channel	&channel = _channels.get(channelName)->second;

	if (channel.getKey().empty())
		channel.setKey(param);
	else
		printInfo(errorKeySet(channelName));
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
