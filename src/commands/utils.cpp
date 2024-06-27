/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:29:02 by macarval          #+#    #+#             */
/*   Updated: 2024/06/27 17:40:04 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
void Commands::parsingArgs(const std::string &message)
{
	std::string token;
	std::istringstream tokenStream(message);

	while (std::getline(tokenStream, token, ' '))
		_args.push_back(token);
}

std::string Commands::getMessage( int index )
{
	std::string result;

	for (std::vector<std::string>::const_iterator it = _args.begin() + index;
			it != _args.end(); ++it)
	{
		if (it != _args.begin() + index)
			result.append(" ");
		result.append(*it);
	}
	return result;
}


std::string Commands::codeToString(t_numCode code)
{
	std::ostringstream oss;

	oss << static_cast<int>(code);

	return oss.str();
}

std::string Commands::intToString(int num)
{
	std::ostringstream oss;

	oss << static_cast<int>(num);

	return oss.str();
}

void Commands::printError(const std::string &errorMessage)
{
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	it->second.sendMessage(errorMessage);
	std::cout << errorMessage << std::endl;
}
