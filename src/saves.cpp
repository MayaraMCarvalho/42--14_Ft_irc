/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saves.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:29:02 by macarval          #+#    #+#             */
/*   Updated: 2024/06/20 17:34:47 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::saveNick(std::string &nick)
{
	std::string message;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	_clients.setNick(_fd, nick);
	_clients.updateNick(_fd, nick);

	message = GREEN + "Nickname update successfully: "
		+ it->second.getNick() + "\n" + RESET;
	it->second.sendMessage(message);
	std::cout << message << std::endl;
}

void Commands::saveUser(std::string &user, std::string &host)
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
