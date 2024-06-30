/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:40:10 by macarval          #+#    #+#             */
/*   Updated: 2024/06/30 05:38:04 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

#include "ClientList.hpp"
#include "ChannelList.hpp"
#include "FileTransfer.hpp"
#include "Bot.hpp"
# include "numCode.hpp"

class	Channel;

class IRCServer
{
	private:
		std::string					_port;
		std::string					_password;
		int 						_serverFd;
		std::vector<struct pollfd>	_pollFds;
		FileTransfer 				_fileTransfer;
		Bot 						_bot;
		ClientList					_clients;
		ChannelList					_channels;
		bool						_shouldExit;
		static IRCServer*			_instance;

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
		t_numCode	authenticate(int userFD, std::string password);
		void		acceptNewClient(void);
		void		handleClientMessage(int clientFd);
		void		removeClient(int clientFd);
		static void	sendMessage(int clientFd, const std::string &message);
		static void	signalHandler(int signal);
		static void	setupSignalHandlers(void);
};

#endif
