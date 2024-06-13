/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:23:56 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/13 04:47:33 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <map>


class Channel;
class ChannelList;

class Client
{
	public:
		typedef enum {
			NO_MODE = 0,
			AWAY = 1,
			INVISIBLE = 2,
			WALLOPS = 4,
			RESTRICTED = 8,
			OPERATOR = 16,
			LOCAL_OP = 32,
			RECV_NOTICES = 64
		} t_mode;

		typedef enum {
			UNKNOWN = 0,
			CONNECTED,
			AUTHENTICATED,
			GOT_USER,
			GOT_NICK,
			REGISTERED,
			DISCONNECTED
		} t_status;

		// Constructors
		Client(void);
		Client(int fd);
		Client(Client &client);

		~Client(void);

		Client &operator=(Client &src);

		// Getters
		std::string getNick(void);
		std::string getUser(void);
		std::string getHost(void);
		std::string getFullId(void);
		int getFD(void);
		std::map<std::string, Channel*> &getChannelList(void);
		t_status getStatus(void);
		bool getMode(t_mode mode);

		// Setters
		void setNick(std::string nick);
		void setUser(std::string user);
		void setHost(std::string host);
		void setFD(int fd);
		void setMode(std::string modeStr);
		void setStatus(t_status status);

		// Channel functions
		bool isInChannel(std::string channelStr);
		void add_channel(Channel &Channel);
		void remove_channel(Channel &Channel);
		void join_channel(ChannelList &channels, std::string channelStr);
		void part_channel(ChannelList &channels, std::string channelStr);

	private:
		std::string _nick;
		std::string _user;
		std::string _host;
		int _fd;
		std::map<std::string, Channel*> _channels;
		t_mode _mode;
		t_status _status;
};

#endif
