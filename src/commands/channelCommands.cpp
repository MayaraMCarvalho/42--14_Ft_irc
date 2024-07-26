/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelCommands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:02:58 by macarval          #+#    #+#             */
/*   Updated: 2024/07/26 16:56:56 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandJoin( void )
{
	if (validSetup() && validSetup() && initValidation(2))
	{
		std::vector<std::string> channels;
		std::string	key = "";
		std::string	channel;

		if (_args.size() > 2)
			key = _args[2];

		parsingArgs(_args[1], ',', channels);

		for (std::vector<std::string>::const_iterator it = channels.begin();
			it != channels.end(); ++it)
		{
			channel = *it;
			if (validChannelName(channel) && validArg(channel)
				&& verifyJoin(channel, key))
			{
				_channels.join(_fd, channel, key);
				printJoin(channel);
			}
		}
	}
}

void Commands::printJoin(std::string &channelName)
{
	Client client = _clients.getClient(_fd)->second;
	std::string message = BGREEN + client.getFullId() + " " + _args[0]
						+ BYELLOW + " " + channelName + RESET;

	sendMessage(_channels.get(channelName), message);

	printInfo(getTopic(channelName));
	printInfo(getNamReply(channelName));
	printInfo(getEndOfNames(channelName));
}

void Commands::commandPart( void )
{
	if (validSetup() && initValidation(2))
	{
		std::vector<std::string> channels;
		std::string	message = "";
		std::string	info = BGREEN + _clients.getClient(_fd)->second.getFullId()
				+ " PART" + BYELLOW + " " ;

		if (_args.size() > 2)
			message = getMessage(2);

		if (!message.empty() && !validMessage(message))
			return ;

		parsingArgs(_args[1], ',', channels);

		for (std::vector<std::string>::const_iterator it = channels.begin();
			it != channels.end(); ++it)
		{
			std::string channel = *it;
			applyPart(channel, info, message);
		}
	}
}

void Commands::applyPart(std::string &channel, std::string &info,
						 std::string &message)
{
	if (validChannelName(channel) && validArg(channel)
		&& verifyChannel(channel))
	{
		std::string fullInfo = info;

		_channels.part(_fd, channel);
		fullInfo += channel;

		if (!message.empty())
			fullInfo += PURPLE + " :" + message;
		fullInfo += RESET;

		sendMessage(_channels.get(channel), fullInfo);
	}
}

void Commands::commandKick( void )
{
	if (validSetup() && initValidation(3))
	{
		std::string	channel = _args[1];
		std::string	user = _args[2];

		if (_args.size() > 3)
			std::string	comment = getMessage(3);

		if (validArg(user) && validChannelName(channel) && validArg(channel)
			&& verifyChannel(channel) && verifyChanOp(channel))
		{
			_channels.part(_clients.getFDByUser(user), channel);
			printInfo(PURPLE + "The user " + BYELLOW + user +
				PURPLE + " have been removed from the channel " +
				BYELLOW + channel + PURPLE + " by the operator " +
				BYELLOW + _clients.getUser(_fd) + "!" + RESET);// Verificar
		}
	}
}

void Commands::commandTopic( void )
{
	if (validSetup() && initValidation(2))
	{
		std::string	channelName = _args[1];
		std::string	topic = "";

		if (validArg(channelName)&& validChannelName(channelName)
			&& verifyChannel(channelName))
		{
			if (_args.size() > 2)
			{
				topic = getMessage(2);
				if (verifyChanOp(channelName) && validMessage(topic))
					_channels.get(channelName)->second.setTopic(topic);
			}
			else
				printInfo(getTopic(channelName));
		}
	}
}
