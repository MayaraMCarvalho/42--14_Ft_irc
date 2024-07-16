/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:18:22 by macarval          #+#    #+#             */
/*   Updated: 2024/07/16 19:06:36 by macarval         ###   ########.fr       */
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
	Client client = _clients.getClient(_fd)->second;
	std::map<std::string, Channel>::iterator it = _channels.get(channelName);
	int	numChannels = client.getChannelList().size();

	if (it != _channels.end())
	{
		int	limit = it->second.getUserLimit();
		if (limit > -1 && numChannels >= limit)
		{
			printInfo(errorTooManyChannels(channelName));
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
	Channel		channel = _channels.get(channelName)->second;
	int			numClients = channel.getNumUsers();

	if (false)// TO DO
		printInfo(errorBannedFromChan(nick, channelName));
	else if (channel.getChannelModeFlags() == Channel::INVITEONLY &&
		!channel.userHasInvite(nick))
		printInfo(errorInviteOnlyChan(nick, channelName));
	else if (channel.getKey() != key)
		printInfo(errorBadChannelKey(nick, channelName));
	else if (channel.getUserLimit() > -1 && numClients >= channel.getUserLimit())
		printInfo(errorChannelIsFull(nick, channelName));
	else
		return true;
	return false;
}

bool Commands::verifyKick (std::string &channelName)
{
	if (!_clients.getClient(_fd)->second.getMode(Client::OPERATOR))
	{
		printInfo(errorChanPrivsNeeded(channelName));
		return false;
	}
	return true;
}

