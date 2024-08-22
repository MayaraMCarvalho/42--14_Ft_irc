/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:19:18 by macarval          #+#    #+#             */
/*   Updated: 2024/08/22 00:22:33 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "IrcServer.hpp"

void Commands::commandMode( void )
{
	if (validSetup() && initValidation(2))
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
			printInfo(getChannelModeIs(_channels.get(channelName)->second));
		else
		{
			std::string	mode = _args[2];
			char		signal = mode[0];
			size_t		index = 3;

			if (verifyMode(mode, channelName, "+-aioOvklmnpqst")
				&& verifyChanOp(channelName))
			{
				Channel &channel = _channels.get(channelName)->second;
				for (std::string::const_iterator it = mode.begin() + 1;
					it != mode.end(); ++it)
					applyMode(channelName, std::string(1, signal) + *it, index);

				std::string message = _args[0] + " " + channelName + " " +
						getChannelFlags(channel.getChannelModeFlags(), channel);

				std::string from = _clients.getClient(_fd)->second.getFullId();

				sendMessage(_channels.get(channelName), message, from);
			}
		}
	}
}

void Commands::applyMode(std::string &channelName, std::string mode,
						 size_t &index)
{
	Channel	&channel = _channels.get(channelName)->second;

	if (mode.find_first_not_of("+-oOvkl") != std::string::npos)
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

void Commands::commandModeUser(std::string &nick)
{
	if (validArg(nick) && verifyNick(nick))
	{
		if (_args.size() < 3)
			printInfo(getUserModeIs(_clients.getClientByNick(nick)->second));
		else
		{
			std::string	mode = _args[2];
			char		signal = mode[0];

			if (verifyMode(mode, nick, "+-aiwroOs"))
			{
				Client &user = _clients.getClientByNick(nick)->second;
				for (std::string::const_iterator it = mode.begin() + 1; it != mode.end(); ++it)
					user.setMode(std::string(1, signal) + *it);

				Client client = _clients.getClient(_fd)->second;
				std::string message = _args[0] + " " + nick + " " + mode;
				std::string from = client.getFullId();
				_server.getMsgHandler().sendMessage(_fd, from, message);
				if (client.getNick() != nick)
					_server.getMsgHandler().sendMessage(user.getFD(), from, message);
			}
		}
	}
}
