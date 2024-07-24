/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:59:16 by macarval          #+#    #+#             */
/*   Updated: 2024/07/24 10:06:43 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string Commands::getWelcome(Client &client)
{
	return (GREEN + toString(RPL_WELCOME) + " " + client.getNick() +
			" :Welcome to IRC server " + BYELLOW + client.getFullId() + RESET);
}

std::string Commands::getUserModeIs(std::string &who) //REFAZER RETORNANDO NADA
{
	int			modeFlags;
	std::string	mode;

	if (isItChannel(who))
		modeFlags = _channels.get(who)->second.getChannelModeFlags();
	else
		modeFlags = _clients.getClientByNick(who)->second.getModeFlags();
	if (modeFlags & Client::AWAY)
		mode += "a";
	if (modeFlags & Client::INVISIBLE)
		mode += "i";
	if (modeFlags & Client::WALLOPS)
		mode += "w";
	if (modeFlags & Client::RESTRICTED)
		mode += "r";
	if (modeFlags & Client::OPERATOR)
		mode += "o";
	if (modeFlags & Client::LOCAL_OP)
		mode += "O";
	if (modeFlags & Client::RECV_NOTICES)
		mode += "s";

	return (CYAN + toString(RPL_UMODEIS) + " " + who + " "
			+ mode + RESET);
}

std::string Commands::getTopic(std::string &channelName)
{
	std::string topic = _channels.get(channelName)->second.getTopic();

	if (topic.empty())
		return (CYAN + toString(RPL_NOTOPIC) + " " + _clients.getNick(_fd)
				+ " " + channelName + " :No topic is set" + RESET);
	else
		return (CYAN + toString(RPL_TOPIC) + " " + _clients.getNick(_fd)
				+ " " + channelName + " :" + topic + RESET);

}

std::string Commands::getInviting(std::string &nickname,
								  std::string &channelName)
{
	return (CYAN + toString(RPL_INVITING) + " " + _clients.getNick(_fd)
			+ " " + nickname + " " + channelName);
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


