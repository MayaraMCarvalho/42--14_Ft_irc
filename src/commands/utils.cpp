/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:29:02 by macarval          #+#    #+#             */
/*   Updated: 2024/07/11 02:30:06 by gmachado         ###   ########.fr       */
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

void Commands::printInfo(const std::string &info)
{
	_clients.getClient(_fd)->second.sendMessage(info);
	std::cout << info << std::endl;
}

void Commands::strToUpper(std::string &str) {
	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
		*it = std::toupper(*it);
}
