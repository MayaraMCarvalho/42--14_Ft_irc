/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandsTest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:25:59 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/25 19:38:16 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "./TestFramework.hpp"
#include "./include/MockTest.hpp"

/*bool    TestIsCommand(void) {
    MockClientList clients;
    MockChannelList channels;
    int fd = 1;
    MockClient client;

    // Adiciona o cliente mock na lista de clientes
    clients.add(client, fd);

    // Cria o objeto Commands com o cliente e a lista de canais mock
    Commands commands(clients, channels, fd);

    std::cout << "\033[0;34m" << "\nTesting Commands::isCommand method:" << "\033[0m" << std::endl;

    std::cout << "Check the JOIN command:" << std::endl;
    std::string message = "JOIN #newchannel";
    bool result = commands.isCommand(message);
    std::cout << "Checks whether the command was recognized as valid:" << std::endl;
    ASSERT_EQ(result, true);
    std::cout << "Checks if the last registered action was join:" << std::endl;
    ASSERT_EQ(channels.getLastAction(), "join");
    std::cout << "Checks if the last registered channel was #channel:" << std::endl;
    ASSERT_EQ(channels.getLastChannel(), "#channel");
    std::cout << "Checks whether the last registered file descriptor was fd:" << std::endl;
    ASSERT_EQ(channels.getLastFd(), fd);

    std::cout << "\nCheck the PART command:" << std::endl;
    message = "PART #channel";
    result = commands.isCommand(message);
    ASSERT_EQ(result, true);
    ASSERT_EQ(channels.getLastAction(), "part");
    ASSERT_EQ(channels.getLastChannel(), "#channel");
    ASSERT_EQ(channels.getLastFd(), fd);

    return (true);
}*/

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>

// Função auxiliar para testar asserções
void assertEqual(bool condition, const std::string &message) {
    if (!condition) {
        std::cerr << "Assertion failed: " << message << std::endl;
    }
}

// Função de teste para o comando JOIN
bool    testCommandJoin(void) {
    ClientList clients;
    ChannelList channels;
    int fd = 1;

    Client client(fd);
    clients.add(client);

    Commands commands(clients, channels, fd);

    std::cout << "Testing Commands::commandJoin method:" << std::endl;

    std::string message = "JOIN #newchannel";
    commands.isCommand(message);

    // Verifica se o canal foi adicionado à lista de canais
    //assertEqual(channels.get("#newchannel") != NULL, "Expected channel #newchannel to exist");

    // Verifica se o cliente está no canal
    Channel* channel = channels.get("#newchannel");

    //assertEqual(channel != NULL, "Expected channel #newchannel to be valid");
    //assertEqual(channel->hasClient(fd), "Expected client to be in channel #newchannel");

    return (true);
}

// Função de teste para o comando PART
bool    testCommandPart(void) {
    ClientList clients;
    ChannelList channels;
    int fd = 1;
    // Client client;

    //clients.add(client, fd);
    Client client(fd);
    clients.add(client);

    // Adiciona um canal e configura um cliente
    std::string channelName = "#newchannel";
    channels.join(fd, channelName, "");

    Commands commands(clients, channels, fd);

    std::cout << "Testing Commands::commandPart method:" << std::endl;

    std::string message = "PART #newchannel";
    commands.isCommand(message);

    assertEqual(channels.getLastAction() == "part", "Expected part action");
    assertEqual(channels.getLastChannel() == "#newchannel", "Expected #newchannel");
    assertEqual(channels.getLastFd() == fd, "Expected file descriptor 1");
    return (true);
}
