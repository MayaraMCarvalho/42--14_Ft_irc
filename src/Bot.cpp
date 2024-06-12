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

#include "../include/Bot.hpp"

// Constructor ================================================================
Bot::Bot() {}//
Bot::Bot(const std::string &name) : _name(name) {}

// Methods ====================================================================
void Bot::respond_to_message(int client_fd, const std::string &message)
{
	std::string response = _name + ": I received your message: " + message;
	send_message(client_fd, response);
}

void Bot::send_message(int client_fd, const std::string &message)
{
	// std::cout << "Bot sending message to client " << client_fd << ": " << message << std::endl; // Adicionando log de depura��o
	write(client_fd, message.c_str(), message.length());
}
