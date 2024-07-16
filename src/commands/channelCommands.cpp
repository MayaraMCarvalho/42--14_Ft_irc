/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelCommands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:02:58 by macarval          #+#    #+#             */
/*   Updated: 2024/07/05 16:31:30 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandJoin( void )
{
	if (initValidation(2))
	{
		std::string	channel = _args[1];
		std::string	key = "";

		if (_args.size() > 2)
			key = _args[2];

		if (validChannelName(channel) && validArg(channel)
			&& verifyJoin(channel, key))
		{
			_channels.join(_fd, channel, key);
			printJoin(channel);
		}
	}
}

void Commands::printJoin(std::string channelName)
{
	std::string nick = _clients.getNick(_fd);
	std::string message = ":" + nick + "!" + _clients.getUser(_fd) + "@" +
		_clients.getHost(_fd) + " " + _args[0] + " :#" + channelName + "";
	std::string topic = getTopic(channelName);

	sendMessage(_channels.get(channelName), message);
	if (!topic.empty())
		printInfo(topic);
	printInfo(getUsersInChannel(channelName));
	printInfo(CYAN + toString(RPL_ENDOFNAMES) + " " + nick
		+ " " + channelName + " :End of /NAMES list." + RESET);
}

void Commands::commandPart( void )
{
	if (initValidation(2))
	{
		std::string channel = _args[1];

		if (validChannelName(channel) && validArg(channel)
			&& verifyChannel(channel))
		{
			_channels.part(_fd, channel);
			printInfo(GREEN + "User successfully part the channel " +
				channel + "!" + RESET);
		}
	}
}

void Commands::commandKick( void )
{
	if (initValidation(3))
	{
		std::string	channel = _args[1];
		std::string	user = _args[2];

		if (_args.size() > 3)
			std::string	comment = getMessage(3);

		if (validChannelName(channel) && validArg(channel) &&
			validArg(user) && verifyChannel(channel) && verifyKick(channel))
		{
			_channels.part(_clients.getFDByUser(user), channel);
			printInfo(PURPLE + "The user " + BYELLOW + user +
				PURPLE + " have been removed from the channel " +
				BYELLOW + channel + PURPLE + "by the operator " +
				BYELLOW + _clients.getUser(_fd) + "!" + RESET);
		}
	}
}
