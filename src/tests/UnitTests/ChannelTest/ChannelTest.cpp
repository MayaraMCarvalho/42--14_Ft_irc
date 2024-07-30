/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelTest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:14:36 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/25 19:38:41 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/TestFramework.hpp"

bool    TestChannelConstructor(void) {
    std::cout << "\033[0;34m" << "\nTesting for the constructor of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if the name is correctly set:" << std::endl;
    result &= ASSERT_EQ(channel.getName(), "TestChannel");

    std::cout << "2) Test if the topic is empty by default:" << std::endl;
    result &= ASSERT_EQ(channel.getTopic().empty(), true);

    std::cout << "3) Test if the key is empty by default:" << std::endl;
    result &= ASSERT_EQ(channel.getKey().empty(), true);

    std::cout << "4) Test if the limit is set to -1 by default:" << std::endl;
    result &= ASSERT_EQ(channel.getUserLimit(), -1);

    return (result);
}

bool    TestChannelCopyConstructor(void) {
    std::cout << "\033[0;34m" << "\nTesting for the copy constructor of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     original("OriginalChannel", msgHandler);
    Channel     copy(original);

    std::cout << "1) Test if the name is copied correctly:" << std::endl;
    result &= ASSERT_EQ(copy.getName(), "OriginalChannel");

    std::cout << "2) Test if the topic is copied correctly:" << std::endl;
    result &= ASSERT_EQ(copy.getTopic(), original.getTopic());

    std::cout << "3) Test if the key is copied correctly:" << std::endl;
    result &= ASSERT_EQ(copy.getKey(), original.getKey());

    std::cout << "4) Test if the limit is copied correctly:" << std::endl;
    result &= ASSERT_EQ(copy.getUserLimit(), original.getUserLimit());

    return (result);
}

bool    TestChannelAssignmentOperator(void) {
    std::cout << "\033[0;34m" << "\nTesting for the assignment operator of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     original("OriginalChannel", msgHandler);
    Channel     assigned("AssignedChannel", msgHandler);

    assigned = original;

    std::cout << "1) Test if the name is correctly assigned:" << std::endl;
    result &= ASSERT_EQ(assigned.getName(), "OriginalChannel");

    std::cout << "2) Test if the topic is correctly assigned:" << std::endl;
    result &= ASSERT_EQ(assigned.getTopic(), original.getTopic());

    std::cout << "3) Test if the key is correctly assigned:" << std::endl;
    result &= ASSERT_EQ(assigned.getKey(), original.getKey());

    std::cout << "4) Test if the limit is correctly assigned:" << std::endl;
    result &= ASSERT_EQ(assigned.getUserLimit(), original.getUserLimit());

    return (result);
}

bool    TestChannelGetters(void) {
    std::cout << "\033[0;34m" << "\nTesting the getters of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if the getter for name returns the correct value:" << std::endl;
    result &= ASSERT_EQ(channel.getName(), "TestChannel");

    std::cout << "2) Test if the getter for topic returns the correct value:" << std::endl;
    result &= ASSERT_EQ(channel.getTopic(), "");

    std::cout << "3) Test if the getter for key returns the correct value:" << std::endl;
    result &= ASSERT_EQ(channel.getKey(), "");

    return (result);
}

bool    TestChannelGetUserLimit(void) {
    std::cout << "\033[0;34m" << "\nTesting getUserLimit of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if the default user limit is -1:" << std::endl;
    result &= ASSERT_EQ(channel.getUserLimit(), -1);

    return (result);
}

bool    TestChannelGetNumUsers(void) {
    std::cout << "\033[0;34m" << "\nTesting getNumUsers of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if the number of users is initially 0:" << std::endl;
    result &= ASSERT_EQ(channel.getNumUsers(), 0);

    return (result);
}

