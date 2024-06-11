/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:51:56 by macarval          #+#    #+#             */
/*   Updated: 2024/06/11 09:08:27 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		std::cout << RED;
		std::cout << "\nUsage: ./ircserv <port> <password>\n\n";
		return (1);
	}
	else
	{
		Server server;

		server.test(argv);
	}
	return 0;
}
