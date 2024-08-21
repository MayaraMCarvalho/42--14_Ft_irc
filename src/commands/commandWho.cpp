/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandWho.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:31:40 by macarval          #+#    #+#             */
/*   Updated: 2024/08/21 18:03:14 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandWho( void )
{
	if (validSetup() && initValidation(1))
	{
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
					std::string channelName = "*";
					printInfo(getWhoReply(who, channelName));
					printInfo(getEndOfWho(channelName));
				}
			}
		}
	}
}

void Commands::commandWhoChannel(std::string &channelName)
{
	if (validChannelName(channelName) && verifyChannel(channelName))
	{
		Channel channel = _channels.get(channelName)->second;
		for (std::map<int, int>::iterator it = channel.usersBegin();
				it != channel.usersEnd(); ++it)
		{
			std::string nick = _clients.getNick(it->first);
			printInfo(getWhoReply(nick, channelName));
		}
		printInfo(getEndOfWho(channelName));
	}
}