bool    TestChannelGetChannelMode(void) {
    std::cout << "\033[0;34m" << "\nTesting getChannelMode of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if the default channel mode NO_CMODE is not set:" << std::endl;
    result &= ASSERT_EQ(channel.getChannelMode(Channel::NO_CMODE), false);

    return (result);
}

bool    TestChannelGetChannelModeFlags(void) {
    std::cout << "\033[0;34m" << "\nTesting getChannelModeFlags of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if the default channel mode flags are NO_CMODE:" << std::endl;
    result &= ASSERT_EQ(channel.getChannelModeFlags(), Channel::NO_CMODE);

    return (result);
}

bool    TestChannelGetUserMode(void) {
    std::cout << "\033[0;34m" << "\nTesting getUserMode of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if the default user mode is not set for any user:" << std::endl;
    result &= ASSERT_EQ(channel.getUserMode(1, Channel::FOUNDER), false);

    return (result);
}

bool    TestChannelGetUserModeFlags(void) {
    std::cout << "\033[0;34m" << "\nTesting getUserModeFlags of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if getUserModeFlags returns NO_UMODE for non-existent user:" << std::endl;
    result &= ASSERT_EQ(channel.getUserModeFlags(1), Channel::NO_UMODE);

    return (result);
}

bool    TestChannelGetPrefix(void) {
    std::cout << "\033[0;34m" << "\nTesting getPrefix of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if getPrefix returns '~' for FOUNDER mode:" << std::endl;
    result &= ASSERT_EQ(channel.getPrefix(Channel::FOUNDER), '~');

    std::cout << "2) Test if getPrefix returns '&' for PROTECTED mode:" << std::endl;
    result &= ASSERT_EQ(channel.getPrefix(Channel::PROTECTED), '&');

    std::cout << "3) Test if getPrefix returns '@' for CHANOP mode:" << std::endl;
    result &= ASSERT_EQ(channel.getPrefix(Channel::CHANOP), '@');

    std::cout << "4) Test if getPrefix returns '%' for HALFOP mode:" << std::endl;
    result &= ASSERT_EQ(channel.getPrefix(Channel::HALFOP), '%');

    std::cout << "5) Test if getPrefix returns '+' for VOICE mode:" << std::endl;
    result &= ASSERT_EQ(channel.getPrefix(Channel::VOICE), '+');

    std::cout << "6) Test if getPrefix returns '\\0' for no mode:" << std::endl;
    result &= ASSERT_EQ(channel.getPrefix(Channel::NO_UMODE), '\0');

    return (result);
}

bool    TestChannelUserIsInChannel(void) {
    std::cout << "\033[0;34m" << "\nTesting userIsInChannel of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if userIsInChannel returns false for non-existent user:" << std::endl;
    result &= ASSERT_EQ(channel.userIsInChannel(1), false);

    return (result);
}

bool    TestChannelUserCanJoin(void) {
    std::cout << "\033[0;34m" << "\nTesting userCanJoin of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if userCanJoin returns true for any user:" << std::endl;
    result &= ASSERT_EQ(channel.userCanJoin(1), true);

    return (result);
}

bool    TestChannelEmpty(void) {
    std::cout << "\033[0;34m" << "\nTesting empty of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if empty returns true for an empty channel:" << std::endl;
    result &= ASSERT_EQ(channel.empty(), true);

    return (result);
}

bool    TestChannelSetTopic(void) {
    std::cout << "\033[0;34m" << "\nTesting setTopic of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if setTopic sets the topic correctly:" << std::endl;
    channel.setTopic("New Topic");
    result &= ASSERT_EQ(channel.getTopic(), "New Topic");

    return (result);
}

bool    TestChannelSetKey(void) {
    std::cout << "\033[0;34m" << "\nTesting setKey of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if setKey sets the key and updates channel mode flags correctly:" << std::endl;
    channel.setKey("NewKey");
    result &= ASSERT_EQ(channel.getKey(), "NewKey");

    std::cout << "2) Test if setKey with empty key updates channel mode flags correctly:" << std::endl;
    channel.setKey("");
    result &= ASSERT_EQ(channel.getKey(), "");

    return (result);
}

