/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:51:56 by macarval          #+#    #+#             */
/*   Updated: 2024/07/25 07:23:46 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <cstdlib>
#include <iostream>
#include "Colors.hpp"
#include "ConsoleLogger.hpp"
#include "IrcServer.hpp"


bool validateArguments(int argc, char *argv[], std::string &port, std::string &password)
{
	if (argc != 3)
	{
		std::cerr << RED;
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		std::cerr << RESET << std::endl;
		return (false);
	}

	// Checks if the port is a valid integer
	try
	{
		port = argv[1];
		int portNum = std::atoi(port.c_str());
		// Ports 0 to 1024 are typically reserved for specific services
		//  of the operating system and above 65535 are invalid, as they
		//  are outside the valid range of TCP and UDP ports.
		//  Helps ensure that the server functions correctly and
		//  prevents possibleproblems arising from the use of invalid ports.
		if (portNum <= 1024 || portNum > 65535)
			throw std::invalid_argument("Port number out of range");
	}
	catch (const std::invalid_argument &e)
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
	}

	// The password is valid if it is not an empty string
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
	ConsoleLogger logger;

	if (!validateArguments(argc, argv, port, password))
		return (1);

	try
	{
		IRCServer server(port, password, logger);
		server.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << RED;
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << RESET << std::endl;
		return (1);
	}
	return (0);
}
