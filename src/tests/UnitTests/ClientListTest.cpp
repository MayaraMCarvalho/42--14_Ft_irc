/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientListTest.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:16:44 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/23 21:18:47 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./TestFramework.hpp"

bool    TestDefaultConstructorClientList(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);

    std::cout << "\033[0;34m" << "\nTesting default constructor:" << "\033[0m" << std::endl;
    std::cout << "1) Check if the default constructor initializes correctly:" << std::endl;
    return (ASSERT_ITER_EQ(clientList.end(), clientList.end()));
}

bool    TestGetClientByNick(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);

    Client      client1(1, dummyMsgHandler, "host1");
    client1.setNick("nick1");
    client1.setUser("user1");

    Client      client2(2, dummyMsgHandler, "host2");
    client2.setNick("nick2");
    client2.setUser("user2");

    clientList.add(client1);
    clientList.add(client2);

    std::cout << "\033[0;34m" << "\nTesting getClientByNick method:" << "\033[0m" << std::endl;

    bool        result = true;

    std::cout << "1) Check that getClientByNick returns the correct client for an existing nick:" << std::endl;
    std::map<int, Client>::iterator it1 = clientList.getClientByNick("nick1");
    result &= ASSERT_ITER_EQ(it1, clientList.getClient(1));
    result &= ASSERT_EQ(it1->second.getNick(), "nick1");
    result &= ASSERT_EQ(it1->second.getUser(), "user1");

    std::cout << "2) Check that getClientByNick returns the correct client for another existing nick:" << std::endl;
    std::map<int, Client>::iterator it2 = clientList.getClientByNick("nick2");
    result &= ASSERT_ITER_EQ(it2, clientList.getClient(2));
    result &= ASSERT_EQ(it2->second.getNick(), "nick2");
    result &= ASSERT_EQ(it2->second.getUser(), "user2");

    std::cout << "3) Check that getClientByNick returns end() for a non-existent nick:" << std::endl;
    std::map<int, Client>::iterator it3 = clientList.getClientByNick("nonexistent_nick");
    result &= ASSERT_ITER_EQ(it3, clientList.getClient(3));

    std::cout << "4) Test getClientByNick with an empty nickname:" << std::endl;
    std::map<int, Client>::iterator it4 = clientList.getClientByNick("");
    result &= ASSERT_ITER_EQ(it4, clientList.getClient(3));
    
    std::cout << "5) Test getClientByNick with a very long nickname:" << std::endl;
    std::string longNick(1000, 'a');
    std::map<int, Client>::iterator it5 = clientList.getClientByNick(longNick);
    result &= ASSERT_ITER_EQ(it5, clientList.getClient(3));
    return (result);
}

bool    TestGetClientByUser(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);

    Client      client1(1, dummyMsgHandler, "host1");
    client1.setNick("nick1");
    client1.setUser("user1");

    Client      client2(2, dummyMsgHandler, "host2");
    client2.setNick("nick2");
    client2.setUser("user2");

    clientList.add(client1);
    clientList.add(client2);

    std::cout << "\033[0;34m" << "\nTesting getClientByUser method:" << "\033[0m" << std::endl;

    bool result = true;
    std::cout << "1) Tests whether getClientByUser returns the correct client for an existing user:" << std::endl;
    std::map<int, Client>::iterator it1 = clientList.getClientByUser("user1");
    result &= ASSERT_ITER_EQ(it1, clientList.getClient(1));
    result &= ASSERT_EQ(it1->second.getNick(), "nick1");
    result &= ASSERT_EQ(it1->second.getUser(), "user1");

    std::cout << "2) Tests whether getClientByUser returns the correct client for another existing user:" << std::endl;
    std::map<int, Client>::iterator it2 = clientList.getClientByUser("user2");
    result &= ASSERT_ITER_EQ(it2, clientList.getClient(2));
    result &= ASSERT_EQ(it2->second.getNick(), "nick2");
    result &= ASSERT_EQ(it2->second.getUser(), "user2");

    std::cout << "3) Tests whether getClientByUser returns end() for a non-existent user:" << std::endl;
    std::map<int, Client>::iterator it3 = clientList.getClientByUser("nonexistent_user");
    result &= ASSERT_ITER_EQ(it3, clientList.getClient(3));

    return (result);
}

