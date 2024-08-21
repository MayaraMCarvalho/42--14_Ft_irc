/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:59:16 by macarval          #+#    #+#             */
/*   Updated: 2024/08/21 18:34:19 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Channel.hpp"

std::string Commands::getWelcome(Client &client)
{
	return (toString(RPL_WELCOME) + " " + client.getNick() +
			" :Welcome to IRC server " + client.getFullId());
}

std::string Commands::getYourHost(Client &client)
{
	return (toString(RPL_YOURHOST) + " " + client.getNick() +
			" :Your host is " + _host);
}

std::string Commands::getMyInfo(Client &client)
{
	int	modeFlags = client.getModeFlags();

	return (toString(RPL_MYINFO) + " " + client.getNick() +
			" " + _host + " " + getUserFlags(modeFlags));
}

std::string Commands::getUserModeIs(Client &client)
{
	int	modeFlags = client.getModeFlags();

	return (toString(RPL_UMODEIS) + " " + client.getNick()
			+ " " + getUserFlags(modeFlags));
}

std::string Commands::getChannelModeIs(Channel &channel)
{
	int	modeFlags = channel.getChannelModeFlags();

	return (toString(RPL_CHANNELMODEIS) + " " + channel.getName()
			+ " " + getChannelFlags(modeFlags, channel));

}

std::string Commands::getTopic(std::string &channelName)
{
	std::string topic = _channels.get(channelName)->second.getTopic();

	if (topic.empty())
		return (toString(RPL_NOTOPIC) + " " + _clients.getNick(_fd)
				+ " " + channelName + " :No topic is set");
	else
		return (toString(RPL_TOPIC) + " " + _clients.getNick(_fd)
				+ " " + channelName + " :" + topic);

}

std::string Commands::getInviting(std::string &nickname,
								  std::string &channelName)
{
	return (toString(RPL_INVITING) + " " + _clients.getNick(_fd)
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
		Channel::t_umode mode = static_cast<Channel::t_umode>(it->second);
		char prefix = channel.getPrefix(mode);
		if (prefix != '\0')
			listUsers.append(1, prefix);
		listUsers.append(_clients.getNick(it->first));
	}
	return (toString(RPL_NAMREPLY) + " " + _clients.getNick(_fd)
			+ " = " + channelName + " :" + listUsers);
}

std::string Commands::getEndOfNames(std::string &channelName)
{
	return (toString(RPL_ENDOFNAMES) + " " + _clients.getNick(_fd)
			+ " " + channelName + " :End of /NAMES list.");
}

std::string Commands::getWhoReply(std::string &nick, std::string &channelName)
{
	Client user = _clients.getClientByNick(nick)->second;
	
	return (toString(RPL_WHOREPLY) + " " + nick + " " + channelName + " ~"
			+ user.getNick() + " " + user.getHost() + " H" + user.getUserName());
}

std::string Commands::getEndOfWho(std::string &channelName)
{
	return (toString(RPL_ENDOFWHO) + " " + _clients.getNick(_fd)
			+ " " + channelName + " :End of /WHO list.");
}