bool    TestChannelSetUserLimit(void) {
    std::cout << "\033[0;34m" << "\nTesting setUserLimit of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Test if setUserLimit sets the user limit and updates channel mode flags correctly:" << std::endl;
    channel.setUserLimit(10);
    result &= ASSERT_EQ(channel.getUserLimit(), 10);

    std::cout << "2) Test if setUserLimit with negative value updates channel mode flags correctly:" << std::endl;
    channel.setUserLimit(-1);
    result &= ASSERT_EQ(channel.getUserLimit(), -1);

    return (result);
}

bool    TestSetChannelMode(void) {
    std::cout << "\033[0;34m" << "\nTesting setChannelMode of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Setting mode with '+' prefix:" << std::endl;
    channel.setChannelMode("+a");
    result &= ASSERT_EQ(channel.getChannelModeFlags(), Channel::ANONYMOUS);

    std::cout << "2) Removing mode with '-' prefix:" << std::endl;
    channel.setChannelMode("-a");
    result &= ASSERT_EQ(channel.getChannelModeFlags(), 0);

    std::cout << "3) Setting multiple modes with '+' prefix:" << std::endl;
    channel.setChannelMode("+i");
    channel.setChannelMode("+m");
    channel.setChannelMode("+n");
    result &= ASSERT_EQ(channel.getChannelModeFlags(), Channel::INVITEONLY);
    result &= ASSERT_EQ(channel.getChannelModeFlags(), Channel::MODERATED);
    result &= ASSERT_EQ(channel.getChannelModeFlags(), Channel::NO_OUT_MSG);

    std::cout << "4) Setting and removing conflicting modes:" << std::endl;
    channel.setChannelMode("+p");
    channel.setChannelMode("-s");
    result &= ASSERT_EQ(channel.getChannelModeFlags(), Channel::PRIVATE);
    result &= ASSERT_EQ(channel.getChannelModeFlags(), 0);

    return (result);
}

bool    TestSetChannelModeFlags(void) {
    std::cout << "\033[0;34m" << "\nTesting setChannelModeFlags of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Setting mode flags directly:" << std::endl;
    channel.setChannelModeFlags(Channel::ANONYMOUS);
    result &= ASSERT_EQ(channel.getChannelModeFlags(), Channel::ANONYMOUS);

    std::cout << "2) Clearing mode flags:" << std::endl;
    channel.setChannelModeFlags(Channel::NO_CMODE);
    result &= ASSERT_EQ(channel.getChannelModeFlags(), Channel::NO_CMODE);

    return (result);
}

bool    TestSetUserMode(void) {
    std::cout << "\033[0;34m" << "\nTesting setUserMode of Channel:" << "\033[0m" << std::endl;
    bool        result = true;
    int         userFD = 1;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    channel.setUserModeFlags(userFD, Channel::NO_CMODE);
    channel.setUserMode(userFD, "+o");
    result &= ASSERT_EQ(channel.getUserModeFlags(userFD), Channel::CHANOP);

    std::cout << "1) Adding user mode:" << std::endl;
    channel.setUserMode(userFD, "+v");
    result &= ASSERT_EQ(channel.getUserModeFlags(userFD), Channel::VOICE);

    std::cout << "2) Removing user mode:" << std::endl;
    channel.setUserMode(userFD, "-o");
    result &= ASSERT_EQ(channel.getUserModeFlags(userFD), 0);

    std::cout << "3) Invalid mode string (length != 2):" << std::endl;
    channel.setUserMode(userFD, "+z");
    result &= ASSERT_EQ(channel.getUserModeFlags(userFD), Channel::VOICE);

    return (result);
}

