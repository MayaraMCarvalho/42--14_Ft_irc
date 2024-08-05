/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelCommands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:02:58 by macarval          #+#    #+#             */
/*   Updated: 2024/08/05 10:03:47 by macarval         ###   ########.fr       */
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
		std::vector<std::string> channels;
		std::vector<std::string> users;
		std::string	comment = "";

		parsingArgs(_args[1], ',', channels);
		parsingArgs(_args[2], ',', users);

		if (_args.size() > 3)
			comment = getMessage(3);

		for (std::vector<std::string>::const_iterator it1 = channels.begin();
			it1 != channels.end(); ++it1)
		{
			std::string channel = *it1;
			for (std::vector<std::string>::const_iterator it2 = users.begin();
			it2 != users.end(); ++it2)
			{
				std::string user = *it2;
				applyKick(channel, user, comment);
			}
		}
	}
}

void Commands::applyKick(std::string &channel, std::string &user, std::string &comment)
{
	if (validArg(user) && validChannelName(channel) && validArg(channel)
		&& verifyChannel(channel) && verifyChanOp(channel))
	{
		std::map<int, Client>::iterator it = _clients.getClientByUser(user);

		if (it == _clients.end() || !it->second.isInChannel(channel))
			printInfo(errorUserNotInChannel(user, channel));
		else
		{
			std::string message = PURPLE +
						_clients.getClient(_fd)->second.getFullId()
						+ " KICK " + BYELLOW + channel + " " + user
						+ BBLUE + " " + comment + RESET;
			sendMessage(_channels.get(channel), message);
			_channels.part(_clients.getFDByUser(user), channel);
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
