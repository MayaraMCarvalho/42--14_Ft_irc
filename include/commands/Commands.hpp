/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:17:29 by macarval          #+#    #+#             */
/*   Updated: 2024/06/21 11:03:55 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <sstream>
# include <map>
# include <vector>
# include <unistd.h>

# include "Colors.hpp"
# include "ClientList.hpp"
# include "ChannelList.hpp"
# include "Client.hpp"

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
		ChannelList					&_channels;
		int							_fd;

	public:
	// Constructor & Destructor ===============================================
		Commands( ClientList &clients, ChannelList &channels, int fd );
		~Commands( void );

	// Exceptions =============================================================

	// Getters ================================================================

	// Setters ================================================================

	// Methods ================================================================
		bool		isCommand(const std::string &message);
		void		parsingArgs(const std::string &message);

		// Commands.cpp
		void		commandNick( void );
		void		commandUser( void );
		void		commandJoin( void );
		void		commandPart( void );
		void		commandPrivMsg( void );

		// validations.cpp
		bool		initialVerify(std::string &error, size_t num, std::string usage);
		bool		validArg(std::string &arg);
		bool		validChannel(std::string &channel, std::string &error);
		bool		validMessage(std::string &message);

		// utils.cpp
		std::string	getMessage( void );
		void		save(std::string &nick);
		void		save(std::string &user, std::string &host);
		bool		sendMessage(int clientFd, const std::string &message);
		bool		sendMessage(std::map<std::string, Channel>::iterator channel, std::string &message);
};

#endif
