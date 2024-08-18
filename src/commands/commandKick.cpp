/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandKick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:09:33 by macarval          #+#    #+#             */
/*   Updated: 2024/08/18 17:00:27 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

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

void Commands::applyKick(std::string &channel, std::string &user,
						 std::string &comment)
{
	if (validArg(user) && validChannelName(channel) && validArg(channel)
		&& verifyChannel(channel) && verifyChanOp(channel))
	{
		std::map<int, Client>::iterator it = _clients.getClientByUser(user);

		if (it == _clients.end() || !it->second.isInChannel(channel))
			printInfo(errorUserNotInChannel(user, channel));
		else
		{
			std::string message = PURPLE + " KICK " + BYELLOW + channel
						+ " " + user + BBLUE + " " + comment + RESET;
			std::string from = _clients.getClient(_fd)->second.getFullId();
			sendMessage(_channels.get(channel), message, from);
			_channels.part(_clients.getFDByUser(user), channel);
		}
	}
}
