/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:18:22 by macarval          #+#    #+#             */
/*   Updated: 2024/07/16 16:21:26 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::verifyChannel(std::string &channelName)
{
	if (_channels.get(channelName) == _channels.end())
		printInfo(errorNoSuchChannel(channelName));
	else if (!_clients.getClient(_fd)->second.isInChannel(channelName))
		printInfo(errorNotOnChannel(channelName));
	else
		return true;
	return false;
}

bool Commands::verifyJoin(std::string &channelName, std::string &key)
{
	std::string	nick = _clients.getNick(_fd);
	std::map<std::string, Channel>::iterator it = _channels.get(channelName);
	int	numChannels = _clients.getClient(_fd)->second.getChannelList().size();

	if (it != _channels.end())
	{
		int	limit = it->second.getUserLimit();
		if (limit > -1 && numChannels >= limit)
		{
			printInfo(RED + toString(ERR_TOOMANYCHANNELS) + " " + nick +
				" " + channelName + " :You have joined too many channels" + RESET);
			return false;
		}
		else
			return verifyJoinChannel(channelName, key);
	}
	return true;
}

bool Commands::verifyJoinChannel(std::string &channelName, std::string &key)
{
	std::string	nick = _clients.getNick(_fd);
	std::string	error =  " " + nick + " " + channelName
						+ " :Cannot join channel ";
	Channel		channel = _channels.get(channelName)->second;
	int	numClients = channel.getNumUsers();


	if (false)// TO DO
		printInfo(RED + toString(ERR_BANNEDFROMCHAN) + error + "(+b)" + RESET);
	else if (channel.getChannelModeFlags() == Channel::INVITEONLY &&
		!channel.userHasInvite(nick))
		printInfo(RED + toString(ERR_INVITEONLYCHAN) + error + "(+i)" + RESET);
	else if (channel.getKey() != key)
		printInfo(RED + toString(ERR_BADCHANNELKEY) + error + "(+k)" + RESET);
	else if (channel.getUserLimit() > -1 && numClients >= channel.getUserLimit())
		printInfo(RED + toString(ERR_CHANNELISFULL) + error + "(+l)" + RESET);
	else
		return true;
	return false;
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