bool    TestSetUserModeFlags(void) {
    std::cout << "\033[0;34m" << "\nTesting setUserModeFlags of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);
    int userFD = 2;
    channel.setUserModeFlags(userFD, Channel::CHANOP);

    std::cout << "1) Directly setting user mode flags:" << std::endl;
    result &= ASSERT_EQ(channel.getUserModeFlags(userFD), Channel::CHANOP);

    std::cout << "2) Clearing user mode flags:" << std::endl;
    channel.setUserModeFlags(userFD, Channel::NO_CMODE);
    result &= ASSERT_EQ(channel.getUserModeFlags(userFD), Channel::NO_CMODE);

    return (result);
}

bool    TestAddUser(void) {
    std::cout << "\033[0;34m" << "\nTesting addUser of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Adding a user to the channel:" << std::endl;
    channel.addUser(1, Channel::CHANOP);
    result &= ASSERT_EQ(channel.usersBegin()->first, 1);
    result &= ASSERT_EQ(channel.usersBegin()->second, Channel::CHANOP);

    std::cout << "2) Adding another user to the channel:" << std::endl;
    channel.addUser(2, Channel::VOICE);
    result &= ASSERT_EQ(channel.usersBegin()->first, 1);
    result &= ASSERT_EQ((++channel.usersBegin())->first, 2);
    result &= ASSERT_EQ((++channel.usersBegin())->second, Channel::VOICE);

    std::cout << "3) Attempting to add a user that cannot join (simulated failure condition):" << std::endl;
    // Ensure userCanJoin() returns false for the user to simulate this test
    // This part requires a mock or adjustment to the userCanJoin() method if needed.
    channel.addUser(3, Channel::FOUNDER);
    result &= ASSERT_EQ(channel.usersBegin()->first, 1);

    return (result);
}

bool    TestRemoveUser(void) {
    std::cout << "\033[0;34m" << "\nTesting removeUser of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    channel.addUser(1, Channel::CHANOP);
    channel.addUser(2, Channel::VOICE);

    std::cout << "1) Removing a user from the channel:" << std::endl;
    channel.removeUser(1);
    result &= ASSERT_EQ(channel.usersBegin()->first, 2);

    std::cout << "2) Removing a user that does not exist:" << std::endl;
    channel.removeUser(3);
    result &= ASSERT_EQ(channel.usersBegin()->first, 2);

    return (result);
}

bool    TestSendToAll(void) {
    std::cout << "\033[0;34m" << "\nTesting sendToAll of Channel:" << "\033[0m" << std::endl;
    bool        result = true;
    int         userFD1 = 1;
    int         userFD2 = 2;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    channel.addUser(userFD1, Channel::CHANOP);
    channel.addUser(userFD2, Channel::VOICE);

    std::cout << "1) Sending message to all users" << std::endl;
    // This requires checking if sendMessage() was called correctly
    // To do this, you need to use a mock for MsgHandler
    channel.sendToAll("Hello, World!");

    std::cout << "2) Sending message from a user to all users" << std::endl;
    channel.sendToAll("Alice", "Hello, World!");

    return (result);
}

bool    TestInviteManagement(void) {
    std::cout << "\033[0;34m" << "\nTesting invite management of Channel:" << "\033[0m" << std::endl;
    bool        result = true;

    MsgHandler  msgHandler;
    Channel     channel("TestChannel", msgHandler);

    std::cout << "1) Adding an invite" << std::endl;
    channel.addInvite("user1");
    result &= ASSERT_EQ(channel.userHasInvite("user1"), true);

    std::cout << "2) Removing an invite" << std::endl;
    channel.removeInvite("user1");
    result &= ASSERT_EQ(channel.userHasInvite("user1"), false);

    std::cout << "3) Adding and removing multiple invites" << std::endl;
    channel.addInvite("user2");
    channel.addInvite("user3");
    channel.removeInvite("user2");
    result &= ASSERT_EQ(channel.userHasInvite("user2"), false);
    result &= ASSERT_EQ(channel.userHasInvite("user3"), true);

    return (result);
}


