/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientTest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:43:19 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/25 19:38:25 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/TestFramework.hpp"
#include "../include/MockIRCServer.hpp"


class TestClient : public Client {
public:
    TestClient(int fd, MsgHandler &msgHandler, const std::string &host)
        : Client(fd, msgHandler, host) {}

    void sendMessage(std::string &msg) {
        MockIRCServer::sendMessage(getFD(), msg);
    }
};

Client createClient(int fd) {
    MsgHandler dummyMsgHandler;
    std::string dummyHost = "localhost";
    return Client(fd, dummyMsgHandler, dummyHost);
}

bool    TestClientDefaultConstructor(void) {
    Client  client = createClient(0);
    bool    result = true;

    std::cout << "\033[0;34m" << "\nTesting for the default constructor Client:" << "\033[0m" << std::endl;
    
    std::cout << "1) Test if default nickname is empty:" << std::endl;
    result &= ASSERT_EQ(client.getNick(), "");

    std::cout << "2) Test if default username is empty:" << std::endl;
    result &= ASSERT_EQ(client.getUser(), "");

    std::cout << "3) Test if default host is empty:" << std::endl;
    result &= ASSERT_EQ(client.getHost(), "");

    std::cout << "4) Test if default status is UNKNOWN:" << std::endl;
    result &= ASSERT_EQ(client.getStatus(), Client::UNKNOWN);

    std::cout << "5) Test if default mode flags is NO_MODE:" << std::endl;
    result &= ASSERT_EQ(client.getModeFlags(), Client::NO_MODE);

    return (result);
}

bool    TestClientParameterizedConstructor(void) {
    Client  client = createClient(42);
    bool    result = true;

    std::cout << "\033[0;34m" << "\nTesting for parameterized constructor Client:" << "\033[0m" << std::endl;
    
    std::cout << "1) Test if parameterized constructor sets the fd correctly:" << std::endl;
    result &= ASSERT_EQ(client.getFD(), 42);

    std::cout << "2) Test if the default nickname is empty:" << std::endl;
    result &= ASSERT_EQ(client.getNick(), "");

    std::cout << "3) Test if the default username is empty:" << std::endl;
    result &= ASSERT_EQ(client.getUser(), "");

    std::cout << "4) Test if the default host is empty:" << std::endl;
    result &= ASSERT_EQ(client.getHost(), "");

    std::cout << "5) Test if the default status is UNKNOWN:" << std::endl;
    result &= ASSERT_EQ(client.getStatus(), Client::UNKNOWN);

    std::cout << "6) Test if the default mode flags are NO_MODE:" << std::endl;
    result &= ASSERT_EQ(client.getModeFlags(), Client::NO_MODE);

    return (result);
}

bool    TestClientCopyConstructor(void) {
    Client  client1 = createClient(42);
    bool    result = true;

    std::cout << "\033[0;34m" << "\nTesting for copy constructor Client:" << "\033[0m" << std::endl;

    client1.setNick("nick");
    client1.setUser("user");
    client1.setHost("host");
    client1.setStatus(Client::CONNECTED);
    client1.setModeFlags(Client::AWAY);

    Client client2(client1);

    std::cout << "1) Test if copy constructor copies the nickname correctly:" << std::endl;
    result &= ASSERT_EQ(client2.getNick(), "nick");

    std::cout << "2) Test if copy constructor copies the username correctly:" << std::endl;
    result &= ASSERT_EQ(client2.getUser(), "user");

    std::cout << "3) Test if copy constructor copies the host correctly:" << std::endl;
    result &= ASSERT_EQ(client2.getHost(), "host");

    std::cout << "4) Test if copy constructor copies the status correctly:" << std::endl;
    result &= ASSERT_EQ(client2.getStatus(), Client::CONNECTED);

    std::cout << "5) Test if copy constructor copies the mode flags correctly:" << std::endl;
    result &= ASSERT_EQ(client2.getModeFlags(), Client::AWAY);

    return (result);
}

