/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelListTest.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:13:02 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/25 20:16:33 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/TestFramework.hpp"

bool    TestChannelListCopyConstructor(void) {
    std::cout << "\033[0;34m" << "\nTesting for ChannelList copy constructor:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    std::vector<struct pollfd> pollFds;
    ClientList  clientList(msgHandler, pollFds);
    ChannelList original(clientList, msgHandler);
    ChannelList copy(original);

    std::cout << "1) Test if the copy constructor correctly copies the channels map:" << std::endl;
    result &= ASSERT_EQ(original.size(), copy.size());

    std::cout << "2) Test if the internal channels map of the copy is the same as the original:" << std::endl;
    for (std::map<std::string, Channel>::iterator it = original.begin(); it != original.end(); ++it) {
        std::map<std::string, Channel>::const_iterator copyIt = copy.get(it->first);
        result &= ASSERT_EQ(it->first, copyIt->first);
    }

    return (result);
}

bool    TestChannelListAssignmentOperator(void) {
    std::cout << "\033[0;34m" << "\nTesting for ChannelList assignment operator:" << "\033[0m" << std::endl;
    bool    result = true;

    MsgHandler  msgHandler;
    std::vector<struct pollfd> pollFds;
    ClientList  clientList(msgHandler, pollFds);
    ChannelList original(clientList, msgHandler);
    ChannelList assigned(clientList, msgHandler);

    Channel channel1("Channel1", msgHandler);
    Channel channel2("Channel2", msgHandler);
    original.add(channel1);
    original.add(channel2);

    assigned = original;

    std::cout << "1) Test if the assignment operator correctly assigns the channels map:" << std::endl;
    result &= ASSERT_EQ(original.size(), assigned.size());

    std::cout << "2) Test if the internal channels map of the assigned list matches the original:" << std::endl;
    for (std::map<std::string, Channel>::iterator it = original.begin(); it != original.end(); ++it) {
        std::map<std::string, Channel>::const_iterator assignedIt = assigned.get(it->first);
        result &= ASSERT_EQ(it->first, assignedIt->first);
    }

    return (result);
}

bool    TestChannelListAdd(void) {
    std::cout << "\033[0;34m" << "\nTesting for ChannelList add method:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    std::vector<struct pollfd> pollFds;
    ClientList  clientList(msgHandler, pollFds);
    ChannelList channelList(clientList, msgHandler);

    Channel channel("TestChannel", msgHandler);
    channelList.add(channel);
    std::cout << "1) Test if the channel is correctly added to the list:" << std::endl;
    result &= ASSERT_EQ(channelList.size(), 1);

    std::cout << "2) Test if the added channel can be retrieved from the list:" << std::endl;
    std::map<std::string, Channel>::iterator it = channelList.get("TestChannel");
    result &= ASSERT_EQ(it->first, "TestChannel");

    return (result);
}

bool    TestChannelListJoin(void) {
    std::cout << "\033[0;34m" << "\nTesting for ChannelList join method:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    std::vector<struct pollfd> pollFds;
    ClientList  clientList(msgHandler, pollFds);
    ChannelList channelList(clientList, msgHandler);

    Client client1(1, msgHandler, "localhost");
    clientList.getClient(1);

    Channel channel("TestChannel", msgHandler);
    channelList.add(channel);

    std::cout << "1) Test if the user can join an existing channel:" << std::endl;
    channelList.join(1, "TestChannel", "");
    result &= ASSERT_TRUE(channel.getNumUsers() > 0);
    result &= ASSERT_TRUE(client1.getChannelList().count("TestChannel") > 0);

    std::cout << "2) Test if the user can join a new channel:" << std::endl;
    channelList.join(2, "NewChannel", "");
    Channel newChannel("NewChannel", msgHandler);
    result &= ASSERT_TRUE(channelList.get("NewChannel") != channelList.end());

    return (result);
}

bool    TestChannelListPart(void) {
    std::cout << "\033[0;34m" << "\nTesting for ChannelList part method:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    std::string dummyHost = "localhost";
    std::vector<struct pollfd> pollFds;
    ClientList  clientList(msgHandler, pollFds);
    ChannelList channelList(clientList, msgHandler);

    Client client1(1, msgHandler, dummyHost);
    clientList.getClient(1);
    Channel channel("TestChannel", msgHandler);
    channelList.add(channel);
    channelList.join(1, "TestChannel", "");

    std::cout << "1) Test if the user can part from a channel:" << std::endl;
    channelList.part(1, "TestChannel");
    //ChannelList::iterator chanIt = channelList.get("TestChannel");
    result &= ASSERT_FALSE(channel.getNumUsers() > 0);
    result &= ASSERT_FALSE(client1.getChannelList().count("TestChannel") > 0);

    result &= ASSERT_ITER_EQ(channelList.get("TestChannel"), channelList.end());

    return (result);
}