bool    TestGetNick(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);

    Client      client1(1, dummyMsgHandler, "host1");
    client1.setNick("nick1");
    client1.setUser("user1");

    Client      client2(2, dummyMsgHandler, "host2");
    client2.setNick("nick2");
    client2.setUser("user2");

    clientList.add(client1);
    clientList.add(client2);

    std::cout << "\033[0;34m" << "\nTesting getNick method:" << "\033[0m" << std::endl;

    bool result = true;
    std::cout << "1) Tests whether getNick returns the correct nickname for an existing fd:" << std::endl;
    result &= ASSERT_EQ(clientList.getNick(1), "nick1");
    result &= ASSERT_EQ(clientList.getNick(2), "nick2");

    std::cout << "2) Tests whether getNick returns an empty string for a non-existent fd:" << std::endl;
    result &= ASSERT_EQ(clientList.getNick(3), "");

    return (result);
}

bool    TestGetUser(void) {
    MsgHandler dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList clientList(dummyMsgHandler, dummyPollFds);

    Client      client1(1, dummyMsgHandler, "host1");
    client1.setNick("nick1");
    client1.setUser("user1");

    Client      client2(2, dummyMsgHandler, "host2");
    client2.setNick("nick2");
    client2.setUser("user2");

    clientList.add(client1);
    clientList.add(client2);

    std::cout << "\033[0;34m" << "\nTesting getUser method:" << "\033[0m" << std::endl;

    bool result = true;
    std::cout << "1) Tests whether getUser returns the correct username for an existing fd:" << std::endl;
    result &= ASSERT_EQ(clientList.getUser(1), "user1");
    result &= ASSERT_EQ(clientList.getUser(2), "user2");

    std::cout << "2) Tests whether getUser returns an empty string for a non-existent fd:" << std::endl;
    result &= ASSERT_EQ(clientList.getUser(3), "");

    return (result);
}

bool    TestGetFDByNick(void) {
    MsgHandler dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList clientList(dummyMsgHandler, dummyPollFds);

    Client client1(1, dummyMsgHandler, "host1");
    client1.setNick("nick1");
    client1.setUser("user1");

    Client      client2(2, dummyMsgHandler, "host2");
    client2.setNick("nick2");
    client2.setUser("user2");

    clientList.add(client1);
    clientList.add(client2);

    std::cout << "\033[0;34m" << "\nTesting getFDByNick method:" << "\033[0m" << std::endl;

    bool        result = true;
    std::string nick1  = "nick1";
    std::string nick2  = "nick2";
    std::string nonexistentNick = "nonexistent";

    std::cout << "1) Tests whether getFDByNick returns the correct file descriptor for an existing nick:" << std::endl;
    result &= ASSERT_EQ(clientList.getFDByNick(nick1), 1);
    result &= ASSERT_EQ(clientList.getFDByNick(nick2), 2);

    std::cout << "2) Tests whether getFDByNick returns -1 for a non-existent nick:" << std::endl;
    result &= ASSERT_EQ(clientList.getFDByNick(nonexistentNick), -1);

    return (result);
}

bool    TestGetFDByUser(void) {
    MsgHandler  dummyMsgHandler;
    std::string dummyHost = "localhost";
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);

    Client      client1(1, dummyMsgHandler, dummyHost);
    Client      client2(2, dummyMsgHandler, dummyHost);

    client1.setNick("nick1");
    client1.setUser("user1");

    client2.setNick("nick2");
    client2.setUser("user2");

    clientList.add(client1);
    clientList.add(client2);

    std::cout << "\033[0;34m" << "\nTesting getFDByUser method:" << "\033[0m" << std::endl;

    bool result = true;
    std::cout << "1) Tests whether getFDByUser returns the correct file descriptor for an existing user:" << std::endl;
    std::string user1 = "user1";
    std::string user2 = "user2";
    result &= ASSERT_EQ(clientList.getFDByUser(user1), 1);
    result &= ASSERT_EQ(clientList.getFDByUser(user2), 2);

    std::cout << "2) Tests whether getFDByUser returns -1 for a non-existent user:" << std::endl;
    std::string nonexistentUser = "nonexistent";
    result &= ASSERT_EQ(clientList.getFDByUser(nonexistentUser), -1);

    return (result);
}

