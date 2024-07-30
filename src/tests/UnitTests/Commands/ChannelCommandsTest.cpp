/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCommandsTest.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:11:43 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/30 11:52:33 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/TestFramework.hpp"

bool TestCommandJoin(void) {
    std::cout << "\033[0;34m\nTesting Commands commandJoin method:\033[0m" << std::endl;
    bool result = true;

    std::string port = "6667";
    std::string password = "secret";
    IRCServer server(port, password);

    MsgHandler dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList clients(dummyMsgHandler, dummyPollFds);
    ChannelList channels(clients, dummyMsgHandler);

    std::string serverPass = "password";
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        std::cerr << "Error: Unable to create socket" << std::endl;
        return false;
    }

    Commands commands(server);

    std::cout << "1) Test if user can join a channel:" << std::endl;
    std::vector<std::string> args;
    args.push_back("JOIN");
    args.push_back("testChannel");
    //commands.setArgs(args);
    //commands.commandJoin();

    //ChannelList::ChannelMap::iterator it = channels.get("testChannel");
    if (channels.get("testChannel") != channels.end()) {
        result &= ASSERT_ITER_EQ(channels.get("testChannel")->second.getName(), "testChannel");
    } else {
        std::cerr << "Error: Channel 'testChannel' not found!" << std::endl;
        result = false;
    }

    close(fd);
    return result;
}
