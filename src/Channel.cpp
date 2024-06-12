/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:17:28 by lucperei          #+#    #+#             */
/*   Updated: 2024/05/25 21:20:27 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"
#include "../include/IrcServer.hpp"

// Constructor & Destructor ===================================================
Channel::Channel(void) {}

Channel::Channel(const std::string &name) : _name(name) {}

// Methods ====================================================================
void Channel::addClient(int client_fd)
{
	_clients.insert(client_fd);
}

void Channel::removeClient(int client_fd)
{
	_clients.erase(client_fd);
}

bool Channel::isClientInChannel(int client_fd) const
{
	return (_clients.find(client_fd) != _clients.end());
}

// void	Channel::sendToAll(int except_fd) {
/*void	Channel::sendToAll(int except_fd, const std::string &message) {
	IRCServer *server = new IRCServer("port", "password");
	int	client_fd;
	for (std::set<int>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
		client_fd = *it;
		if (client_fd != except_fd) {

			//sendMessage(client_fd, message);
			server->sendMessage(client_fd, message);
		}
	}
	delete server;
}*/

// I need to check why it is not forwarding the messages to all clients since I am specifying
void Channel::sendToAll(IRCServer *server, const std::string &message)
{
	for (std::set<int>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		int	client_fd = *it;

		server->sendMessage(client_fd, message);
	}
}
