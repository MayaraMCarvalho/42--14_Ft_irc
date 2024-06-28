/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelCommands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:02:58 by macarval          #+#    #+#             */
/*   Updated: 2024/06/28 09:15:53 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandJoin( void )
{
	if (initialVerify(2, "JOIN <#channel_name> <key (optional)>\n"))
	{
		std::string channel = _args[1];
		std::string key = "";

		if (_args.size() > 2)
			key = _args[2];
		if (validChannel(channel))
		{
			if (!validArg(channel))
				return ;
			else
			{
				_channels.join(_fd, channel, key);
				printError(GREEN + "User successfully join the channel " +
					channel + "!\n" + RESET);
			}
		}
	}
}

void Commands::commandPart( void )
{
	if (initialVerify(2, "PART <#channel_name>\n"))
	{
		std::string channel = _args[1];

		if (validChannel(channel))
		{
			if (!validArg(channel))
				return ;
			else
			{
				_channels.part(_fd, channel);
				printError(GREEN + "User successfully part the channel " +
					channel + "!\n" + RESET);
			}
		}
	}
}
