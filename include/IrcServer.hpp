/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:40:10 by macarval          #+#    #+#             */
/*   Updated: 2024/06/21 09:06:34 by macarval         ###   ########.fr       */
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
#include "../include/ClientList.hpp"
#include "../include/ChannelList.hpp"
#include "../include/FileTransfer.hpp"
#include "../include/Bot.hpp"
#include "../include/Colors.hpp"

class	Channel;

class IRCServer
{
	private:
		std::string						_port;
		std::string						_password;
		int 							_serverFd;
		std::vector<struct pollfd>		_pollFds;
		FileTransfer 					_fileTransfer;
		Bot 							_bot;

		ClientList						_clients;
		ChannelList						_channels;

		void handleFileTransfer(int clientFd, const std::string &command);

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
		void		handleClientMessage(int clientFd);
		void		removeClient(int clientFd);
		static void	sendMessage(int clientFd, const std::string &message);
		static void	signalHandler(int signal);
		static void	setupSignalHandlers(void);
};

#endif