bool    TestEnd(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);

    Client      client1(1, dummyMsgHandler, "host1");
    client1.setNick("nick1");
    client1.setUser("user1");

    clientList.add(client1);

    std::cout << "\033[0;34m" << "\nTesting ClientList::end method:" << "\033[0m" << std::endl;

    bool        result = true;

    std::map<int, Client>::iterator itEnd  = clientList.end();
    std::map<int, Client>::iterator itFind = clientList.getClient(2);

    std::cout << "1) Checks whether the iterator returned by end() is different from a valid iterator:" << std::endl;
    result &= ASSERT_ITER_EQ(itEnd, clientList.getClientByNick("invalidNick"));

    Client      client2(2, dummyMsgHandler, "host2");
    client2.setNick("nick2");
    client2.setUser("user2");
    clientList.add(client2);

    itEnd  = clientList.end();
    itFind = clientList.getClient(3);

    result &= ASSERT_ITER_EQ(itEnd, clientList.getClientByNick("anotherInvalidNick"));
    result &= ASSERT_ITER_EQ(itFind, itEnd);

    return (result);
}

bool    TestSetNick(void) {
    bool        result = true;
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);

    Client      client1(1, dummyMsgHandler, "host1");
    client1.setNick("oldNick");
    client1.setUser("user1");
    client1.setStatus(Client::AUTHENTICATED);

    clientList.add(client1);

    std::cout << "\033[0;34m" << "\nTesting ClientList::setNick method:" << "\033[0m" << std::endl;

    std::string newNick = "newNick";
    clientList.setNick(1, newNick);
    client1.setStatus(Client::AUTHENTICATED);

    std::cout << "1) Check if the nickname was updated correctly:" << std::endl;
    std::map<int, Client>::iterator it = clientList.getClient(1);
    result &= ASSERT_ITER_EQ(it->second.getNick(), newNick);

    std::string invalidNick = "invalidNick";
    clientList.setNick(2, invalidNick);

    std::cout << "2) Checks that the nickname for fd 1 has not been changed:" << std::endl;
    it = clientList.getClient(1);
    result &= ASSERT_ITER_EQ(it->second.getNick(), newNick);

    std::cout << "3) Checks if getClient returns end() for non-existent fd:" << std::endl;
    std::map<int, Client>::iterator itInvalid = clientList.getClient(2);
    result &= ASSERT_ITER_EQ(itInvalid == clientList.end(), true);

    return (result);
}

bool    TestSetUser(void) {
    bool result = true;
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);

    Client      client1(1, dummyMsgHandler, "host1");
    client1.setNick("nick1");
    client1.setUser("oldUser");
    client1.setStatus(Client::AUTHENTICATED);

    clientList.getClient(1)->second.setStatus(Client::AUTHENTICATED);

    clientList.add(client1);

    std::cout << "\033[0;34m" << "\nTesting ClientList::setUser method:" << "\033[0m" << std::endl;

    std::string newUser = "newUser";
    clientList.setUser(1, newUser);

    std::cout << "1) Checks if the user was updated correctly:" << std::endl;
    std::map<int, Client>::iterator it = clientList.getClient(1);
    result &= ASSERT_ITER_EQ(it->second.getUser(), newUser);

    std::cout << "2) Checks that the user for fd 1 has not been changed:" << std::endl;
    it = clientList.getClient(1);
    result &= ASSERT_ITER_EQ(it->second.getUser(), newUser);

    std::cout << "3) Checks if getClient returns end() for non-existent fd:" << std::endl;
    std::map<int, Client>::iterator itInvalid = clientList.getClient(2);
    result &= ASSERT_ITER_EQ(itInvalid == clientList.end(), true);

    return (result);
}