bool    TestChannelListPartDisconnectedClient(void) {
    std::cout << "\033[0;34m" << "\nTesting for ChannelList partDisconnectedClient method:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    std::string dummyHost = "192.168.0.2";
    MsgHandler  dummyMsgHandler1;
    MsgHandler  dummyMsgHandler2;
    std::vector<struct pollfd> pollFds;
    ClientList  clientList(msgHandler, pollFds);
    ChannelList channelList(clientList, msgHandler);

    Client client1(1, dummyMsgHandler1, dummyHost);
    Client client2(2, dummyMsgHandler2, dummyHost);
    clientList.add(1, dummyHost);
    clientList.add(2, dummyHost);

    Channel channel("TestChannel", msgHandler);
    channelList.add(channel);
    channelList.join(1, "TestChannel", "");
    channelList.join(2, "TestChannel", "");

    std::cout << "1) Test if all channels are removed for a disconnected client:" << std::endl;
    channelList.partDisconnectedClient(1);

    std::map<std::string, Channel>::iterator chanIt = channelList.get("TestChannel");
    result &= ASSERT_FALSE_ITER(chanIt->second.getNumUsers() > 0, chanIt);
    result &= ASSERT_TRUE_ITER(chanIt->second.getNumUsers() > 0, chanIt);


    return (result);
}

bool    TestChannelListUserCanJoin(void) {
    std::cout << "\033[0;34m" << "\nTesting for ChannelList userCanJoin method:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    std::string dummyHost = "localhost";
    std::vector<struct pollfd> pollFds;
    ClientList  clientList(msgHandler, pollFds);
    ChannelList channelList(clientList, msgHandler);

    Client client1(1, msgHandler, dummyHost);
    Client client2(2, msgHandler, dummyHost);
    clientList.add(1, dummyHost);
    clientList.add(2, dummyHost);

    Channel channel("TestChannel", msgHandler);
    channel.setKey("secret");
    channel.setUserLimit(10);
    channelList.add(channel);

    channelList.join(1, "TestChannel", "secret");

    std::cout << "1) Test if user can join channel with correct key:" << std::endl;
    result &= ASSERT_TRUE(channelList.userCanJoin(2, channel, "secret"));

    std::cout << "2) Test if user cannot join channel if already in it:" << std::endl;
    result &= ASSERT_FALSE(channelList.userCanJoin(1, channel, "secret"));

    std::cout << "3) Test if user cannot join channel with wrong key:" << std::endl;
    result &= ASSERT_FALSE(channelList.userCanJoin(2, channel, "wrongkey"));

    std::cout << "4) Test if user cannot join channel if limit is reached:" << std::endl;
    channel.setUserLimit(1);
    result &= ASSERT_FALSE(channelList.userCanJoin(2, channel, "secret"));

    return (result);
}

bool    TestChannelListUserHasInvite(void) {
    std::cout << "\033[0;34m" << "\nTesting for ChannelList addInvite method:" << "\033[0m" << std::endl;
    bool    result = true;

    try {
        MsgHandler  msgHandler;
        std::string dummyHost = "localhost";
        std::vector<struct pollfd> pollFds;
        ClientList  clientList(msgHandler, pollFds);
        ChannelList channelList(clientList, msgHandler);

        Client client1(1, msgHandler, dummyHost);
        clientList.add(1, dummyHost);

        std::string channelName = "TestChannel";
        Channel channel(channelName, msgHandler);
        channelList.add(channel);

        std::cout << "1) Test if user does not have invite to another channel:" << std::endl;
        result &= ASSERT_FALSE(channelList.userHasInvite("client1", "AnotherChannel"));

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        result = false;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
        result = false;
    }

    return (result);
}

bool TestChannelListInviteUser(void) {
    std::cout << "\033[0;34m" << "\nTesting for ChannelList inviteUser method:" << "\033[0m" << std::endl;
    bool result = true;

    try {
        MsgHandler msgHandler;
        std::string dummyHost = "localhost";
        std::vector<struct pollfd> pollFds;
        ClientList clientList(msgHandler, pollFds);
        ChannelList channelList(clientList, msgHandler);

        Client client1(1, msgHandler, dummyHost);
        Client client2(2, msgHandler, dummyHost);
        clientList.add(1, dummyHost);
        clientList.add(2, dummyHost);

        std::string channelName = "TestChannel";
        Channel channel(channelName, msgHandler);
        channelList.add(channel);
        
        channelList.join(1, channelName, "");
        channelList.join(2, channelName, "");

        std::cout << "1) Test if invitee has been invited:" << std::endl;
        result &= ASSERT_TRUE(channelList.userHasInvite("client2", channelName));

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        result = false;
    } catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
        result = false;
    }

    return (result);
}
