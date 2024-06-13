/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMap.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:12:12 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/13 04:17:52 by gmachado         ###   ########.fr       */
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
};

#endif
