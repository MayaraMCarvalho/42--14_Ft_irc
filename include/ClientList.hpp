/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientList.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:30:27 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/13 05:04:54 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_LIST_HPP
# define CLIENT_LIST_HPP

#include <map>
#include "Client.hpp"

class ClientList
{
	public:
		ClientList(void);
		ClientList(ClientList &src);

		~ClientList(void);

		ClientList &operator=(ClientList &src);

		// Getters
		Client *getClient(int fd);
		Client *getClientByNick(std::string nick);
		Client *getClientByUser(std::string user);
		std::string getNick(int fd);
		std::string getUser(int fd);
		int getFDByNick(std::string nick);
		int getFDByUser(std::string user);

		// Setters
		void setNick(int fd, std::string nick);
		void setUser(int fd, std::string user);

		void add(int fd, std::string host);
		void remove(int fd);
		void removeByNick(std::string nick);
		void removeByUser(std::string user);

	private:
		std::map<int, Client> _clients;
		std::map<std::string, int> _userToFD;
		std::map<std::string, int> _nickToFD;
};

#endif
