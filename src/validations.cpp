/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:25:52 by macarval          #+#    #+#             */
/*   Updated: 2024/06/20 20:37:19 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

bool Commands::initialVerify(std::string &message, size_t num, std::string usage)
{
	if (_args.size() < num) // verificar se melhor usar =!
	{
		message = RED + "Error: Number of invalid arguments\n" +
			usage + RESET;
	}
	// else if (it->second.getStatus() != 2)
	// 	message = RED + "Error: Unauthenticated clients\n" + RESET;
	else
		return true;
	return false;
}

bool Commands::validArg(std::string &arg)
{
	std::map<int, Client>::iterator it = _clients.getClientByNick(arg);
	std::string error = "";

	if (arg.empty())
		error = RED + "Error: Empty parameter\n" + RESET;
	else if (arg.size() > MAX_LENGTH)
		error = RED + "Error: Too long\n" + RESET;
	else if (!(arg.find_first_not_of(ALPHA_NUM_SET) == std::string::npos))
		error = RED + "Error: Prohibited characters found\n" + RESET;
	else if (_args[0] == NICK && it != _clients.end())
		error = RED + "Error: Nickname already exists\n" + RESET;
	else
		return true;

	it = _clients.getClient(_fd);
	it->second.sendMessage(error);
	std::cout << error << std::endl;

	return false;
}

bool Commands::validChannel(std::string &channel, std::string &error)
{
	if (!channel.empty())
	{
		if (channel[0] != '#')
		{
			error = RED + "Error: Non-standard channel name\n" + RESET;
			return false;
		}
		else
			channel.erase(0, 1);
	}
	return true;
}

bool Commands::validMessage(std::string &message)
{
	std::string error = "";
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (!message.empty())
	{
		if (message[0] != ':')
		{
			error = RED + "Error: Non-standard message\n" + RESET;
		}
		else
		{
			message.erase(0, 1);
			return true;
		}
	}
	it->second.sendMessage(error);
	std::cout << error << std::endl;

	return false;
}
