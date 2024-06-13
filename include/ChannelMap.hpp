/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelMap.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:12:12 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/13 01:25:41 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "Channel.hpp"

class ChannelMap
{
	private:
		std::map<std::string, Channel> _channels;

	public:
		ChannelMap(void);
		ChannelMap(ChannelMap &src);

		~ChannelMap(void);

		ChannelMap &operator=(ChannelMap &src);
};
