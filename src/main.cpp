/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:51:56 by macarval          #+#    #+#             */
/*   Updated: 2024/07/06 19:40:20 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/IrcServer.hpp"


int main(int argc, char *argv[])
{
	std::string	port;
	std::string	password;
	IRCServer server;

	if (!server.validateArguments(argc, argv, port, password))
		return (1);

	try
	{
		IRCServer server(port, password);
		server.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << RED;
		std::cerr << "Error: " << e.what() << std::endl;
		std::cout << RESET << std::endl;
		return (1);
	}
	return (0);
}