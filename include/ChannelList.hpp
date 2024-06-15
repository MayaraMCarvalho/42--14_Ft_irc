/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:12:12 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/14 03:57:33 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_LIST_HPP
# define CHANNEL_LIST_HPP

#include <map>
#include "Channel.hpp"

class ChannelList
{
	private:
		std::map<std::string, Channel> _channels;

	public:
		ChannelList(void);
		ChannelList(ChannelList &src);

		~ChannelList(void);

		ChannelList &operator=(ChannelList &src);

		// Getters
		Channel *get(std::string name);

		void add(Channel &channel);
		void remove(std::string name);
};

#endif
