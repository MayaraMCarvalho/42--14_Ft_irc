/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:47:05 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/13 02:00:37 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include "Client.hpp"

class Channel
{
	public:
		typedef enum e_cmode {
			ANONYMOUS = 1,
			INVITEONLY = 2,
			MODERATED = 4,
			NO_OUT_MSG = 8,
			QUIET = 16,
			PRIVATE = 32,
			SECRET = 64,
			SERV_REOP = 128,
			OP_TOPIC = 256
		} t_cmode;

		typedef enum e_umode {
			CREATOR = 1,
			CHANOP = 2,
			VOICE = 4
		} t_umode;

		Channel(void);
		Channel(std::string name);
		Channel(Channel &src);

		~Channel(void);

		Channel &operator=(Channel &src);

	private:
		std::string name;
		std::map<std::string, Client *> _users;
		std::map<std::string, t_umode> _userModes;
		std::map<std::string, Client *> bannedUsers;
		int _mode_flags;
};
