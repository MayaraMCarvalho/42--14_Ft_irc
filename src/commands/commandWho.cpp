/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandWho.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:31:40 by macarval          #+#    #+#             */
/*   Updated: 2024/08/22 09:44:23 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandWho( void )
{
	if (validSetup() && initValidation(1))
	{
		std::string channelName = "*";
		if (_args.size() > 1)
		{
			std::string	who = _args[1];
			bool		isChannel = isItChannel(who);

			if (isChannel)
				commandWhoChannel(who);
			else
			{
				if (validArg(who) && verifyNick(who))
				{
					printInfo(getWhoReply(who, channelName));
					printInfo(getEndOfWho(channelName));
				}
			}
		}
		else
			printListWho(channelName);
	}
}

void Commands::commandWhoChannel(std::string &channelName)
{
	if (validChannelName(channelName) && verifyChannel(channelName))
	{
		Channel &channel = _channels.get(channelName)->second;
		for (std::map<int, int>::iterator it = channel.usersBegin();
				it != channel.usersEnd(); ++it)
		{
			std::string nick = _clients.getNick(it->first);
			printInfo(getWhoReply(nick, channelName));
		}
		printInfo(getEndOfWho(channelName));
	}
}

void Commands::printListWho(std::string &channelName)
{
	for(std::map<int, Client>::iterator it = _clients.begin();
		it != _clients.end(); ++it)
	{
		std::string nick = it->second.getNick();
		channelName = "*";
		std::set<std::string> list = it->second.getChannelList();
		if (!list.empty())
		{
			for(std::set<std::string>::iterator channel = list.begin();
				channel != list.end(); ++channel)
			{
				channelName = *channel;
				printInfo(getWhoReply(nick, channelName));
			}
		}
		else
			printInfo(getWhoReply(nick, channelName));

	}
	printInfo(getEndOfWho(channelName));
}
