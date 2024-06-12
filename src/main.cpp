/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:51:56 by macarval          #+#    #+#             */
/*   Updated: 2024/06/12 12:06:50 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/IrcServer.hpp"

bool validateArguments(int argc, char *argv[], std::string& port, std::string& password) {
    
	if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
        return (false);
    }

    // Verifica se a porta é um número inteiro válido
    try {
        port = argv[1];
        int portNum = std::atoi(port.c_str());
		// Portas de 0 a 1024 são normalmente reservadas para serviços específicos 
		// do sistema operacional e acima de 65535 são inválidas, pois estão fora 
		// do intervalo válido de portas TCP e UDP.
		// Ajuda a garantir que o servidor funcione corretamente e evita possíveis
		// problemas decorrentes do uso de portas inválidas.
        if (portNum <= 1024 || portNum > 65535) {
            throw std::invalid_argument("Port number out of range");
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid port number: " << argv[1] << std::endl;
        return (false);
    } catch (const std::out_of_range& e) {
        std::cerr << "Port number out of range: " << argv[1] << std::endl;
        return (false);
    }

    // A senha é válida se não for uma string vazia
    password = argv[2];
    if (password.empty()) {
        std::cerr << "Invalid password: " << argv[2] << std::endl;
        return (false);
    }

    return (true);
}


int main(int argc, char *argv[])
{
	std::string port;
	std::string password;

    if (!validateArguments(argc, argv, port, password)) {
        return (1);
    }

	try {
		IRCServer server(port, password);
		server.run();
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