bool    TestAddClient(void) {
    std::vector<struct pollfd>  dummyPollFds;
    MsgHandler  dummyMsgHandler;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);

    std::cout << "\033[0;34m" << "\nTesting ClientList::add method:" << "\033[0m" << std::endl;
    bool result = true;

    std::cout << "1) Test adding a new client:" << std::endl;
    Client      client1(10, dummyMsgHandler, "host1");
    client1.setNick("nick1");
    client1.setUser("user1");
    clientList.add(client1);
    std::string user1 = "user1";
    std::string nick1 = "nick1";
    std::map<int, Client>::iterator it1 = clientList.getClient(10);
    result &= ASSERT_ITER_NOT_END(it1, clientList.getClient(10));
    result &= ASSERT_EQ(it1->second.getNick(), nick1);
    result &= ASSERT_EQ(it1->second.getUser(), user1);

    std::cout << "2) Try adding another client:" << std::endl;
    Client      client2(2, dummyMsgHandler, "host2");
    client2.setNick("nick2");
    client2.setUser("user2");
    clientList.add(client2);
    std::map<int, Client>::iterator it2 = clientList.getClient(2);
    result &= ASSERT_ITER_NOT_END(it2, clientList.getClient(2));
    result &= ASSERT_EQ(it2->second.getNick(), "nick2");
    result &= ASSERT_EQ(it2->second.getUser(), "user2");

    std::cout << "3) Test adding a client with a nickname that already exists:" << std::endl;
    Client      client5(5, dummyMsgHandler, "host5");
    client5.setNick("nick1");
    client5.setUser("user5");
    clientList.add(client5);
    std::map<int, Client>::iterator it5 = clientList.getClient(5);
    result &= ASSERT_ITER_END(it5, clientList.getClient(5));

    std::cout << "4) Test adding a client with a user that already exists:" << std::endl;
    Client      client6(6, dummyMsgHandler, "host6");
    client6.setNick("nick6");
    client6.setUser("user1");
    clientList.add(client6);
    std::map<int, Client>::iterator it6 = clientList.getClient(6);
    result &= ASSERT_ITER_END(it6, clientList.getClient(6));

    std::cout << "5) Test adding a valid client:" << std::endl;
    Client      client3(3, dummyMsgHandler, "host3");
    client3.setNick("nick3");
    client3.setUser("user3");
    clientList.add(client3);
    std::map<int, Client>::iterator it3 = clientList.getClient(3);
    result &= ASSERT_ITER_NOT_END(it3, clientList.getClient(3));
    result &= ASSERT_EQ(it3->second.getNick(), "nick3");
    result &= ASSERT_EQ(it3->second.getUser(), "user3");

    std::cout << "6) Test adding a client with a different nickname and username:" << std::endl;
    Client      client4(4, dummyMsgHandler, "host4");
    client4.setNick("nick4");
    client4.setUser("user4");
    clientList.add(client4);
    std::map<int, Client>::iterator it4 = clientList.getClient(4);
    result &= ASSERT_ITER_NOT_END(it4, clientList.getClient(4));
    result &= ASSERT_EQ(it4->second.getNick(), "nick4");
    result &= ASSERT_EQ(it4->second.getUser(), "user4");

    std::cout << "7) Tests for the existence of entries in _nickToClient and _userToClient:" << std::endl;
    std::map<int, Client>::iterator itNick = clientList.getClientByNick("nick4");
    result &= ASSERT_ITER_NOT_END(itNick, clientList.getClientByNick("nick4"));
    result &= ASSERT_EQ(itNick->second.getUser(), "user4");

    std::map<int, Client>::iterator itUser = clientList.getClientByUser("user4");
    result &= ASSERT_ITER_NOT_END(itUser->first, clientList.getClientByUser("user4")->first);
    result &= ASSERT_EQ(itUser->second.getNick(), "nick4");

    return (result);
}

bool    TestAddClientWithAddress(void) {
    std::cout << "\033[0;34m" << "\nTesting add method with address:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList clientList(dummyMsgHandler, dummyPollFds);
    std::string hostname = "127.0.0.1";

    clientList.add(1, hostname);
    
    std::cout << "1) Test whether the client correctly added the fd and hostname with the method:" << std::endl;
    std::map<int, Client>::iterator client = clientList.getClient(1);

    result &= ASSERT_EQ(client->first, 1);
    result &= ASSERT_EQ(client->second.getHost(), hostname);
    return (result);
}

bool    TestAddMultipleClients(void) {
    bool        result = true;
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);
    std::string hostname1 = "192.168.0.1";
    std::string hostname2 = "127.0.0.1";

    clientList.add(1, hostname1);
    clientList.add(2, hostname2);

    std::cout << "2) Testing the add method with address and multiple clients:" << std::endl;
    
    std::map<int, Client>::iterator client1 = clientList.getClient(1);

    result &= ASSERT_EQ(client1->first, 1);
    result &= ASSERT_EQ(client1->second.getHost(), hostname1);
    
    std::map<int, Client>::iterator client2 = clientList.getClient(2);
    result &= ASSERT_EQ(client2->first, 2);
    result &= ASSERT_EQ(client2->second.getHost(), hostname2);
    return (result);
}

bool    TestAddClientWithSameFd(void) {
    bool        result = true;
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);
    std::string hostname1 = "192.168.0.2";
    std::string hostname2 = "127.0.0.1";

    clientList.add(1, hostname1);
    clientList.add(1, hostname2);

    std::cout << "3) Testing the add method with address and same fd:" << std::endl;
    
    std::map<int, Client>::iterator client = clientList.getClient(1);

    result &= ASSERT_EQ(client->first, 1);
    result &= ASSERT_EQ(client->second.getHost(), hostname1);
    return (result);
}

