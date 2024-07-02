/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorsCode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:30:03 by macarval          #+#    #+#             */
/*   Updated: 2024/07/02 10:24:34 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string Commands::codeToStr(t_numCode code)
{
	std::ostringstream oss;

	oss << static_cast<int>(code);

	return oss.str();
}

std::string Commands::errorNeedMoreParams(std::string suffix)
{
	return (RED + "Error " + codeToStr(ERR_NEEDMOREPARAMS) +
		"\n" + _args[0] + ": " + suffix + RESET);
}

std::string Commands::errorNoSuchNick(std::string &recipient, std::string who)
{
	return (RED + "Error " + codeToStr(ERR_NOSUCHNICK) +
		"\n" + recipient + ":No such " + who + " \n" + RESET);
}

std::string Commands::errorAlredyRegister( void )
{
	return (RED + "Error " + codeToStr(ERR_ALREADYREGISTERED) +
			"\nYou may not reregister\n" + RESET);
}
