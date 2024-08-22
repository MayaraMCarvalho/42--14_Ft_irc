/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:40:10 by macarval          #+#    #+#             */
/*   Updated: 2024/08/22 01:04:24 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

#include "ClientList.hpp"
#include "ChannelList.hpp"
#include "MsgHandler.hpp"
#include "Logger.hpp"

class	Channel;

class IRCServer
{
	private:

		std::string					_port;
		std::string					_password;
		int 						_serverFd;
		std::vector<struct pollfd>	_pollFds;
		Logger						&_logger;
		MsgHandler					_msgHandler;
		ClientList					_clients;
		ChannelList					_channels;
		bool						_isFdDisconnected;
		bool						_shouldExit;
		static IRCServer*			_instance;
		std::string					_hostname;
		bool						_hostnameIsSet;

	public:
		static const int MAX_MSG_LENGTH = 512;

	// Constructor & Destructor ===============================================
		IRCServer(const std::string &port, const std::string &password,
			Logger &logger);
		~IRCServer( void );

	// Exceptions =============================================================

	// Getters ================================================================
		ClientList			&getClients( void );
		ChannelList			&getChannels( void );
		const std::string	&getPassword( void );
		MsgHandler			&getMsgHandler(void);
		bool				getIsFdDisconnected(void);
		static std::string	getHostName(const int socketFd);
		Logger		&getLogger(void);

	// Setters ================================================================

	// Methods ================================================================

		void				setupServer(void);
		void				run(void);
		void				acceptNewClient(void);
		bool				handleClientMessage(int clientFd);
		void				removeClient(int clientFd);
		static void			signalHandler(int signal);
		static void			setupSignalHandlers(void);
		void				disconnectClient(int fd, size_t fdIdx);
		void				disconnectClient(int fd);
		void				handleClientSideDisconnect(int fd);
};

#endif