bool    TestAddClientWithHostname(void) {
    std::cout << "\033[0;34m" << "\nTesting add method with hostname:" << "\033[0m" << std::endl;
    bool        result = true;
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);
    std::string hostname = "127.0.0.1";
    clientList.add(1, hostname);

    std::cout << "1) Test whether the client correctly added the fd and hostname with the method:" << std::endl;
    std::map<int, Client>::iterator client = clientList.getClient(1);

    result &= ASSERT_EQ(client->first, 1);
    result &= ASSERT_EQ(client->second.getHost(), hostname);
    
    return (result);
}

bool    TestRemoveClient(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);
    Client      client(1, dummyMsgHandler, "host1");
    std::string nick = "nick";
    std::string user = "user";
    bool        result;

    client.setNick(nick);
    client.setUser(user);
    clientList.add(client);
    clientList.remove(1);

    std::cout << "\033[0;34m" << "\nTesting remove method:" << "\033[0m" << std::endl;
    std::cout << "1) Test whether the client is correctly removed from the client list (ClientList):" << std::endl;
    result = ASSERT_ITER_EQ(clientList.getClient(1), clientList.end());
    return (result);
}

bool    TestRemoveClientByNick(void) {
    std::cout << "\033[0;34m" << "\nTesting removeByNick method:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);
    Client      client1(1, dummyMsgHandler, "host1");
    client1.setNick("nick1");
    client1.setUser("user1");

    Client      client2(2, dummyMsgHandler, "host2");
    client2.setNick("nick2");
    client2.setUser("user2");

    clientList.add(client1);
    clientList.add(client2);

    std::string nickToRemove = "nick1";
    clientList.removeByNick(nickToRemove);

    std::cout << "1) Test whether the client with nick 'nick1' was removed:" << std::endl;
    result &= ASSERT_ITER_END(clientList.getClientByNick("nick1"), clientList.end());
    result &= ASSERT_ITER_NOT_END(clientList.getClientByNick("nick2"), clientList.end());

    return (result);
}

bool    TestRemoveClientByUser(void) {
    std::cout << "\033[0;34m" << "\nTesting removeByUser method:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);
    Client      client1(1, dummyMsgHandler, "host1");
    client1.setNick("nick1");
    client1.setUser("user1");

    Client      client2(2, dummyMsgHandler, "host2");
    client2.setNick("nick2");
    client2.setUser("user2");

    clientList.add(client1);
    clientList.add(client2);

    std::string userToRemove = "user1";
    clientList.removeByUser(userToRemove);

    std::cout << "1) Test whether the client with user 'user1' was removed:" << std::endl;
    result &= ASSERT_ITER_END(clientList.getClientByUser("user1"), clientList.end());
    result &= ASSERT_ITER_NOT_END(clientList.getClientByUser("user2"), clientList.end());

    std::cout << "2) Test whether the nick corresponding to 'user1' was removed from the map:" << std::endl;
    result &= ASSERT_ITER_END(clientList.getClientByNick("nick1"), clientList.end());
    result &= ASSERT_ITER_NOT_END(clientList.getClientByNick("nick2"), clientList.end());

    return (result);
}

/*bool    TestUpdateNick(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);    Client      client(1, dummyMsgHandler, "host1");
    std::string oldNick = "oldNick";
    std::string newNick = "newNick";
    bool        result  = true;

    std::cout << "\033[0;34m" << "\nTesting updateNick method:" << "\033[0m" << std::endl;

    try {
        client.setNick(oldNick);
        client.setStatus(Client::AUTHENTICATED);
        clientList.add(client);
        clientList.updateNick(1, newNick);

        std::cout << "1) Checks if the new nickname is correct:" << std::endl;
        result &= ASSERT_EQ(clientList.getClientByNick(newNick)->second.getNick(), newNick);
        std::cout << "2) Checks if the old nickname has been removed:" << std::endl;
        result &= ASSERT_ITER_EQ(clientList.getClientByNick(oldNick), clientList.end());
    } catch (const std::invalid_argument& e) {
        std::cerr << "Caught std::invalid_argument: " << e.what() << std::endl;
        result &= false;
    } catch (const std::exception& e) {
        std::cerr << "Caught std::exception: " << e.what() << std::endl;
        result &= false;
    }

    return (result);
}

bool    TestUpdateUser(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);
    Client client(1, dummyMsgHandler, "host1");
    std::string oldUser = "oldUser";
    std::string newUser = "newUser";
    bool        result  = true;

    client.setUser(oldUser);
    client.setStatus(Client::AUTHENTICATED);
    clientList.add(client);
    clientList.updateUser(1, newUser);

    std::cout << "\033[0;34m" << "\nTesting updateUser method:" << "\033[0m" << std::endl;
    std::cout << "1) Check if newUser is in the ClientList:" << std::endl;
    result &= ASSERT_ITER_EQ(clientList.getClientByUser(newUser)->second.getUser(), newUser);
    std::cout << "2) Check if the old user has been removed:" << std::endl;
    result &= ASSERT_ITER_EQ(clientList.getClientByUser(oldUser), clientList.end());
    return (result);
}*/

