/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:47:05 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/16 18:31:14 by gmachado         ###   ########.fr       */
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
			SAFE = 512
		} t_cmode;

		typedef enum {
			NO_UMODE = 0,
			CREATOR = 1,
			CHANOP = 2,
			VOICE = 4
		} t_umode;

		Channel(std::string name);
		Channel(Channel &src);

		~Channel(void);

		Channel &operator=(Channel &src);

		// Getters
		std::string getName(void);
		std::string getTopic(void);
		int	getUserLimit(void);
		bool getChannelMode(t_cmode mode);
		int getChannelModeFlags(void);
		bool getUserMode(int userFD, t_umode mode);
		int getUserModeFlags(int userFD);
		bool isUserInChannel(int userFD);
		bool userCanJoin(int userFD);

		// Setters
		void setTopic(std::string topic);
		void setUserLimit(int limit);
		void setChannelMode(std::string modeStr);
		void setChannelModeFlags(int modeFlags);
		void setUserMode(int userFD, std::string modeStr);

		// Channel functions
		void addUser(int fd, int userModeFlags);
		void removeUser(int fd);
		void sendToAll(std::string &message);

	private:
		std::string _name;
		std::string _topic;
		std::map<int, int> _users;
		int _channelModeFlags;
		int _limit;

		Channel(void);
};

#endif
