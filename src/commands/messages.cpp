/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:40:49 by macarval          #+#    #+#             */
/*   Updated: 2024/06/27 11:04:24 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "IrcServer.hpp"

void Commands::commandJoin( void )
{
	std::string error;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (initialVerify(error, 2, "JOIN <#channel_name> <key (optional)>\n"))
	{
		std::string channel = _args[1];
		std::string key = "";

		if (_args.size() > 2)
			key = _args[2];
		if (validChannel(channel, error))
		{
			if (!validArg(channel))
				return ;
			else
			{
				_channels.join(_fd, channel, key);
				error = GREEN + "User successfully join the channel " +
					channel + "!\n" + RESET;
			}
		}
	}
	it->second.sendMessage(error);
	std::cout << error << std::endl;
}

void Commands::commandPart( void )
{
	std::string error;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (initialVerify(error, 2, "PART <#channel_name>\n"))
	{
		std::string channel = _args[1];

		if (validChannel(channel, error))
		{
			if (!validArg(channel))
				return ;
			else
			{
				_channels.part(_fd, channel);
				error = GREEN + "User successfully part the channel " +
					channel + "!\n" + RESET;
			}
		}
	}
	it->second.sendMessage(error);
	std::cout << error << std::endl;
}

void Commands::commandPrivMsg( void )
{
	std::string error;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (initialVerify(error, 3, "PRIVMSG <recipient> :<message>\n"))
	{
		std::string recipient = _args[1];
		std::string message = getMessage(2);
		bool isChannel = validChannel(recipient, error);

		if (!validArg(recipient) || !validMessage(message))
			return ;
		else
		{
			if (!isChannel)
			{
				if (sendMessage(_clients.getFDByNick(recipient), message))
					return ;
				error = RED + "Error: User not found\n" + RESET;
			}
			else
			{
				if (sendMessage( _channels.get(recipient), message))
					return ;
				error = RED + "Error: channel not found\n" + RESET;
			}
		}
	}
	it->second.sendMessage(error);
	std::cout << error << std::endl;
}

bool Commands::sendMessage(int clientFd, const std::string &message)
{
	if (clientFd == -1)
		return false;

	std::string fullMessage = BBLUE + "Message received from " +
		BYELLOW + _clients.getNick(_fd) + BPURPLE +
		"\n" + message + RESET;

	IRCServer::sendMessage(clientFd, fullMessage);
	return true;
}

bool Commands::sendMessage(std::map<std::string, Channel>::iterator channel, std::string &message)
{
	if (channel == _channels.end())
		return false;

	std::string fullMessage = BBLUE + "Message received from " +
		BYELLOW + _clients.getNick(_fd) + BPURPLE +
		"\n" + message + RESET + "\r\n";
	channel->second.sendToAll(fullMessage);
	return true;
}

std::string Commands::getMessage( int index )
{
	std::string result;

	for (std::vector<std::string>::const_iterator it = _args.begin() + index;
			it != _args.end(); ++it)
	{
		if (it != _args.begin() + index)
			result.append(" ");
		result.append(*it);
	}
	return result;
}
