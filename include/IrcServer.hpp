/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:40:10 by macarval          #+#    #+#             */
/*   Updated: 2024/06/12 15:39:19 by macarval         ###   ########.fr       */
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

// Color codes as global variables
const std::string RESET = "\033[0m";
const std::string RED = "\033[31;1m";
const std::string GREEN = "\033[32;1m";
const std::string YELLOW = "\033[33;1m";
const std::string BLUE = "\033[34;1m";
const std::string PURPLE = "\033[35;1m";
const std::string CYAN = "\033[36;1m";
const std::string GRAY = "\033[37;1m";

class	Channel;

class IRCServer
{
	private:
		std::string						_port;
		std::string						_password;
		int 							_server_fd;
		std::map<int, Client>			_clients;
		std::map<std::string, Channel> _channels;
		std::vector<struct pollfd>		_poll_fds;
		FileTransfer 					_file_transfer;
		Bot 							_bot;
		void handle_file_transfer(int client_fd, const std::string &command);

	public:
	// Constructor & Destructor ===============================================
		IRCServer( void );
		~IRCServer( void );

	// Exceptions =============================================================

	// Getters ================================================================

	// Setters ================================================================

	// Methods ================================================================
		IRCServer(const std::string &port, const std::string &password);
		void		setup_server(void);
		void		run(void);
		void		acceptNewClient(void);
		void		handleClientMessage(int client_fd);
		void		remove_client(int client_fd);
		void		send_message(int client_fd, const std::string &message);
		static void	signalHandler(int signal);
		static void	setupSignalHandlers(void);
};

#include "Channel.hpp"

#endif
