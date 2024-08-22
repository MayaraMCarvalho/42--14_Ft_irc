/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandInvite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:23:08 by macarval          #+#    #+#             */
/*   Updated: 2024/08/22 12:20:04 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandInvite( void )
{
	if (validSetup() && initValidation(3))
	{
		std::string	nick = _args[1];
		std::string	channelName = _args[2];

		if (validArg(channelName) && validChannelName(channelName)
			&& verifyChannel(channelName) && verifyChanOp(channelName)
			&& validArg(nick) && verifyInvite(nick, channelName))
		{
			_channels.get(channelName)->second.addInvite(nick);
			printInfo(getInviting(nick, channelName));
			sendInviting(nick, channelName);
		}
	}
}

void Commands::sendInviting(std::string &nick, std::string &channelName)
{
	std::string	info;

	info = " INVITE " + nick + " " + channelName;

	_clients.getClientByNick(nick)->second.sendMessage(_clients.getClient(_fd)->second.getFullId(), info);
}
