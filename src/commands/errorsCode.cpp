/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorsCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:30:03 by macarval          #+#    #+#             */
/*   Updated: 2024/07/04 16:44:16 by macarval         ###   ########.fr       */
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
	return (RED + toString(ERR_ALREADYREGISTERED) +
			+ " " + _clients.getNick(_fd) + " :You may not reregister" + RESET);
}
