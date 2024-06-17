/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelList.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 03:46:51 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/17 03:08:19 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelList.hpp"

ChannelList::ChannelList(void) : _channels() { }

ChannelList::ChannelList(ChannelList &src) : _channels(src._channels) { }

ChannelList::~ChannelList(void) { }

ChannelList &ChannelList::operator=(ChannelList &src) {
	if (this == &src)
		return *this;

	_channels = src._channels;
	return *this;
}

// Getters
std::map<std::string, Channel>::iterator ChannelList::get(std::string name) {
	return _channels.find(name);
}

std::map<std::string, Channel>::iterator ChannelList::end(void) {
	return _channels.end();
}

void ChannelList::add(Channel channel) {
	_channels.insert(
		std::pair<const std::string, Channel>(channel.getName(), channel));
}

void ChannelList::remove(std::string name)
{
	_channels.erase(name);
}
