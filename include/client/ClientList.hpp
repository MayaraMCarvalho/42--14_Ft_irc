/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientList.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:30:27 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/16 18:30:34 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_LIST_HPP
# define CLIENT_LIST_HPP

#include <map>
#include "Client.hpp"

class ClientList {
	public:
		ClientList(void);
		ClientList(ClientList &src);

		~ClientList(void);

		ClientList &operator=(ClientList &src);

		// Getters
		std::map<int, Client>::iterator getClient(int fd);
		std::map<int, Client>::iterator getClientByNick(std::string nick);
		std::map<int, Client>::iterator getClientByUser(std::string user);
		std::string getNick(int fd);
		std::string getUser(int fd);
		int getFDByNick(std::string &nick);
		int getFDByUser(std::string &user);
		std::map<int, Client>::iterator end(void);

		// Setters
		void setNick(int fd, std::string &nick);
		void setUser(int fd, std::string &user);

		void add(Client &client);
		void add(int fd, struct in_addr *address);
		void add(int fd, std::string &host);
		void remove(int fd);
		void removeByNick(std::string &nick);
		void removeByUser(std::string &user);
		void updateNick(int fd, std::string &newNick);
		void updateUser(int fd, std::string &newUser);

	private:
		std::map<int, Client> _clients;
		std::map<std::string, std::map<int, Client>::iterator> _userToClient;
		std::map<std::string, std::map<int, Client>::iterator> _nickToClient;
};

#endif