bool    TestClientAssignmentOperator(void) {
    bool    result = true;

    std::cout << "\033[0;34m" << "\nTesting for client assignment operator:" << "\033[0m" << std::endl;

    Client client1 = createClient(42);
    client1.setNick("nick");
    client1.setUser("user");
    client1.setHost("host");
    client1.setStatus(Client::CONNECTED);
    client1.setModeFlags(Client::AWAY);

    Client client2 = createClient(0);

    client2 = client1;

    std::cout << "1) Test if the assignment operator copies the nickname correctly:" << std::endl;
    result &= ASSERT_EQ(client2.getNick(), "nick");

    std::cout << "2) Test if the assignment operator copies the username correctly:" << std::endl;
    result &= ASSERT_EQ(client2.getUser(), "user");

    std::cout << "3) Test if the assignment operator copies the host correctly:" << std::endl;
    result &= ASSERT_EQ(client2.getHost(), "host");

    std::cout << "4) Test if the assignment operator copies the status correctly:" << std::endl;
    result &= ASSERT_EQ(client2.getStatus(), Client::CONNECTED);

    std::cout << "5) Test if the assignment operator copies the mode flags correctly:" << std::endl;
    result &= ASSERT_EQ(client2.getModeFlags(), Client::AWAY);

    return (result);
}

 /*bool    TestSetNick(void) {
    bool result = true;
    std::cout << "\033[0;34m" << "\nTesting setNick method:" << "\033[0m" << std::endl;

    MsgHandler dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList clientList(dummyMsgHandler, dummyPollFds);
    std::string hostname1 = "192.168.0.2";
    //std::string hostname2 = "127.0.0.1";

    clientList.add(1, hostname1);
   // clientList.add(1, hostname2);
   std::map<int, Client>::iterator client = clientList.getClient(1);
   client->second.setStatus(Client::AUTHENTICATED);

    //c1.setStatus(Client::AUTHENTICATED);

    std::cout << "1) Test setting a new nickname:" << std::endl;
    //cl.setNick(1, "newNick");
    const std::string& newNick = "newNick";
    clientList.setNick(1, newNick);
    result &= (clientList.getNick(1) == "newNick");





    //result &= (cl._nickToClient.find("newNick") != cl._nickToClient.end());

   std::cout << "2) Test setting an empty nickname:" << std::endl;
    try {
        cl.setNick(1, "");
        result &= false; // should not reach here
    } catch (...) {
        result &= true;
    }

    std::cout << "3) Test setting a nickname with invalid characters:" << std::endl;
    try {
        cl.setNick(1, "reallyLongNickname");
        result &= false; // should not reach here
    } catch (...) {
        result &= true;
    }

    std::cout << "4) Test setting a nickname when client status is disconnected:" << std::endl;
    c1.setStatus(Client::DISCONNECTED);
    try {
        cl.setNick(1, "anotherNick");
        result &= false; // should not reach here
    } catch (...) {
        result &= true;
    }

    std::cout << "5) Test setting a nickname when nickname is already in use:" << std::endl;
    Client& c2 = cl.clients[2];
    c2.setStatus(Client::AUTHENTICATED);
    cl.setNick(2, "uniqueNick");
    try {
        cl.setNick(1, "uniqueNick");
        result &= false; // should not reach here
    } catch (...) {
        result &= true;
    }

    return (result);
}*/

