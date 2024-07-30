/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:29:48 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/26 02:41:08 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/TestFramework.hpp"


bool    checkSendMessage(int clientFd, const std::string &expectedMessage) {
    std::string response;
    ssize_t nbytes = send(clientFd, expectedMessage.c_str(), expectedMessage.length(), 0);

    if (nbytes < 0) {
        std::cerr << "Error writing to client " << clientFd << std::endl;
        return (false);
    }

    return (true);
}

bool    TestBotConstructors(void) {
    std::cout << "\033[0;34m" << "\nTesting Bot constructors:" << "\033[0m" << std::endl;
    bool result = true;

    Bot bot1;
    std::cout << "1) Test if Bot default constructor creates an object:" << std::endl;
    result &= ASSERT_EQ(bot1.getName(), "");

    Bot bot2("TestBot");
    std::cout << "2) Test if Bot constructor with name initializes name correctly:" << std::endl;
    result &= ASSERT_EQ(bot2.getName(), "TestBot");

    return (result);
}

bool    TestBotGettersSetters(void) {
    std::cout << "\033[0;34m" << "\nTesting Bot getters and setters:" << "\033[0m" << std::endl;
    bool result = true;

    Bot bot;
    bot.setName("UpdatedBot");

    std::cout << "1) Test if setName correctly sets the name:" << std::endl;
    result &= ASSERT_EQ(bot.getName(), "UpdatedBot");

    return (result);
}

bool    TestBotRespondToMessage(void) {
    std::cout << "\033[0;34m" << "\nTesting Bot respondToMessage method:" << "\033[0m" << std::endl;
    bool result = true;
    int clientFd = 1;

    Bot bot("EchoBot");
    std::string message = "Hello, Bot!";
    std::string expectedResponse = "EchoBot: I received your message: Hello, Bot!";

    std::cout << "1) Test if respondToMessage sends the correct response:" << std::endl;
    result &= checkSendMessage(clientFd, expectedResponse);

    return (result);
}
