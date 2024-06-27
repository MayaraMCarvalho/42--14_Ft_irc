/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:23:56 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/27 03:20:03 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <set>

class Channel;
class ChannelList;

class Client {
	public:
		typedef enum {
			NO_MODE = 0,
			AWAY = 1,
			WALLOPS = 2,
			INVISIBLE = 4,
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
		Client(int fd);
		Client(const Client &src);

		~Client(void);

		Client &operator=(const Client &src);

		// Getters
		const std::string &getNick(void);
		const std::string &getUser(void);
		const std::string &getHost(void);
		const std::string getFullId(void);
		int getFD(void);
		std::set<std::string> &getChannelList(void);
		t_status getStatus(void);
		bool getMode( t_mode mode) ;
		int getModeFlags();


		// Setters
		void setNick(const std::string &nick);
		void setUser(const std::string &user);
		void setHost(const std::string &host);
		void setFD(int fd);
		void setModeFlags(int modeFlags);
		void setMode(const std::string &modeStr);
		void setStatus(t_status status);

		// Channel functions
		bool isInChannel(const std::string &channelStr) ;
		void addChannel(const std::string &channelStr);
		void removeChannel(const std::string &channelStr);
		void sendMessage(const std::string &msg);

	private:
		std::string _nick;
		std::string _user;
		std::string _host;
		int _fd;
		std::set<std::string> _channels;
		int _modeFlags;
		t_status _status;

		// Private default constructor to prevent empty initialization
		Client(void);

};

#endif
