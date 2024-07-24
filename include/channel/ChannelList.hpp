/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:12:12 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/23 21:37:14 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_LIST_HPP
# define CHANNEL_LIST_HPP

# include <map>
# include "Channel.hpp"
# include "../client/ClientList.hpp"
# include "../utils/Colors.hpp"
# include "Codes.hpp"

class ChannelList
{
	private:
		ClientList &_clients;
		MsgHandler &_msgHandler;

		std::map<std::string, Channel> _channels;
		std::map<std::string, std::set<std::string> > _invites;
		std::map<std::string, Channel>::size_type remove(std::string name);

		void addInvite(const std::string &nick, const std::string &chan);
		void removeInvite(const std::string &nick, const std::string &chan);

		static const int _DEFAULT_FLAGS = Channel::NO_UMODE;

	public:
		ChannelList(ClientList &clients, MsgHandler &msgHandler);
		ChannelList(ChannelList &src);

		~ChannelList(void);

		ChannelList &operator=(ChannelList &src);

		// Getters
		std::map<std::string, Channel>::iterator add(Channel channel);
		std::map<std::string, Channel>::iterator get(std::string name);
		std::map<std::string, Channel>::const_iterator get(std::string name) const;
		std::map<std::string, Channel>::iterator get(int fd);
		std::map<std::string, Channel>::iterator begin(void);
		std::map<std::string, Channel>::iterator end(void);
    	std::map<std::string, Channel>::const_iterator end(void) const;
		
		int			size(void);
		void		join(int userFD, const std::string &chanName, const std::string &key);
		void		part(int userFD, std::string chanName);
		void		partDisconnectedClient(int userFD);
		bool		userCanJoin(int userFD, Channel &chan, const std::string &key);
		bool		userHasInvite(const std::string &nick, const std::string &chan);
		t_numCode	inviteUser(const std::string &inviter,
		const std::string &invitee, const std::string &chan);
};

#endif
