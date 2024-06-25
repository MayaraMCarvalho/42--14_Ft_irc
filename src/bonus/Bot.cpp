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
	// std::cout << "Bot sending message to client " << clientFd << ": " << message << std::endl; // Adicionando log de depura��o
	std::string fullMessage = message + "\n";
	write(clientFd, fullMessage.c_str(), fullMessage.length());
}
