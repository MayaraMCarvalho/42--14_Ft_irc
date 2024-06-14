/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:40:10 by macarval          #+#    #+#             */
/*   Updated: 2024/06/14 16:45:27 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

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
#include <map>
#include "../include/Client.hpp"
// #include "../include/Channel.hpp"
#include "../include/FileTransfer.hpp"
#include "../include/Bot.hpp"
#include "../include/Commands.hpp"

class	Channel;

class IRCServer
{
	private:
		std::string						_port;
		std::string						_password;
		int 							_server_fd;
		std::map<int, Client>			_clients;
		std::map<std::string, Channel>	_channels;
		std::vector<struct pollfd>		_poll_fds;
		FileTransfer 					_file_transfer;
		Bot 							_bot;

		void handleFileTransfer(int client_fd, const std::string &command);

	public:
	// Constructor & Destructor ===============================================
		IRCServer( void );
		~IRCServer( void );

	// Exceptions =============================================================

	// Getters ================================================================

	// Setters ================================================================

	// Methods ================================================================
		IRCServer(const std::string &port, const std::string &password);
		void		setupServer(void);
		void		run(void);
		void		acceptNewClient(void);
		void		handleClientMessage(int client_fd);
		void		removeClient(int client_fd);
		void		sendMessage(int client_fd, const std::string &message);
		static void	signalHandler(int signal);
		static void	setupSignalHandlers(void);
};

#include "Channel.hpp"

#endif
