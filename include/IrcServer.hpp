/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:40:10 by macarval          #+#    #+#             */
/*   Updated: 2024/08/20 00:47:19 by lucperei         ###   ########.fr       */
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

	public:
		static const int MAX_MSG_LENGTH = 512;

	// Constructor & Destructor ===============================================
		IRCServer(const std::string &port, const std::string &password,
			Logger &logger);
		~IRCServer( void );

	// Exceptions =============================================================

	// Getters ================================================================
	
		const				std::string& getPort(void);
		const				std::string& getPassword(void);
		int					getServerFd(void);
		const				std::vector<struct pollfd>& getPollFds(void);
		const				FileTransfer& getFileTransfer(void);
		const				Bot& getBot(void);
		ClientList			&getClients( void );
		ChannelList			&getChannels( void );
		MsgHandler			&getMsgHandler(void);
		bool				getIsFdDisconnected(void);
		static std::string	getHostName(const char *ip, const char *port);
		Logger		&getLogger(void);

	// Setters ================================================================
	
		void		setPort(const std::string& port);
		void		setPassword(const std::string& password);
		void		setServerFd(int serverFd);
		void		setPollFds(const std::vector<struct pollfd>& pollFds);
		void		setFileTransfer(FileTransfer& fileTransfer);
		void		setBot(const Bot& bot);
		void		setClients(ClientList& clients);
		void		setChannels(ChannelList& channels);

	// Methods ================================================================

		void		run(void);
		void		setupServer(void);
		void		acceptNewClient(void);
		bool		handleClientMessage(int clientFd);
		void		removeClient(int clientFd);
		void		setupSignalHandlers(void);
		void		disconnectClient(int fd, size_t fdIdx);
		void		disconnectClient(int fd);
		void		handleClientSideDisconnect(int fd);
		t_numCode	authenticate(int userFD, std::string password);
		static void	signalHandler(int signal);
		static void	sendMessage(int clientFd, const std::string &message);
};

#endif
