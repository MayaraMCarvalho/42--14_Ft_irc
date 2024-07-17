/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientList.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:30:27 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/07 16:24:33 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_LIST_HPP
# define CLIENT_LIST_HPP

# include <map>
# include "./Client.hpp"
# include <stdexcept>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "../numCode.hpp"

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
		t_numCode updateNick(int fd, std::string &newNick);
		t_numCode updateUser(int fd, std::string &newUser);

		static bool isValidNick(std::string nick);
		static bool isValidUser(std::string user);
		static bool isSpecialChar(char ch);

	private:
		std::map<int, Client> _clients;
		std::map<std::string, std::map<int, Client>::iterator> _userToClient;
		std::map<std::string, std::map<int, Client>::iterator> _nickToClient;
};

#endif
