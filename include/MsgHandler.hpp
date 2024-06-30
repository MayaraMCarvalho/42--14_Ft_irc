/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsgHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:44:02 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/30 05:33:55 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_HANDLER
# define MSG_HANDLER

# include <string>

class MsgHandler {
	public:
		// Numeric error replies
		static std::string errAlreadyRegistered(const std::string &client);
		static std::string errBadChanMask(const std::string &channel);
		static std::string errBadChannelKey(const std::string &client,
			const std::string &channel);
		static std::string errBannedFromChan(const std::string &client,
			const std::string &channel);
		static std::string errCannotSendToChan(const std::string &client,
			const std::string &channel);
		static std::string errChannelIsFull(const std::string &client,
			const std::string &channel);
		static std::string errChanOPrivIsNeeded(const std::string &client,
			const std::string &channel);
		static std::string errErroneusNickname(const std::string &client);
		static std::string errInputTooLong(const std::string &client);
		static std::string errInvalidModeParam(const std::string &client,
			const std::string &target, const char mode,
			const std::string &param, const std::string &description);
		static std::string errInviteOnlyChan(const std::string &client,
			const std::string &channel);
		static std::string errNeedMoreParams(const std::string &client,
			const std::string &command);
		static std::string errNicknameInUse(const std::string &client);
		static std::string errNoNickNameGiven(const std::string &client);
		static std::string errNoOrigin(const std::string &client);
		static std::string errNoRecipient(const std::string &client,
			const std::string &command);
		static std::string errNoSuchChannel(const std::string &client,
			const std::string &channel);
		static std::string errNoSuchNick(const std::string &client,
			const std::string &nick);
		static std::string errNoTextToSend(const std::string &client);
		static std::string errNotOnChannel(const std::string &client,
			const std::string &channel);
		static std::string errNotRegistered(const std::string &client);
		static std::string errPasswordMismatch(const std::string &client);
		static std::string errTooManyChannels(const std::string &client,
			const std::string &channel);
		static std::string errUModeUnknownFlag(const std::string &client);
		static std::string errUnknownCommand(const std::string &client,
			const std::string &command, const std::string &info);
		static std::string errUnknownCommand(const std::string &client,
			const std::string &command, const std::string &subcommand,
			const std::string &info);
		static std::string errUnknownMode(const std::string &client,
		const char mode);
		static std::string errUserNotInChannel(const std::string &client,
			const std::string &channel, const std::string &nick);
		static std::string errUserOnChannel(const std::string &client,
			const std::string &channel, const std::string &nick);
		static std::string errUsersDontMatch(const std::string &client);

		// Numeric normal replies
		static std::string rplChannelModeIs(const std::string &client,
			const int chanModes);
		static std::string rplEndOfNames(const std::string &client,
			const std::string &channel);
		static std::string rplNamReply(const std::string &client,
			const std::string &channel, const std::string &clientList,
			const char symbol);
		static std::string rplTopic(const std::string &client,
			const std::string &channel, const std::string &topic);
		static std::string rplNoTopic(const std::string &client,
			const std::string &channel);
		static std::string rplList(const std::string &client,
			const std::string &channel, const std::string &topic,
			const int numUsers);
		static std::string rplListEnd(const std::string &client);
		static std::string rplInviting(const std::string &client,
			const std::string &channel, const std::string &nick);
		static std::string rplUModeIs(const std::string &client,
			const int userModes);

		// Server Messages

	private:
		MsgHandler(void);
		MsgHandler(MsgHandler &src);
		~MsgHandler(void);
		MsgHandler &operator=(MsgHandler &src);
};


#endif
