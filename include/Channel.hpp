/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:47:05 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/13 04:17:05 by gmachado         ###   ########.fr       */
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
			VOICE = 4,
			BANNED = 8
		} t_umode;

		typedef struct {
			t_umode userMode;
			Client* client;
		} t_client_with_mode;

		Channel(void);
		Channel(std::string name);
		Channel(Channel &src);

		~Channel(void);

		Channel &operator=(Channel &src);

	private:
		std::string name;
		std::map<int, t_client_with_mode> _users;
		t_cmode _channelMode;
		int _limit;
};

#endif