bool    TestIsValidNick(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);
    bool        result = true;

    std::cout << "\033[0;34m" << "\nTesting isValidNick method:" << "\033[0m" << std::endl;
    
    std::cout << "1) Test empty nick:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidNick(""), false);

    std::cout << "2) Test nick with more than 9 characters:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidNick("abcdefghij"), false);

    std::cout << "3) Test valid nick with alphabetic characters only:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidNick("nickname"), true);

    std::cout << "4) Test valid nick with special characters:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidNick("nick_name"), true);

    std::cout << "5) Test valid nick with alphanumeric characters:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidNick("nick123"), true);

    std::cout << "6) Test nick starting with a non-alphabetic character:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidNick("1nickname"), false);

    std::cout << "7) Test nick with invalid special characters:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidNick("nick@name"), false);

    std::cout << "8) Test nick with hyphen:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidNick("nick-name"), true);

    std::cout << "9) Test nick starting with special character:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidNick("_nickname"), true);

    return (result);
}

bool    TestIsValidUser(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);
    bool        result = true;

    std::cout << "\033[0;34m" << "\nTesting isValidUser method:" << "\033[0m" << std::endl;
    
    std::cout << "1) Test empty user:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidUser(""), false);

    std::cout << "2) Test user with valid characters:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidUser("validuser"), true);

    std::cout << "3) Test user with space character:" << std::endl;
    result &= ASSERT_EQ(clientList.isValidUser("user name"), false);

    std::cout << "4) Test user with control characters (0x01 to 0x1F except 0x0A and 0x0D):" << std::endl;
    result &= ASSERT_EQ(clientList.isValidUser("\x01\x02\x1F"), true);

    std::cout << "5) Test user with DEL character (0x7F):" << std::endl;
    result &= ASSERT_EQ(clientList.isValidUser("\x7F"), false);

    std::cout << "6) Test user with printable characters (0x21 to 0x3F and 0x41 and above):" << std::endl;
    result &= ASSERT_EQ(clientList.isValidUser("user!#@"), true);

    std::cout << "7) Test user with invalid control character (0x0A):" << std::endl;
    result &= ASSERT_EQ(clientList.isValidUser("user\x0Aname"), false);

    std::cout << "8) Test user with invalid control character (0x0D):" << std::endl;
    result &= ASSERT_EQ(clientList.isValidUser("user\x0Dname"), false);

    return (result);
}

bool    TestIsSpecialChar(void) {
    MsgHandler  dummyMsgHandler;
    std::vector<struct pollfd> dummyPollFds;

    ClientList  clientList(dummyMsgHandler, dummyPollFds);
    bool        result = true;

    std::cout << "\033[0;34m" << "\nTesting isSpecialChar method:" << "\033[0m" << std::endl;
    
    std::cout << "1) Test '[' character (0x5B):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('['), true);

    std::cout << "2) Test '\\' character (0x5C):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('\\'), true);

    std::cout << "3) Test ']' character (0x5D):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar(']'), true);

    std::cout << "4) Test '^' character (0x5E):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('^'), true);

    std::cout << "5) Test '_' character (0x5F):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('_'), true);

    std::cout << "6) Test '`' character (0x60):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('`'), true);

    std::cout << "7) Test '{' character (0x7B):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('{'), true);

    std::cout << "8) Test '|' character (0x7C):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('|'), true);

    std::cout << "9) Test '}' character (0x7D):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('}'), true);

    std::cout << "10) Test '~' character (0x7E):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('~'), false);

    std::cout << "11) Test '@' character (0x40):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('@'), false);

    std::cout << "12) Test 'a' character (0x61):" << std::endl;
    result &= ASSERT_EQ(clientList.isSpecialChar('a'), false);

    return (result);
}
