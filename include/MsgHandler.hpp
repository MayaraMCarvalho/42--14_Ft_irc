/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsgHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:44:02 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/03 03:37:42 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_HANDLER
# define MSG_HANDLER

#include <list>
#include <map>
# include <string>

class MsgHandler {
	public:
		static const int MAX_RETRIES = 3;

		MsgHandler(void);
		MsgHandler(MsgHandler &src);
		MsgHandler(std::string host);

		~MsgHandler(void);

		MsgHandler &operator=(MsgHandler &src);

		typedef struct {
			std::string msgStr;
			union {
				int retries;
				int error;
			};
		} t_msg;

		std::string getHost(void);
		void sendMessage(int fd, const std::string &msg);
		void sendMessage(int fd, const std::string &from,
			const std::string &msg);
		t_msg pop(int fd);
		void push(int fd, t_msg msg);
		unsigned long size(int fd);

		// Numeric error replies
		std::string errAlreadyRegistered(const std::string &client);
		std::string errBadChanMask(const std::string &channel);
		std::string errBadChannelKey(const std::string &client,
			const std::string &channel);
		std::string errBannedFromChan(const std::string &client,
			const std::string &channel);
		std::string errCannotSendToChan(const std::string &client,
			const std::string &channel);
		std::string errChannelIsFull(const std::string &client,
			const std::string &channel);
		std::string errChanOPrivIsNeeded(const std::string &client,
			const std::string &channel);
		std::string errErroneusNickname(const std::string &client);
		std::string errInputTooLong(const std::string &client);
		std::string errInvalidModeParam(const std::string &client,
			const std::string &target, const char mode,
			const std::string &param, const std::string &description);
		std::string errInviteOnlyChan(const std::string &client,
			const std::string &channel);
		std::string errNeedMoreParams(const std::string &client,
			const std::string &command);
		std::string errNicknameInUse(const std::string &client);
		std::string errNoNickNameGiven(const std::string &client);
		std::string errNoOrigin(const std::string &client);
		std::string errNoRecipient(const std::string &client,
			const std::string &command);
		std::string errNoSuchChannel(const std::string &client,
			const std::string &channel);
		std::string errNoSuchNick(const std::string &client,
			const std::string &nick);
		std::string errNoTextToSend(const std::string &client);
		std::string errNotOnChannel(const std::string &client,
			const std::string &channel);
		std::string errNotRegistered(const std::string &client);
		std::string errPasswordMismatch(const std::string &client);
		std::string errTooManyChannels(const std::string &client,
			const std::string &channel);
		std::string errUModeUnknownFlag(const std::string &client);
		std::string errUnknownCommand(const std::string &client,
			const std::string &command, const std::string &info);
		std::string errUnknownCommand(const std::string &client,
			const std::string &command, const std::string &subcommand,
			const std::string &info);
		std::string errUnknownMode(const std::string &client,
		const char mode);
		std::string errUserNotInChannel(const std::string &client,
			const std::string &channel, const std::string &nick);
		std::string errUserOnChannel(const std::string &client,
			const std::string &channel, const std::string &nick);
		std::string errUsersDontMatch(const std::string &client);

		// Numeric normal replies
		std::string rplWelcome(const std::string &client);
		std::string rplChannelModeIs(const std::string &client,
			const int chanModes);
		std::string rplEndOfNames(const std::string &client,
			const std::string &channel);
		std::string rplNamReply(const std::string &client,
			const std::string &channel, const std::string &clientList,
			const char symbol);
		std::string rplTopic(const std::string &client,
			const std::string &channel, const std::string &topic);
		std::string rplNoTopic(const std::string &client,
			const std::string &channel);
		std::string rplList(const std::string &client,
			const std::string &channel, const std::string &topic,
			const int numUsers);
		std::string rplListEnd(const std::string &client);
		std::string rplInviting(const std::string &client,
			const std::string &channel, const std::string &nick);
		std::string rplUModeIs(const std::string &client,
			const int userModes);

		// Server Messages

	private:
		std::string _host;
		std::map<int, std::list<t_msg> > _msgQueues;
};


#endif
