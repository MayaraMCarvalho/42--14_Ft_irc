/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:47:05 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/01 03:35:48 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>
# include "Client.hpp"

class Channel
{
	public:
		typedef enum {
			NO_CMODE = 0,
			ANONYMOUS = 1,
			INVITEONLY = 2,
			MODERATED = 4,
			NO_OUT_MSG = 8,
			QUIET = 16,
			PRIVATE = 32,
			SECRET = 64,
			SERV_REOP = 128,
			OP_TOPIC = 256,
			SAFE = 512,
			HAS_KEY = 1024,
			ULIMIT = 2048
		} t_cmode;

		typedef enum {
			NO_UMODE = 0,
			FOUNDER = 1,
			CHANOP = 2,
			VOICE = 4,
			HALFOP = 8,
			PROTECTED = 16
		} t_umode;

		Channel(const std::string &name, MsgHandler &msgHandler);
		Channel(const Channel &src);

		~Channel(void);

		Channel &operator=(const Channel &src);

		// Getters
		const std::string &getName(void);
		const std::string &getTopic(void);
		const std::string &getKey(void);
		int	getUserLimit(void);
		int	getNumUsers(void);
		bool getChannelMode(const t_cmode mode);
		int getChannelModeFlags(void);
		bool getUserMode(const int userFD, const t_umode mode);
		int getUserModeFlags(const int userFD);
		bool userIsInChannel(const int userFD);
		bool userCanJoin(const int userFD);
		bool userHasInvite(const std::string &nick);
		bool empty(void);
		static char getPrefix(t_umode umode);
		std::map<int, int>::iterator usersBegin(void);
		std::map<int, int>::iterator usersEnd(void);

		// Setters
		void setTopic(const std::string &topic);
		void setKey(const std::string &key);
		void setUserLimit(const int limit);
		void setChannelMode(const std::string &modeStr);
		void setChannelModeFlags(const int modeFlags);
		void setUserMode(const int userFD, const std::string &modeStr);
		void setUserModeFlags(const int userFD, const int modeFlags);

		// Channel functions
		void addUser(const int fd, const int userModeFlags);
		void removeUser(const int fd);
		void sendToAll(const std::string &from, const std::string &message);
		void sendToAll(const std::string &message);
		void addInvite(const std::string &nick);
		void removeInvite(const std::string &nick);

	private:
		MsgHandler &_msgHandler;
		std::string _name;
		std::string _topic;
		std::string _key;
		std::map<int, int> _users;
		std::set<std::string> _invites;
		int _channelModeFlags;
		int _limit;
};

#endif
