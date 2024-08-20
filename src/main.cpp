/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:51:56 by macarval          #+#    #+#             */
/*   Updated: 2024/08/20 00:49:44 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/IrcServer.hpp"

#include <cstdlib>
#include <iostream>
#include "Colors.hpp"
#include "ConsoleLogger.hpp"
#include "IrcServer.hpp"


bool	validateArguments(int argc, char *argv[], std::string &port, std::string &password)
{
	int portNum;
	std::string portStr;

	if (argc != 3)
	{
		std::cerr << RED;
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		std::cerr << RESET << std::endl;
		return (false);
	}

	port = argv[1];
    portStr = argv[1];
    if (!containsOnlyDigits(portStr))
	{
		std::cerr << RED;
		std::cerr << "Invalid port number: " << YELLOW << argv[1] << std::endl;
		std::cerr << RESET << std::endl;
		return (false);
	}
	catch (const std::out_of_range &e)
	{
		std::cerr << RED;
		std::cerr << "Port number out of range: ";
		std::cerr << YELLOW << argv[1] << std::endl;
		std::cerr << RESET << std::endl;
		return (false);
	} else {
		std::istringstream iss(portStr);
		iss >> portNum;
		if (portNum <= 1024 || portNum > 65535)
		{
			std::cerr << RED;
			std::cerr << "Error: Port number out of range" << std::endl;
			std::cout << RESET;
			return (false);
		}
	}

	password = argv[2];
	if (password.empty())
	{
		std::cerr << RED;
		std::cerr << "Invalid password! "<< YELLOW << argv[2] << std::endl;
		std::cerr << RESET << std::endl;
		return (false);
	}

	return (true);
}

int main(int argc, char *argv[])
{
	std::string	port;
	std::string	password;
	ConsoleLogger logger(Logger::DEBUG);


	if (!validateArguments(argc, argv, port, password))
		return (1);

	try
	{
		IRCServer server(port, password, logger);
		server.run();
	}
	catch (const std::exception &e)
	{
		logger.fatal("Exception caught: " + RED + e.what() + RESET);
		return (1);
	}
	return (0);
}
