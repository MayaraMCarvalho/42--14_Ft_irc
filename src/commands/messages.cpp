/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:40:49 by macarval          #+#    #+#             */
/*   Updated: 2024/06/21 16:21:58 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void Commands::commandJoin( void )
{
	std::string error;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (initialVerify(error, 2, "JOIN <#channel_name>\n"))
	{
		std::string channel = _args[1];

		if (validChannel(channel, error))
		{
			if (!validArg(channel))
				return ;
			else
			{
				_channels.join(_fd, channel);
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
		std::string message = getMessage();
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
	ssize_t	nbytes;

	if (clientFd == -1)
		return false;

	std::string fullMessage = BBLUE + "Message received from " +
		BYELLOW + _clients.getNick(_fd) + BPURPLE +
		"\n" + message + RESET + "\r\n";

	nbytes = write(clientFd, fullMessage.c_str(), fullMessage.length());
	if (nbytes < 0)
	{
		std::cerr << RED << "Write error on client " << clientFd << std::endl;
		std::cout << RESET;
	}
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

std::string Commands::getMessage( void )
{
	std::string result;

	for (std::vector<std::string>::const_iterator it = _args.begin() + 2;
			it != _args.end(); ++it)
	{
		if (it != _args.begin() + 2)
			result.append(" ");
		result.append(*it);
	}
	return result;
}
