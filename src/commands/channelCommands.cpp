/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelCommands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:02:58 by macarval          #+#    #+#             */
/*   Updated: 2024/07/02 16:52:39 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandJoin( void )
{
	if (initValidation(2, "JOIN <#channel_name> <key (optional)>\n"))
	{
		std::string	channel = _args[1];
		std::string	key = "";

		if (_args.size() > 2)
			key = _args[2];

		if (validChannel(channel) && validArg(channel)
			&& verifyChannel(channel) && verifyJoin(channel, key))
		{
			_channels.join(_fd, channel, key);
			printError(GREEN + "User successfully join the channel " +
				channel + "!\n" + RESET);
		}
	}
}

void Commands::commandPart( void )
{
	if (initValidation(2, "PART <#channel_name>\n"))
	{
		std::string channel = _args[1];

		if (validChannel(channel) && validArg(channel) && verifyChannel(channel))
		{
			_channels.part(_fd, channel);
			printError(GREEN + "User successfully part the channel " +
				channel + "!\n" + RESET);
		}
	}
}

void Commands::commandKick( void )
{
	if (initValidation(3, "KICK <channel> <user> <comment(Optional)>\n"))
	{
		std::string	channel = _args[1];
		std::string	user = _args[2];

		if (_args.size() > 3)
			std::string	comment = getMessage(3);

		if (validChannel(channel) && validArg(channel) &&
			validArg(user) && verifyChannel(channel) && verifyKick(channel))
		{
			_channels.part(_clients.getFDByUser(user), channel);
			printError(PURPLE + "The user " + BYELLOW + user +
				PURPLE + " have been removed from the channel " +
				BYELLOW + channel + PURPLE + "by the operator " +
				BYELLOW + _clients.getUser(_fd) + "!\n" + RESET);
		}
	}
}
