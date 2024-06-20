/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:58:05 by macarval          #+#    #+#             */
/*   Updated: 2024/06/20 17:36:28 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::validationsArg(std::string &arg)
{
	std::map<int, Client>::iterator it = _clients.getClientByNick(arg);
	std::string message = "";

	if (arg.size() > MAX_LENGTH)
		message = RED + "Error: Too long\n" + RESET;
	else if (!(arg.find_first_not_of(ALPHA_NUM_SET) == std::string::npos))
		message = RED + "Error: Prohibited characters found\n" + RESET;
	else if (_args[0] == NICK && it != _clients.end())
		message = RED + "Error: Nickname already exists\n" + RESET;
	else
		return true;

	it = _clients.getClient(_fd);
	it->second.sendMessage(message);
	std::cout << message << std::endl;

	return false;
}
