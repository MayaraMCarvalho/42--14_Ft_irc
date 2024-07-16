/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorsCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:30:03 by macarval          #+#    #+#             */
/*   Updated: 2024/07/05 16:43:18 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string Commands::errorNeedMoreParams(std::string suffix)
{
	return (RED + toString(ERR_NEEDMOREPARAMS) + " " + _clients.getNick(_fd)
		+ " " + _args[0] + " :" + suffix + RESET);
}

std::string Commands::errorNoSuchNick(std::string &recipient, std::string who)
{
	return (RED + toString(ERR_NOSUCHNICK) +
		recipient + ":No such " + who + RESET);
}

std::string Commands::errorAlredyRegister( void )
{
	return (RED + toString(ERR_ALREADYREGISTERED) + " " +
		_clients.getNick(_fd) + " :You may not reregister" + RESET);
}

std::string Commands::errorNotOnChannel(std::string &channelName)
{
	return (RED + toString(ERR_NOTONCHANNEL) + " " + _clients.getNick(_fd) +
			+ " " + channelName + ":You're not on that channel" + RESET);
}

std::string Commands::errorNoSuchChannel(std::string &channelName)
{
	return (RED + toString(ERR_NOSUCHCHANNEL) + " " + _clients.getNick(_fd) +
			+ " " + channelName + ":No such channel" + RESET);
}

std::string Commands::errorCannotSendToChan(std::string &channelName)
{
	return (RED + toString(ERR_CANNOTSENDTOCHAN) + " " + _clients.getNick(_fd) +
			+ " " + channelName + ":Cannot send to channel" + RESET);
}
