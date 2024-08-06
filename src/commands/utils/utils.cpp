/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:29:02 by macarval          #+#    #+#             */
/*   Updated: 2024/08/06 18:16:45 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

std::string Commands::getMessage(int index)
{
	std::string	result;

	for (std::vector<std::string>::const_iterator it = _args.begin() + index;
			it != _args.end(); ++it)
	{
		if (it != _args.begin() + index)
			result.append(" ");
		result.append(*it);
	}
	return result;
}

std::string Commands::toString(t_numCode code)
{
	std::ostringstream	oss;

	oss << std::setw(3) << std::setfill('0') << static_cast<int>(code);
	return oss.str();
}

std::string Commands::toString(int num)
{
	std::ostringstream	oss;

	oss << static_cast<int>(num);
	return oss.str();
}

int Commands::toInt(std::string &str)
{
	std::istringstream iss(str);
	int number;
	iss >> number;

	if (iss.fail() || !iss.eof())
		return -1;

	return number;
}

void Commands::printInfo(const std::string &info)
{
	_clients.getClient(_fd)->second.sendMessage(info);
}

void Commands::strToUpper(std::string &str) {
	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
		*it = std::toupper(*it);
}

std::string Commands::getUserFlags(int modeFlags)
{
	std::stringstream mode;

	if (modeFlags)
		mode << '+';

	if (modeFlags & Client::AWAY) mode << "a";
	if (modeFlags & Client::INVISIBLE) mode << "i";
	if (modeFlags & Client::WALLOPS) mode << "w";
	if (modeFlags & Client::RESTRICTED) mode << "r";
	if (modeFlags & Client::OPERATOR) mode << "o";
	if (modeFlags & Client::LOCAL_OP) mode << "O";
	if (modeFlags & Client::RECV_NOTICES) mode << "s";

	return mode.str();

}

std::string Commands::getChannelFlags(int modeFlags, Channel &channel)
{
	std::stringstream mode, params;

	if (modeFlags)
		mode << '+';
	if (modeFlags & Channel::ANONYMOUS) mode << "a";
	if (modeFlags & Channel::INVITEONLY) mode << "i";
	if (modeFlags & Channel::MODERATED) mode << "m";
	if (modeFlags & Channel::NO_OUT_MSG) mode << "n";
	if (modeFlags & Channel::QUIET) mode << "q";
	if (modeFlags & Channel::PRIVATE) mode << "p";
	if (modeFlags & Channel::SECRET) mode << "s";
	if (modeFlags & Channel::OP_TOPIC) mode << "t";
	if (modeFlags & Channel::HAS_KEY)
	{
		mode << "k";
		params << channel.getKey() << ' ';
	}
	if (modeFlags & Channel::ULIMIT)
	{
		mode << "l";
		params << channel.getUserLimit() << ' ';
	}

	return mode.str() + " " + YELLOW + params.str();
}
