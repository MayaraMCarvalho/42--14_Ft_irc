/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:59:16 by macarval          #+#    #+#             */
/*   Updated: 2024/07/16 19:21:59 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string Commands::getWelcome(Client &client)
{
	return (GREEN + toString(RPL_WELCOME) + " " + client.getNick() +
		" :Welcome to IRC server " + client.getFullId() + RESET);
}

std::string Commands::getTopic(std::string &channelName)
{
	std::string topic = _channels.get(channelName)->second.getTopic();

	if (!topic.empty())
	return (CYAN + toString(RPL_TOPIC) + " " + _clients.getNick(_fd)
		+ " " + channelName + " :" + topic + RESET);
	else
		return "";
}

std::string Commands::getNamReply(std::string &channelName)
{
	Channel		channel = _channels.get(channelName)->second;
	std::string	listUsers = "";

	for (std::map<int, int>::iterator it = channel.usersBegin();
		it != channel.usersEnd(); ++it)
	{
		if (it != channel.usersBegin() && it != channel.usersEnd())
			listUsers.append(" ");
		listUsers.append(_clients.getNick(it->first));
	}
	return (CYAN + toString(RPL_NAMREPLY) + " " + _clients.getNick(_fd)
		+ " = " + channelName + " :" + listUsers + "" + RESET);
}

std::string Commands::getEndOfNames(std::string &channelName)
{
	return (CYAN + toString(RPL_ENDOFNAMES) + " " + _clients.getNick(_fd)
			+ " " + channelName + " :End of /NAMES list." + RESET);
}
