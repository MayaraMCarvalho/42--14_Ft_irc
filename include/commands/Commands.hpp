/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:17:29 by macarval          #+#    #+#             */
/*   Updated: 2024/06/27 18:04:30 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <poll.h>

#include "ClientList.hpp"
#include "ChannelList.hpp"
#include "FileTransfer.hpp"
#include "Bot.hpp"
#include "Colors.hpp"
#include "numCode.hpp"

class	Channel;

# define MAX_LENGTH 30

# define ALPHA_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define NUM_SET "0123456789_"
# define ALPHA_NUM_SET ALPHA_SET NUM_SET

# define PASS "PASS"
# define NICK "NICK"
# define USER "USER"
# define JOIN "JOIN"
# define PART "PART"
# define PRIVMSG "PRIVMSG"
# define KICK "KICK"
# define INVITE "INVITE"
# define TOPIC "TOPIC"
# define MODE "MODE"
# define QUIT "QUIT"

class Commands
{
	private:
		std::vector<std::string>	_args;
		ClientList					&_clients;
		ChannelList					&_channels;
		const int					_fd;
		const std::string			&_serverPass;

	public:
	// Constructor & Destructor ===============================================
		Commands( ClientList &clients, ChannelList &channels,
			int fd, const std::string &pass);
		~Commands( void );

	// Exceptions =============================================================

	// Getters ================================================================

	// Setters ================================================================

	// Methods ================================================================

		// Commands.cpp
		bool		isCommand(const std::string &message);
		void		commandKick( void );
		void		commandInvite( void );
		void		commandTopic( void );
		void		commandMode( void );
		void		commandQuit( void );
		void		quitServer( void );
		std::string	getClientMessage( void );

		// channelCommands.cpp
		void		commandJoin( void );
		void		commandPart( void );

		// messagesCommands.cpp
		void		commandPrivMsg( void );
		bool		sendMessage(int clientFd, const std::string &message);
		bool		sendMessage(std::map<std::string, Channel>::iterator channel, std::string &message);
		std::string	getFullMessage(const std::string &message);

		// setupCommands.cpp
		void		commandPass( void );
		void		commandNick( void );
		void		saveNick(std::string &nick);
		void		commandUser( void );
		void		saveUser(std::string &user);

		// utils.cpp
		void		parsingArgs(const std::string &message);
		std::string	getMessage( int index );
		std::string	codeToString(t_numCode code);
		std::string	intToString(int num);
		void		printError(const std::string &errorMessage);

		// validations.cpp
		bool		initialVerify(size_t num, const std::string &usage);
		bool		getErrors( void );
		bool		validArg(std::string &arg);
		bool		validChannel(std::string &channel);
		bool		validMessage(std::string &message);
};

#endif
