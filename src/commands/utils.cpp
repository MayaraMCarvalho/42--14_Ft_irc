/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:29:02 by macarval          #+#    #+#             */
/*   Updated: 2024/06/25 15:45:58 by macarval         ###   ########.fr       */
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

void Commands::save(std::string &nick)
{
	std::string message;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	_clients.setNick(_fd, nick);
	_clients.updateNick(_fd, nick);

	message = GREEN + "Nickname update successfully: " +
		BYELLOW + it->second.getNick() + "\n" + RESET;
	it->second.sendMessage(message);
	std::cout << message << std::endl;
}

void Commands::save(std::string &user, std::string &host)
{
	std::string message;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	_clients.setUser(_fd, user);
	_clients.updateUser(_fd, user);
	it->second.setHost(host);

	message = GREEN + "User update successfully!\n" + RESET;
	it->second.sendMessage(message);
	std::cout << message << std::endl;
}
