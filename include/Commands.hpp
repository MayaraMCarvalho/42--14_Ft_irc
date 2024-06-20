/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:17:29 by macarval          #+#    #+#             */
/*   Updated: 2024/06/20 17:37:29 by macarval         ###   ########.fr       */
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

# define MAX_LENGTH 30

# define ALPHA_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define NUM_SET "0123456789_"
# define ALPHA_NUM_SET ALPHA_SET NUM_SET

# define NICK "NICK"
# define USER "USER"
# define JOIN "JOIN"
# define PART "PART"
# define PRIVMSG "PRIVMSG"

class Commands
{
	private:
		std::vector<std::string>	_args;
		ClientList					&_clients;
		int							_fd;

	public:
	// Constructor & Destructor ===============================================
		Commands( ClientList &clients, int fd );
		~Commands( void );

	// Exceptions =============================================================

	// Getters ================================================================

	// Setters ================================================================

	// Methods ================================================================
		bool		isCommand(const std::string &message);
		void		parsingArgs(const std::string &message);

		void		commandNick( void );
		void		commandUser( void );
		void		commandJoin( void );
		void		commandPart( void );
		void		commandPrivMsg( void );

		bool		validationsArg(std::string &arg);

		void		save(std::string &nick);
		void		save(std::string &user, std::string &host);
};

#endif
