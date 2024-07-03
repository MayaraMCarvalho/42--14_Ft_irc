/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:29:02 by macarval          #+#    #+#             */
/*   Updated: 2024/07/02 18:19:35 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string Commands::getMessage(int index)
{
	std::string	result;

	for (std::vector<std::string>::const_iterator it = _args.begin() + index;
			it != _args.end(); ++it)
	{
		if (it != _args.begin() + index)
			result.append(" ");
		result.append(*it);
	}
	return result;
}

std::string Commands::toString(t_numCode code)
{
	std::ostringstream	oss;

	oss << static_cast<int>(code);
	return oss.str();
}

std::string Commands::toString(int num)
{
	std::ostringstream	oss;

	oss << static_cast<int>(num);
	return oss.str();
}

void Commands::printError(const std::string &errorMessage)
{
	_clients.getClient(_fd)->second.sendMessage(errorMessage);
	std::cout << errorMessage << std::endl;
}
