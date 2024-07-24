/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:59:16 by macarval          #+#    #+#             */
/*   Updated: 2024/07/05 11:27:20 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string Commands::getTopic(std::string &channelName)
{
	// if (topic)
	return (CYAN + toString(RPL_TOPIC) + " " + _clients.getNick(_fd)
		+ " #" + channelName + " :Print topic se houver" + RESET);
	// else
	// 	return "";
}

std::string Commands::getUsersInChannel(std::string &channelName)
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
		+ " = #" + channelName + " :" + listUsers + "" + RESET);
}
