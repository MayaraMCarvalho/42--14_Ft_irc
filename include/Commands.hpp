/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:17:29 by macarval          #+#    #+#             */
/*   Updated: 2024/06/20 15:14:53 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <sstream>
# include <map>
# include <vector>

# include "../include/Colors.hpp"
# include "../include/ClientList.hpp"
# include "../include/Client.hpp"

# define NICKNAME_MAX_LENGTH 20
# define ALPHA_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define NUM_SET "0123456789"
# define ALPHA_NUM_SET ALPHA_SET NUM_SET

class Commands
{
	private:
		std::vector<std::string>	_args;

	public:
	// Constructor & Destructor ===============================================
		Commands( void );
		~Commands( void );
	// Exceptions =============================================================

	// Getters ================================================================

	// Setters ================================================================

	// Methods ================================================================
		bool		isCommand(const std::string &message, int client_fd, ClientList &_clients);
		void		parsingArgs(const std::string &message);
		void		commandNick(int client_fd, ClientList &_clients);
		bool		validationsNick(std::string nick, int client_fd, ClientList &_clients);
		void		commandUser(int client_fd, ClientList &_clients);
		void		commandJoin(int client_fd, ClientList &_clients);
		void		commandPart(int client_fd, ClientList &_clients);
		void		commandPrivMsg(int client_fd, ClientList &_clients);
};

#endif
