/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:18:22 by macarval          #+#    #+#             */
/*   Updated: 2024/07/05 10:38:21 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::verifyChannel(std::string &channelName)
{
	if (!_clients.getClient(_fd)->second.isInChannel(channelName))
	{
		printInfo(RED + toString(ERR_NOTONCHANNEL) +
			":You're not on that channel" + RESET);
	}
	else
		return true;
	return false;
}

bool Commands::verifyJoin(std::string &channelName, std::string &key)
{
	std::string	nick = _clients.getNick(_fd);

	if (false)// TO DO
	{
		printInfo(RED + toString(ERR_TOOMANYCHANNELS) + " " + nick +
			" #" + channelName + " :You have joined too many channels" + RESET);
		return false;
	}
	else if (_channels.get(channelName) != _channels.end())
	{
		Channel		channel = (_channels.get(channelName))->second;
		std::string	error = nick + " #" + channelName + " :Cannot join channel ";

		if (false)// TO DO
		{
			printInfo(RED + toString(ERR_BANNEDFROMCHAN) + " " +
				error + "(+b)" + RESET);
		}
		else if (channel.getChannelModeFlags() == Channel::INVITEONLY &&
			!channel.userHasInvite(nick))
		{
			printInfo(RED + toString(ERR_INVITEONLYCHAN) + " " +
				error + "(+i)" + RESET);
		}
		else if (channel.getKey() != key)
		{
			printInfo(RED + toString(ERR_BADCHANNELKEY) + " " +
				error + "(+k)" + RESET);
		}
		else if (false)// TO DO
		{
			printInfo(RED + toString(ERR_CHANNELISFULL) + " " +
				error + "(+l)" + RESET);
		}
		else
			return true;
		return false;
	}
	return true;
}

bool Commands::verifyKick (std::string &channel)
{
	if (!_clients.getClient(_fd)->second.getMode(Client::OPERATOR))
	{
		printInfo(RED + toString(ERR_CHANOPRIVSNEEDED) +
			": #" + channel + ":You're not channel operator" + RESET);
		return false;
	}
	return true;
}

