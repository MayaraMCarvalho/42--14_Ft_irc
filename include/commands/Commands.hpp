/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:17:29 by macarval          #+#    #+#             */
/*   Updated: 2024/07/25 20:22:19 by macarval         ###   ########.fr       */
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
	// Methods ================================================================

		// ADICIONAR CONST E & ONDE NECESSÁRIO E RETESTAR TODOS OS COMANDOS

		// Commands.cpp
		void		extractCommands(int clientFd);
		bool		isCommand(int clientFd, const std::string &message);
		void		parsingArgs(const std::string &message);

		void		commandInvite( void );
		void		sendInviting(std::string &nick, std::string &channelName);

		// channelCommands.cpp
		void		commandJoin( void );
		void		printJoin(std::string &channelName);
		void		commandPart( void );
		void		commandKick( void );
		void		commandTopic( void );

		// commandMode.cpp
		void		commandMode( void );
		void		commandModeChannel(std::string &channelName);
		bool		verifyMode(std::string &mode, std::string &who,
							   std::string pattern);
		void		applyMode(std::string &channelName, std::string mode,
							  size_t &index);
		void		handleModeParameters(std::string &mode,
									std::string &channelName, size_t &index);
		void		handleKeyMode(std::string &channelName, std::string &param);
		void		commandModeUser(std::string &nick);
		bool		verifyNick(std::string &nick);

		// privmsgCommands.cpp
		void		commandPrivMsg( void );
		bool		sendMessage(int clientFd, const std::string &message);
		void		sendMessageChannel(std::string &recipient, std::string &message);
		bool		sendMessage(std::map<std::string, Channel>::iterator channel,
								std::string &message);
		std::string	getFullMessage(const std::string &message, std::string &name);
		bool		isItChannel(const std::string &channelName);

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
		std::string	errorNoSuchNick(std::string &recipient);
		std::string	errorNoSuchChannel(std::string &channelName);
		std::string	errorCannotSendToChan(std::string &channelName);
		std::string	errorTooManyChannels(std::string &channelName);
		std::string	errorNoRecipient( void );
		std::string	errorNoTextToSend( void );
		std::string	errorNoNicknameGiven( void );
		std::string	errorErroneusNickname(std::string &arg);
		std::string	errorNicknameInUse(std::string &nick);
		std::string	errorUserNotInChannel(std::string &nick,
										  std::string &channelName);
		std::string	errorNotOnChannel(std::string &channelName);
		std::string	errorUserOnChannel(std::string &nick,
									   std::string &channelName);
		std::string	errorNotRegistered( void );
		std::string	errorNeedMoreParams( void );
		std::string	errorAlredyRegister( void );
		std::string	errorPassMismatch( void );
		std::string	errorKeySet(std::string &channelName);
		std::string	errorChannelIsFull(std::string &nick,
									   std::string &channel);
		std::string	errorInviteOnlyChan(std::string &nick,
										std::string &channel);
		std::string	errorBannedFromChan(std::string &nick,
										std::string &channel);
		std::string	errorBadChannelKey(std::string &nick,
									   std::string &channel);
		std::string	errorBadChanMask(std::string &channelName);
		std::string	errorChanPrivsNeeded(std::string &channelName);
		std::string	errorUsersDontMatch( void );
		std::string	errorUnknownMode(std::string &nick, std::string &mode);

		// infos.cpp
		std::string	getWelcome(Client &client);
		std::string	getUserModeIs(Client &client);
		std::string	getChannelModeIs(Channel &channel);
		std::string	getTopic(std::string &channelName);
		std::string	getInviting(std::string &nickname, std::string &channelName);
		std::string	getNamReply(std::string &channelName);
		std::string	getEndOfNames(std::string &channelName);

		// utils.cpp
		std::string	getMessage(int index);
		std::string	toString(t_numCode &code);
		std::string	toString(int num);
		int			toInt(std::string &str);
		void		printInfo(const std::string &info);
		static void	strToUpper(std::string &str);

		// validations.cpp
		bool		initValidation(size_t numArgs);
		bool		validArg(std::string &arg);
		bool		validChannelName(std::string &channel);
		bool		validMessage(std::string &message);
		bool		validSetup( void );
		bool		invalidChar(std::string &arg);

		// verify.cpp
		bool		verifyChannel(std::string &channelName);
		bool		verifyJoin(std::string &channelName, std::string &key);
		bool		verifyJoinChannel(std::string &channelName,
									  std::string &key);
		bool		verifyChanOp(std::string &channelName);
		bool		verifyInvite(std::string &nick, std::string &channelName);
};

#endif
