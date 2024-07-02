/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:18:22 by macarval          #+#    #+#             */
/*   Updated: 2024/07/01 13:36:05 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::verifyChannel(std::string &channelName)
{
	if (_channels.get(channelName) == _channels.end())
	{
		printError(RED + "Error "+ codeToStr(ERR_NOSUCHCHANNEL) +
			":Channel not found\n" + RESET);
	}
	else if (_args[0] != JOIN &&
		!_clients.getClient(_fd)->second.isInChannel(channelName))
	{
		printError(RED + "Error "+ codeToStr(ERR_NOTONCHANNEL) +
			":You're not on that channel\n" + RESET);
	}
	else
		return true;
	return false;
}
