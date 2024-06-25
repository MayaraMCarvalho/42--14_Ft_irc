/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:29:02 by macarval          #+#    #+#             */
/*   Updated: 2024/06/25 15:11:04 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string Commands::getMessage( void )
{
	std::string result;

	for (std::vector<std::string>::const_iterator it = _args.begin() + 2;
			it != _args.end(); ++it)
	{
		if (it != _args.begin() + 2)
			result.append(" ");
		result.append(*it);
	}
	return result;
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

bool Commands::sendMessage(int clientFd, const std::string &message)
{
	ssize_t	nbytes;

	if (clientFd == -1)
		return false;

	std::string fullMessage = BBLUE + "Message received from " +
		BYELLOW + _clients.getNick(_fd) + BPURPLE +
		"\n" + message + "\n" + RESET;

	nbytes = write(clientFd, fullMessage.c_str(), fullMessage.length());
	if (nbytes < 0)
	{
		std::cerr << RED << "Write error on client " << clientFd << std::endl;
		std::cout << RESET;
	}
	return true;
}

bool Commands::sendMessage(std::map<std::string, Channel>::iterator channel, std::string &message)
{
	if (channel == _channels.end())
		return false;

	std::string fullMessage = BBLUE + "Message received from " +
		BYELLOW + _clients.getNick(_fd) + BPURPLE +
		"\n" + message + "\n" + RESET;
	channel->second.sendToAll(fullMessage);
	return true;
}
