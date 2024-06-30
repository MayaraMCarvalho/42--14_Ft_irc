/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:02:17 by lucperei          #+#    #+#             */
/*   Updated: 2024/05/25 11:34:41 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bot.hpp"

// Constructor ================================================================
Bot::Bot() {}

Bot::Bot(const std::string &name) : _name(name) {}

// Methods ====================================================================
void Bot::respondToMessage(int clientFd, const std::string &message)
{
	std::string response = _name + ": I received your message: " + message;
	sendMessage(clientFd, response);
}

void Bot::sendMessage(int clientFd, const std::string &message)
{
	std::string fullMessage = message + "\r\n";
	ssize_t nbytes = send(clientFd, fullMessage.c_str(), fullMessage.length(), 0);

	if (nbytes < 0)
		std::cerr << "Error writing to client " << clientFd << std::endl;
}
