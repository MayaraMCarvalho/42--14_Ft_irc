/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandJoin.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:02:58 by macarval          #+#    #+#             */
/*   Updated: 2024/08/18 16:59:50 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandJoin( void )
{
	if (validSetup() && initValidation(2))
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
	std::string message = BGREEN + _args[0]
						+ BYELLOW + " " + channelName + RESET;
	std::string from = client.getFullId();

	sendMessage(_channels.get(channelName), message, from);

	printInfo(getTopic(channelName));
	printInfo(getNamReply(channelName));
	printInfo(getEndOfNames(channelName));
}