bool    TestClientGetAndSetUser(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::getUser and Client::setUser method:" << "\033[0m" << std::endl;
    bool    result = true;

   Client  client = createClient(0);

    std::cout << "1) Test if the default user is an empty string:" << std::endl;
    result &= ASSERT_EQ(client.getUser(), "");

    client.setUser("TestUser");

    std::cout << "2) Test if getUser returns 'TestUser' after setting it:" << std::endl;
    result &= ASSERT_EQ(client.getUser(), "TestUser");

    client.setUser("NewUser");

    std::cout << "3) Test if getUser returns 'NewUser' after updating it:" << std::endl;
    result &= ASSERT_EQ(client.getUser(), "NewUser");

    client.setUser("");
    std::cout << "4) Test if getUser returns an empty string when the user is set to empty:" << std::endl;
    result &= ASSERT_EQ(client.getUser(), "");

    client.setUser("A");
    std::cout << "5) Test if getUser returns 'A' for a one-character user:" << std::endl;
    result &= ASSERT_EQ(client.getUser(), "A");

    client.setUser("MultipleCharsUser");
    std::cout << "6) Test if getUser returns 'MultipleCharsUser' for a multi-character user:" << std::endl;
    result &= ASSERT_EQ(client.getUser(), "MultipleCharsUser");

    return (result);
}

bool    TestClientGetAndSetHost(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::getHost  and Client::setHost method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client  client = createClient(0);

    std::cout << "1) Test if the default host is an empty string:" << std::endl;
    result &= ASSERT_EQ(client.getHost(), "");

    client.setHost("TestHost");

    std::cout << "2) Test if getHost returns 'TestHost' after setting it:" << std::endl;
    result &= ASSERT_EQ(client.getHost(), "TestHost");

    client.setHost("NewHost");

    std::cout << "3) Test if getHost returns 'NewHost' after updating it:" << std::endl;
    result &= ASSERT_EQ(client.getHost(), "NewHost");

    client.setHost("");
    std::cout << "4) Test if getHost returns an empty string when the host is set to empty:" << std::endl;
    result &= ASSERT_EQ(client.getHost(), "");

    client.setHost("A");
    std::cout << "5) Test if getHost returns 'A' for a one-character host:" << std::endl;
    result &= ASSERT_EQ(client.getHost(), "A");

    client.setHost("MultipleCharsHost");
    std::cout << "6) Test if getHost returns 'MultipleCharsHost' for a multi-character host:" << std::endl;
    result &= ASSERT_EQ(client.getHost(), "MultipleCharsHost");

    return (result);
}

bool    TestClientGetFullId(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::getFullId method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client  client = createClient(0);

    client.setNick("nick");
    client.setUser("user");
    client.setHost("host");

    std::string expectedFullId = "nick!user@host";
    std::cout << "1) Test if getFullId returns 'nick!user@host':" << std::endl;
    result &= ASSERT_EQ(client.getFullId(), expectedFullId);

    client.setNick("");
    client.setUser("");
    client.setHost("");
    expectedFullId = "!@";
    std::cout << "2) Test if getFullId returns '!@' when nick, user, and host are empty:" << std::endl;
    result &= ASSERT_EQ(client.getFullId(), expectedFullId);

    client.setNick("");
    client.setUser("user");
    client.setHost("host");
    expectedFullId = "!user@host";
    std::cout << "3) Test if getFullId returns '!user@host' when nick is empty:" << std::endl;
    result &= ASSERT_EQ(client.getFullId(), expectedFullId);

    client.setNick("nick");
    client.setUser("");
    client.setHost("host");
    expectedFullId = "nick!@host";
    std::cout << "4) Test if getFullId returns 'nick!@host' when user is empty:" << std::endl;
    result &= ASSERT_EQ(client.getFullId(), expectedFullId);

    client.setNick("nick");
    client.setUser("user");
    client.setHost("");
    expectedFullId = "nick!user@";
    std::cout << "5) Test if getFullId returns 'nick!user@' when host is empty:" << std::endl;
    result &= ASSERT_EQ(client.getFullId(), expectedFullId);

    client.setNick("nick");
    client.setUser("user");
    client.setHost("host");
    expectedFullId = "nick!user@host";
    std::cout << "6) Test if getFullId returns 'nick!user@host' with non-empty nick, user, and host:" << std::endl;
    result &= ASSERT_EQ(client.getFullId(), expectedFullId);

    client.setNick("nick#");
    client.setUser("user@");
    client.setHost("host!");
    expectedFullId = "nick#!user@host!";
    std::cout << "7) Test if getFullId returns 'nick#!user@host!' for special characters in nick, user, and host:" << std::endl;
    result &= ASSERT_EQ(client.getFullId(), expectedFullId);

    return (result);
}

bool    TestClientGetAndSetFD(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::setFD and  Client::getFD methods:" << "\033[0m" << std::endl;
    bool    result = true;

    Client  client = createClient(42);

    std::cout << "1) Test if getFD returns the correct file descriptor (42):" << std::endl;
    result &= ASSERT_EQ(client.getFD(), 42);

    int newFD = 56;
    client.setFD(newFD);
    std::cout << "2) Test if getFD returns the correct file descriptor after setting it to " << newFD << ":" << std::endl;
    result &= ASSERT_EQ(client.getFD(), newFD);

    int newFD1 = 42;
    client.setFD(newFD1);
    std::cout << "3) Test if getFD returns the initial file descriptor (42) after resetting it:" << std::endl;
    result &= ASSERT_EQ(client.getFD(), newFD1);

    int newFD2 = 0;
    client.setFD(newFD2);
    std::cout << "4) Test if getFD returns the correct file descriptor (0) when set to 0:" << std::endl;
    result &= ASSERT_EQ(client.getFD(), newFD2);

    int newFD3 = -1;
    client.setFD(newFD3);
    std::cout << "5) Test if getFD returns the correct file descriptor (-1) when set to -1:" << std::endl;
    result &= ASSERT_EQ(client.getFD(), newFD3);

    int newFD4 = 9999;
    client.setFD(newFD4);
    std::cout << "6) Test if getFD returns the correct file descriptor (9999) when set to 9999:" << std::endl;
    result &= ASSERT_EQ(client.getFD(), newFD4);

    return (result);
}

bool    TestClientGetChannelList(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::getChannelList method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client  client = createClient(42);

    std::cout << "1) Test if getChannelList returns an empty list initially:" << std::endl;
    result &= ASSERT_TRUE(client.getChannelList().empty());

    std::cout << "2) Test if getChannelList returns the correct list after adding a channel:" << std::endl;
    client.addChannel("#channel1");
    result &= ASSERT_EQ(client.getChannelList().size(), 1);
    result &= ASSERT_TRUE(client.getChannelList().count("#channel1") > 0);

    std::cout << "3) Test if getChannelList returns the correct list after adding multiple channels:" << std::endl;
    client.addChannel("#channel2");
    client.addChannel("#channel3");
    result &= ASSERT_EQ(client.getChannelList().size(), 3);
    result &= ASSERT_TRUE(client.getChannelList().count("#channel1") > 0);
    result &= ASSERT_TRUE(client.getChannelList().count("#channel2") > 0);
    result &= ASSERT_TRUE(client.getChannelList().count("#channel3") > 0);

    std::cout << "4) Test if getChannelList returns the correct list after removing a channel:" << std::endl;
    client.removeChannel("#channel2");
    result &= ASSERT_EQ(client.getChannelList().size(), 2);
    result &= ASSERT_TRUE(client.getChannelList().count("#channel1") > 0);
    result &= ASSERT_FALSE(client.getChannelList().count("#channel2") > 0);
    result &= ASSERT_TRUE(client.getChannelList().count("#channel3") > 0);

    std::cout << "5) Test if getChannelList returns the correct list after removing all channels:" << std::endl;
    client.removeChannel("#channel1");
    client.removeChannel("#channel3");
    result &= ASSERT_TRUE(client.getChannelList().empty());

    return (result);
}

bool    TestClientGetAndSetStatus(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::getStatus method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client client1 = createClient(0);
    std::cout << "1) Test if getStatus returns the default status (UNKNOWN):" << std::endl;
    result &= ASSERT_EQ(client1.getStatus(), Client::UNKNOWN);

    client1.setStatus(Client::CONNECTED);
    std::cout << "2) Test if getStatus returns the status (CONNECTED) after setting it:" << std::endl;
    result &= ASSERT_EQ(client1.getStatus(), Client::CONNECTED);

    client1.setStatus(Client::AUTHENTICATED);
    std::cout << "3) Test if getStatus returns the status (AUTHENTICATED) after setting it:" << std::endl;
    result &= ASSERT_EQ(client1.getStatus(), Client::AUTHENTICATED);

    client1.setStatus(Client::GOT_USER);
    std::cout << "4) Test if getStatus returns the status (GOT_USER) after setting it:" << std::endl;
    result &= ASSERT_EQ(client1.getStatus(), Client::GOT_USER);

    client1.setStatus(Client::REGISTERED);
    std::cout << "5) Test if getStatus returns the status (REGISTERED) after setting it:" << std::endl;
    result &= ASSERT_EQ(client1.getStatus(), Client::REGISTERED);

    return (result);
}

bool    TestClientGetModeFlags(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::getModeFlags method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client client = createClient(42);

    std::cout << "1) Test if getModeFlags returns 0 for a new client:" << std::endl;
    result &= ASSERT_EQ(client.getModeFlags(), 0);

    int modeFlags = Client::AWAY | Client::INVISIBLE;
    client.setMode("+a");
    client.setMode("+i");
    std::cout << "2) Test if getModeFlags returns correct flags after setting +a and +i:" << std::endl;
    result &= ASSERT_EQ(client.getModeFlags(), modeFlags);

    modeFlags = Client::INVISIBLE;
    client.setMode("-a");
    std::cout << "3) Test if getModeFlags returns correct flags after setting -a:" << std::endl;
    result &= ASSERT_EQ(client.getModeFlags(), modeFlags);

    modeFlags = 0;
    client.setMode("-i");
    std::cout << "4) Test if getModeFlags returns correct flags after setting -i:" << std::endl;
    result &= ASSERT_EQ(client.getModeFlags(), modeFlags);

    modeFlags = Client::OPERATOR | Client::RECV_NOTICES;
    client.setMode("+o");
    client.setMode("+s");
    std::cout << "5) Test if getModeFlags returns correct flags after setting +o and +s:" << std::endl;
    result &= ASSERT_EQ(client.getModeFlags(), modeFlags);

    return (result);
}

bool    TestClientSetModeFlags(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::setModeFlags method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client  client = createClient(42);

    std::cout << "1) Test if setModeFlags sets mode flags to 0:" << std::endl;
    client.setModeFlags(0);
    result &= ASSERT_EQ(client.getModeFlags(), 0);

    int modeFlags = Client::AWAY;
    std::cout << "2) Test if setModeFlags sets mode flags to AWAY:" << std::endl;
    client.setModeFlags(modeFlags);
    result &= ASSERT_EQ(client.getModeFlags(), modeFlags);

    modeFlags = Client::INVISIBLE;
    std::cout << "3) Test if setModeFlags sets mode flags to INVISIBLE:" << std::endl;
    client.setModeFlags(modeFlags);
    result &= ASSERT_EQ(client.getModeFlags(), modeFlags);

    modeFlags = Client::OPERATOR | Client::RECV_NOTICES;
    std::cout << "4) Test if setModeFlags sets mode flags to OPERATOR and RECV_NOTICES:" << std::endl;
    client.setModeFlags(modeFlags);
    result &= ASSERT_EQ(client.getModeFlags(), modeFlags);

    modeFlags = Client::AWAY | Client::INVISIBLE | Client::RESTRICTED;
    std::cout << "5) Test if setModeFlags sets mode flags to AWAY, INVISIBLE, and RESTRICTED:" << std::endl;
    client.setModeFlags(modeFlags);
    result &= ASSERT_EQ(client.getModeFlags(), modeFlags);

    return (result);
}

bool    TestClientGetMode(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::getMode method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client  client = createClient(42);

    std::cout << "1) Test if getMode returns false for AWAY mode when not set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::AWAY), false);

    client.setMode("+a");
    std::cout << "2) Test if getMode returns true for AWAY mode when set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::AWAY), true);

    client.setMode("-a");
    std::cout << "3) Test if getMode returns false for AWAY mode after removal:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::AWAY), false);

    std::cout << "4) Test if getMode returns false for INVISIBLE mode when not set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::INVISIBLE), false);

    client.setMode("+i");
    std::cout << "5) Test if getMode returns true for INVISIBLE mode when set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::INVISIBLE), true);

    client.setMode("-i");
    std::cout << "6) Test if getMode returns false for INVISIBLE mode after removal:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::INVISIBLE), false);

    std::cout << "7) Test if getMode returns false for WALLOPS mode when not set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::WALLOPS), false);

    client.setMode("+w");
    std::cout << "8) Test if getMode returns true for WALLOPS mode when set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::WALLOPS), true);

    client.setMode("-w");
    std::cout << "9) Test if getMode returns false for WALLOPS mode after removal:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::WALLOPS), false);

    std::cout << "10) Test if getMode returns false for RESTRICTED mode when not set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::RESTRICTED), false);

    client.setMode("+r");
    std::cout << "11) Test if getMode returns true for RESTRICTED mode when set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::RESTRICTED), true);

    client.setMode("-r");
    std::cout << "12) Test if getMode returns false for RESTRICTED mode after removal:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::RESTRICTED), false);

    std::cout << "13) Test if getMode returns false for OPERATOR mode when not set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::OPERATOR), false);

    client.setMode("+o");
    std::cout << "14) Test if getMode returns true for OPERATOR mode when set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::OPERATOR), true);

    client.setMode("-o");
    std::cout << "15) Test if getMode returns false for OPERATOR mode after removal:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::OPERATOR), false);

    std::cout << "16) Test if getMode returns false for LOCAL_OP mode when not set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::LOCAL_OP), false);

    client.setMode("+O");
    std::cout << "17) Test if getMode returns true for LOCAL_OP mode when set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::LOCAL_OP), true);

    client.setMode("-O");
    std::cout << "18) Test if getMode returns false for LOCAL_OP mode after removal:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::LOCAL_OP), false);

    std::cout << "19) Test if getMode returns false for RECV_NOTICES mode when not set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::RECV_NOTICES), false);

    client.setMode("+s");
    std::cout << "20) Test if getMode returns true for RECV_NOTICES mode when set:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::RECV_NOTICES), true);

    client.setMode("-s");
    std::cout << "21) Test if getMode returns false for RECV_NOTICES mode after removal:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::RECV_NOTICES), false);

    std::cout << "22) Test if getMode returns false for invalid mode:" << std::endl;
    client.setMode("+x");
    result &= ASSERT_EQ(client.getMode(Client::AWAY), false);

    return (result);
}

bool    TestClientSetMode(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::setMode method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client  client = createClient(0);

    client.setMode("+a");
    std::cout << "1) Test if the AWAY mode is set correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::AWAY), true);

    client.setMode("-a");
    std::cout << "2) Test if the AWAY mode is removed correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::AWAY), false);

    client.setMode("+i");
    std::cout << "3) Test if the INVISIBLE mode is set correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::INVISIBLE), true);

    client.setMode("-i");
    std::cout << "4) Test if the INVISIBLE mode is removed correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::INVISIBLE), false);

    client.setMode("+w");
    std::cout << "5) Test if the WALLOPS mode is set correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::WALLOPS), true);

    client.setMode("-w");
    std::cout << "6) Test if the WALLOPS mode is removed correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::WALLOPS), false);

    client.setMode("+r");
    std::cout << "7) Test if the RESTRICTED mode is set correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::RESTRICTED), true);

    client.setMode("-r");
    std::cout << "8) Test if the RESTRICTED mode is removed correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::RESTRICTED), false);

    client.setMode("+o");
    std::cout << "9) Test if the OPERATOR mode is set correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::OPERATOR), true);

    client.setMode("-o");
    std::cout << "10) Test if the OPERATOR mode is removed correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::OPERATOR), false);

    client.setMode("+O");
    std::cout << "11) Test if the LOCAL_OP mode is set correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::LOCAL_OP), true);

    client.setMode("-O");
    std::cout << "12) Test if the LOCAL_OP mode is removed correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::LOCAL_OP), false);

    client.setMode("+s");
    std::cout << "13) Test if the RECV_NOTICES mode is set correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::RECV_NOTICES), true);

    client.setMode("-s");
    std::cout << "14) Test if the RECV_NOTICES mode is removed correctly:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::RECV_NOTICES), false);

    client.setMode("+x");
    std::cout << "15) Test if invalid mode does not change any mode flags:" << std::endl;
    result &= ASSERT_EQ(client.getMode(Client::AWAY), false);

    return (result);
}

bool    TestClientIsInChannel(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::isInChannel method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client client = createClient(0);

    std::cout << "1) Test if isInChannel returns false for a channel the client is not in:" << std::endl;
    result &= ASSERT_FALSE(client.isInChannel("#testChannel"));

    client.addChannel("#testChannel");
    std::cout << "2) Test if isInChannel returns true for a channel the client was added to:" << std::endl;
    result &= ASSERT_TRUE(client.isInChannel("#testChannel"));

    client.removeChannel("#testChannel");
    std::cout << "3) Test if isInChannel returns false for a channel the client was removed from:" << std::endl;
    result &= ASSERT_FALSE(client.isInChannel("#testChannel"));

    client.addChannel("#anotherChannel");
    std::cout << "4) Test if isInChannel returns true for another channel the client was added to:" << std::endl;
    result &= ASSERT_TRUE(client.isInChannel("#anotherChannel"));

    return (result);
}

bool    TestClientAddChannel(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::addChannel method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client client = createClient(0);

    std::cout << "1) Test if addChannel correctly adds a new channel to the client's channel list:" << std::endl;
    client.addChannel("#testChannel");
    result &= ASSERT_TRUE(client.isInChannel("#testChannel"));

    std::cout << "2) Test if addChannel does not duplicate channels in the client's channel list:" << std::endl;
    client.addChannel("#testChannel");
    std::set<std::string> channelList = client.getChannelList();
    result &= ASSERT_EQ(channelList.count("#testChannel"), 1);

    std::cout << "3) Test if addChannel correctly adds multiple channels to the client's channel list:" << std::endl;
    client.addChannel("#anotherChannel");
    result &= ASSERT_TRUE(client.isInChannel("#testChannel"));
    result &= ASSERT_TRUE(client.isInChannel("#anotherChannel"));

    return (result);
}

bool    TestClientRemoveChannel(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::removeChannel method:" << "\033[0m" << std::endl;
    bool    result = true;

    Client client = createClient(0);

    client.addChannel("#testChannel");
    client.addChannel("#anotherChannel");

    std::cout << "1) Test if removeChannel correctly removes a channel from the client's channel list:" << std::endl;
    client.removeChannel("#testChannel");
    result &= ASSERT_FALSE(client.isInChannel("#testChannel"));

    std::cout << "2) Test if removeChannel does not affect other channels in the client's channel list:" << std::endl;
    result &= ASSERT_TRUE(client.isInChannel("#anotherChannel"));

    std::cout << "3) Test if removeChannel does nothing when the channel is not in the client's channel list:" << std::endl;
    client.removeChannel("#nonExistentChannel");
    result &= ASSERT_TRUE(client.isInChannel("#anotherChannel"));
    result &= ASSERT_FALSE(client.isInChannel("#nonExistentChannel"));

    std::cout << "4) Test if removeChannel works correctly after multiple additions and removals:" << std::endl;
    client.addChannel("#newChannel");
    result &= ASSERT_TRUE(client.isInChannel("#newChannel"));
    client.removeChannel("#newChannel");
    result &= ASSERT_FALSE(client.isInChannel("#newChannel"));
    client.removeChannel("#anotherChannel");
    result &= ASSERT_FALSE(client.isInChannel("#anotherChannel"));

    return (result);
}

void    mockSendMessage(int fd, const std::string &msg) {
    std::cerr << "Mock sendMessage called with fd: " << fd << " and msg: " << msg << std::endl;
}

bool    TestClientSendMessage(void) {
    std::cout << "\033[0;34m" << "\nTesting Client::sendMessage method:" << "\033[0m" << std::endl;
    bool    result = true;

    MsgHandler dummyMsgHandler;
    std::string dummyHost = "localhost";
    TestClient client(42, dummyMsgHandler, dummyHost);

    std::string msg1 = "Hello, World!";
    std::string msg2 = "Test message";
    std::string msg3 = "Another test message";

    std::cout << "1) Test if sendMessage correctly calls MockIRCServer::sendMessage with 'Hello, World!':" << std::endl;
    client.sendMessage(msg1);

    std::cout << "2) Test if sendMessage correctly calls MockIRCServer::sendMessage with 'Test message':" << std::endl;
    client.sendMessage(msg2);

    std::cout << "3) Test if sendMessage correctly calls MockIRCServer::sendMessage with 'Another test message':" << std::endl;
    client.sendMessage(msg3);

    return (result);
}
