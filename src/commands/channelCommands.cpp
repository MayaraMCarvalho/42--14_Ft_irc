/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelCommands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:02:58 by macarval          #+#    #+#             */
/*   Updated: 2024/07/01 14:26:47 by macarval         ###   ########.fr       */
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
			if (!validArg(channel) || !verifyChannel(channel))
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

bool Commands::verifyJoin(std::string &channelName, std::string &key)
{
	Channel channel = (_channels.get(channelName))->second;
	Client client = (_clients.getClient(_fd))->second;//
	std::string error = "\n" + channelName + " :Cannot join channel ";

	if (false)// TO DO
	{
		printError(RED + "Error "+ codeToStr(ERR_BANNEDFROMCHAN) +
			error + "(+b)\n" + RESET);
	}
	else if (channel.getChannelModeFlags() == Channel::INVITEONLY &&
		!channel.userHasInvite(client.getNick()))
	{
		printError(RED + "Error "+ codeToStr(ERR_INVITEONLYCHAN) +
			error + "(+i)\n" + RESET);
	}
	else if (channel.getKey() != key)
	{
		printError(RED + "Error "+ codeToStr(ERR_BADCHANNELKEY) +
			error + "(+k)\n" + RESET);
	}
	else if (false)// TO DO
	{
		printError(RED + "Error "+ codeToStr(ERR_CHANNELISFULL) +
			error + "(+l)\n" + RESET);
	}
	else if (false)// TO DO
	{
		printError(RED + "Error "+ codeToStr(ERR_TOOMANYCHANNELS) +
			"\n" + channelName + " :You have joined too many channels\n" + RESET);
	}
	else
		return true;
	return false;
}

void Commands::commandPart( void )
{
	if (initialVerify(2, "PART <#channel_name>\n"))
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
