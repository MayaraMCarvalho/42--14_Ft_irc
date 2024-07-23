/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:18:22 by macarval          #+#    #+#             */
/*   Updated: 2024/07/02 16:32:09 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::verifyChannel(std::string &channelName)
{
	if (_channels.get(channelName) == _channels.end())
	{
		printError(RED + "Error "+ toString(ERR_NOSUCHCHANNEL) +
			":Channel not found\n" + RESET);
	}
	else if (_args[0] != JOIN &&
		!_clients.getClient(_fd)->second.isInChannel(channelName))
	{
		printError(RED + "Error "+ toString(ERR_NOTONCHANNEL) +
			":You're not on that channel\n" + RESET);
	}
	else
		return true;
	return false;
}

bool Commands::verifyJoin(std::string &channelName, std::string &key)
{
	Channel		channel = (_channels.get(channelName))->second;
	Client		client = (_clients.getClient(_fd))->second;
	std::string	error = "\n" + channelName + " :Cannot join channel ";

	if (false)// TO DO
	{
		printError(RED + "Error "+ toString(ERR_BANNEDFROMCHAN) +
			error + "(+b)\n" + RESET);
	}
	else if (channel.getChannelModeFlags() == Channel::INVITEONLY &&
		!channel.userHasInvite(client.getNick()))
	{
		printError(RED + "Error "+ toString(ERR_INVITEONLYCHAN) +
			error + "(+i)\n" + RESET);
	}
	else if (channel.getKey() != key)
	{
		printError(RED + "Error "+ toString(ERR_BADCHANNELKEY) +
			error + "(+k)\n" + RESET);
	}
	else if (false)// TO DO
	{
		printError(RED + "Error "+ toString(ERR_CHANNELISFULL) +
			error + "(+l)\n" + RESET);
	}
	else if (false)// TO DO
	{
		printError(RED + "Error "+ toString(ERR_TOOMANYCHANNELS) +
			"\n" + channelName + " :You have joined too many channels\n" + RESET);
	}
	else
		return true;
	return false;
}

bool Commands::verifyKick (std::string &channel)
{
	if (!_clients.getClient(_fd)->second.getMode(Client::OPERATOR))
	{
		printError(RED + "Error " + toString(ERR_CHANOPRIVSNEEDED) +
			": #" + channel + ":You're not channel operator\n" + RESET);
		return false;
	}
	return true;
}

