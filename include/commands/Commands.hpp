/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:17:29 by macarval          #+#    #+#             */
/*   Updated: 2024/07/16 19:22:08 by macarval         ###   ########.fr       */
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
#include <iomanip>
#include <string>
#include <vector>
#include <poll.h>

#include "ClientList.hpp"
#include "ChannelList.hpp"
#include "MsgHandler.hpp"
#include "FileTransfer.hpp"
#include "Bot.hpp"
#include "Colors.hpp"
#include "Codes.hpp"

class	IRCServer;
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
		IRCServer					&_server;
		ClientList					&_clients;
		ChannelList					&_channels;
		const std::string			&_serverPass;
		const std::string			&_host;
		int							_fd;

	public:
	// Constructor & Destructor ===============================================
		Commands( IRCServer& server );
		~Commands( void );

	// Exceptions =============================================================

	// Getters ================================================================

	// Setters ================================================================

	// Methods ================================================================

		// Commands.cpp
		bool		isCommand(int clientFd, const std::string &message);
		void		parsingArgs(const std::string &message);
		// Mover?
		void		commandInvite( void );
		void		commandTopic( void );
		void		commandMode( void );
		//

		// channelCommands.cpp
		void		commandJoin( void );
		void		printJoin(std::string channelName);
		void		commandPart( void );
		void		commandKick( void );

		// privmsgCommands.cpp
		void		commandPrivMsg( void );
		bool		sendMessage(int clientFd, const std::string &message);
		bool		sendMessage(std::map<std::string, Channel>::iterator channel,
						std::string &message);
		std::string	getFullMessage(const std::string &message);

		// quitCommand.cpp
		void		commandQuit( void );
		void		quitServer( void );
		bool		getQuitMessage(std::string &messageQuit);

		// setupCommands.cpp
		void		commandPass( void );
		void		commandNick( void );
		void		commandUser( void );
		void		saveUser(std::string &user, std::string &userName);

		// errorsCode.cpp
		std::string	errorNoSuchNick(std::string &recipient, std::string who);
		std::string	errorNoSuchChannel(std::string &channelName);
		std::string	errorCannotSendToChan(std::string &channelName);
		std::string	errorTooManyChannels(std::string &channelName);
		std::string	errorNoRecipient( void );
		std::string	errorNoTextToSend( void );
		std::string	errorNoNicknameGiven( void );
		std::string	errorErroneusNickname(std::string &arg);
		std::string	errorNicknameInUse(std::string &nick);
		std::string	errorNotOnChannel(std::string &channelName);
		std::string	errorNotRegistered( void );
		std::string	errorNeedMoreParams(std::string suffix);
		std::string	errorAlredyRegister( void );
		std::string	errorPassMismatch( void );
		std::string	errorChannelIsFull(std::string &nick, std::string &channel);
		std::string	errorInviteOnlyChan(std::string &nick, std::string &channel);
		std::string	errorBannedFromChan(std::string &nick, std::string &channel);
		std::string	errorBadChannelKey(std::string &nick, std::string &channel);
		std::string	errorBadChanMask(std::string &channelName);
		std::string	errorChanPrivsNeeded(std::string &channelName);

		// infos.cpp
		std::string	getWelcome(Client &client);
		std::string	getTopic(std::string &channelName);
		std::string	getNamReply(std::string &channelName);
		std::string	getEndOfNames(std::string &channelName);

		// utils.cpp
		std::string	getMessage(int index);
		std::string	toString(t_numCode code);
		std::string	toString(int num);
		void		printInfo(const std::string &info);

		// validations.cpp
		bool		initValidation(size_t numArgs);
		bool		validArg(std::string &arg);
		bool		validChannelName(std::string &channel);
		bool		validMessage(std::string &message);
		bool		setupDone( void );
		bool		invalidChar(std::string &arg);

		// verify.cpp
		bool		verifyChannel(std::string &channelName);
		bool		verifyJoin(std::string &channelName, std::string &key);
		bool		verifyJoinChannel(std::string &channelName, std::string &key);
		bool		verifyKick (std::string &channelName);

		//
		// tests.cpp
		void		tests(Commands commands); //
};

#endif
