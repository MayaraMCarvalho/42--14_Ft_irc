/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandPart.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:10:50 by macarval          #+#    #+#             */
/*   Updated: 2024/08/05 10:11:03 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

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
			fullInfo += " :" + message;

		sendMessage(_channels.get(channel), fullInfo);
	}
}
