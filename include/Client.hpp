/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:23:56 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/13 02:42:10 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>

class Channel;

class Client
{
	private:
		std::string _nick;
		std::string _username;
		int _fd;
		std::map<std::string, Channel*> _channels;
		int _mode_flags;


	public:
		typedef enum e_mode {
			AWAY = 1,
			INVISIBLE = 2,
			WALLOPS = 4,
			RESTRICTED = 8,
			OPERATOR = 16,
			LOCAL_OP = 32,
			RECV_NOTICES = 64
		} t_mode;

		Client(void);
		Client(int fd, std::string nick, std::string username);
		Client(Client &client);

		~Client(void);

		Client &operator=(Client &src);
};
