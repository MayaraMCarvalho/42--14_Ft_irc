/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:25:21 by lucperei          #+#    #+#             */
/*   Updated: 2024/05/25 21:19:17 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <algorithm>
#include <string>
#include <set>
#include "../include/IrcServer.hpp"

class	IRCServer;

class	Channel
{
	private:
		std::string		_name;
		std::set<int>	_clients;

	public:
	// Constructor & Destructor ===============================================
		Channel(void);
		Channel(const std::string &name);

	// Methods ================================================================
		void	addClient(int client_fd);
		void	removeClient(int client_fd);
		bool	isClientInChannel(int client_fd) const;
		void	sendToAll(IRCServer *server, const std::string &message);
};

#endif
