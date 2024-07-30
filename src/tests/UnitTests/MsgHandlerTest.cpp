/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsgHandlerTest.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:36:23 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/26 02:24:39 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/TestFramework.hpp"

bool TestDefaultConstructorMsgHandler(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the default constructor of MsgHandler:"
              << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;

    std::cout << "1) Test if the default host is 'defaulthost':" << std::endl;
    result &= ASSERT_EQ(handler.getHost(), "defaulthost");

    return (result);
}

bool TestParameterizedConstructorMsgHandler(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the parameterized constructor of MsgHandler with host:"
              << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler("testhost");

    std::cout << "1) Test if the host is set to 'testhost':" << std::endl;
    result &= ASSERT_EQ(handler.getHost(), "testhost");

    return (result);
}

bool TestCopyConstructorMsgHandler(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the copy constructor of MsgHandler:"
              << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler original("originalhost");
    MsgHandler copy(original);

    std::cout << "1) Test if the host of the copy is 'originalhost':" << std::endl;
    result &= ASSERT_EQ(copy.getHost(), "originalhost");

    return (result);
}

bool TestAssignmentOperatorMsgHandler(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the assignment operator of MsgHandler:"
              << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler original("originalhost");
    MsgHandler assigned;
    assigned = original;

    std::cout << "1) Test if the host of the assigned object is 'originalhost':" << std::endl;
    result &= ASSERT_EQ(assigned.getHost(), "originalhost");

    return (result);
}

bool TestSendMessage(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the sendMessage method of MsgHandler:"
              << "\033[0m" << std::endl;
    std::string msg = "Hello, World!";
    bool result = true;
    int fd = 1;

    MsgHandler handler("testhost");

    handler.sendMessage(fd, msg);

    std::cout << "1) Test if the message is correctly sent to the queue:" << std::endl;
    handler.sendPush(fd, ":testhost Hello, World!\r\n");
    std::string expectedMsg = ":testhost Hello, World!\r\n";
    result &= ASSERT_EQ(handler.sendPop(fd), expectedMsg);

    return (result);
}

bool TestSendMessageWithFrom(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the sendMessage method of MsgHandler with 'from' parameter:"
              << "\033[0m" << std::endl;
    bool result = true;
    int fd = 1;

    MsgHandler handler;
    std::string from = "sender";
    std::string msg = "Hello, World!";

    handler.sendMessage(fd, from, msg);

    std::cout << "1) Test if the message is correctly sent to the queue with the 'from' parameter:" << std::endl;
    handler.sendPush(fd, ":sender Hello, World!\r\n");
    std::string expectedMsg = ":sender Hello, World!\r\n";
    result &= ASSERT_EQ(handler.sendPop(fd), expectedMsg);
    return (result);
}

bool TestSendPop(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the sendPop method of MsgHandler:"
              << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    int fd = 1;
    std::string msg = "Test message";

    handler.sendPush(fd, msg);

    std::cout << "1) Test if sendPop returns the correct message:" << std::endl;
    result &= ASSERT_EQ(handler.sendPop(fd), msg);

    std::cout << "2) Test if sendPop throws an exception for an empty queue:" << std::endl;
    try
    {
        handler.sendPop(2);
        result &= false;
    }
    catch (const std::out_of_range &)
    {
        result &= true;
    }

    return (result);
}

bool TestSendPush(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the sendPush method of MsgHandler:"
              << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    int fd = 1;
    std::string msg = "Test message";

    std::cout << "1) Test if sendPush inserts the message correctly:" << std::endl;
    result &= ASSERT_EQ(handler.sendPush(fd, msg), true);
    result &= ASSERT_EQ(handler.sendPop(fd), msg);

    std::cout << "2) Test if sendPush returns false for message exceeding max length:" << std::endl;
    std::string longMsg(handler.MAX_SEND_QUEUE_LENGTH + 1, 'a');
    result &= ASSERT_EQ(handler.sendPush(fd, longMsg), false);

    return (result);
}

bool TestRemoveSendChars(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the removeSendChars method of MsgHandler:"
              << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    int fd = 1;
    std::string msg = "Test message";

    handler.sendPush(fd, msg);

    std::cout << "1) Test if removeSendChars correctly removes characters from the message:" << std::endl;
    handler.removeSendChars(fd, 5);
    result &= ASSERT_EQ(handler.sendPop(fd), "message");

    return (result);
}

bool TestSendLength(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the sendLength method of MsgHandler:"
              << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    int fd = 1;
    std::string msg = "Test message";

    handler.sendPush(fd, msg);

    std::cout << "1) Test if sendLength returns the correct length of the message:" << std::endl;
    result &= ASSERT_EQ(handler.sendLength(fd), static_cast<ssize_t>(msg.length()));

    std::cout << "2) Test if sendLength returns 0 for a non-existing queue:" << std::endl;
    result &= ASSERT_EQ(handler.sendLength(2), 0);

    return (result);
}

bool TestRecvPush(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the recvPush method of MsgHandler:"
              << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    int fd = 1;
    std::string msg = "Test message";

    std::cout << "1) Test if recvPush inserts the message correctly:" << std::endl;
    result &= ASSERT_EQ(handler.recvPush(fd, msg), true);
    result &= ASSERT_EQ(handler.recvPop(fd), msg);

    std::cout << "2) Test if recvPush returns false for message exceeding max length:" << std::endl;
    std::string longMsg(handler.MAX_RECV_QUEUE_LENGTH + 1, 'a');
    result &= ASSERT_EQ(handler.recvPush(fd, longMsg), false);

    return (result);
}

bool TestRecvPop(void)
{
    std::cout << "\033[0;34m"
              << "\nTesting for the recvPop method of MsgHandler:"
              << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    int fd = 1;
    std::string msg = "Test message";

    handler.recvPush(fd, msg);

    std::cout << "1) Test if recvPop returns the correct message:" << std::endl;
    result &= ASSERT_EQ(handler.recvPop(fd), msg);

    std::cout << "2) Test if recvPop throws an exception for an empty queue:" << std::endl;
    try
    {
        handler.recvPop(2);
        result &= false;
    }
    catch (const std::out_of_range &)
    {
        result &= true;
    }

    return (result);
}

bool    TestRecvLength(void) {
    std::cout << "\033[0;34m" << "\nTesting for the recvLength method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    int fd = 1;
    std::string msg = "Test message";

    handler.recvPush(fd, msg);

    std::cout << "1) Test if recvLength returns the correct length of the message:" << std::endl;
    result &= ASSERT_EQ(handler.recvLength(fd), static_cast<ssize_t>(msg.length()));

    std::cout << "2) Test if recvLength returns 0 for a non-existing queue:" << std::endl;
    result &= ASSERT_EQ(handler.recvLength(2), 0);

    return (result);
}

bool    TestResetQueues(void) {
    std::cout << "\033[0;34m" << "\nTesting for the resetQueues method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    int fd = 1;
    std::string msg = "Test message";

    handler.sendPush(fd, msg);
    handler.recvPush(fd, msg);
    handler.resetQueues(fd);

    std::cout << "1) Test if resetQueues removes the send queue:" << std::endl;
    result &= ASSERT_EQ(handler.sendLength(fd), 0);

    std::cout << "2) Test if resetQueues removes the recv queue:" << std::endl;
    result &= ASSERT_EQ(handler.recvLength(fd), 0);

    return (result);
}

bool    TestErrNeedMoreParams(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errNeedMoreParams method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string command = "command";
    std::string expected = "461 client command :Not enough parameters";

    std::cout << "1) Test if errNeedMoreParams returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errNeedMoreParams(client, command), expected);

    return (result);
}

bool    TestErrAlreadyRegistered(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errAlreadyRegistered method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "462 client :You may not reregister";

    std::cout << "1) Test if errAlreadyRegistered returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errAlreadyRegistered(client), expected);

    return (result);
}

bool    TestErrPasswordMismatch(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errPasswordMismatch method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "464 client :Password incorrect";

    std::cout << "1) Test if errPasswordMismatch returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errPasswordMismatch(client), expected);

    return (result);
}

bool    TestErrErroneusNickname(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errErroneusNickname method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "432 client :Erroneus nickname";

    std::cout << "1) Test if errErroneusNickname returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errErroneusNickname(client), expected);

    return (result);
}

bool    TestErrNoNickNameGiven(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errNoNickNameGiven method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "431 client :No nickname given";

    std::cout << "1) Test if errNoNickNameGiven returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errNoNickNameGiven(client), expected);

    return (result);
}

bool    TestErrNicknameInUse(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errNicknameInUse method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "433 client :Nickname is already in use";

    std::cout << "1) Test if errNicknameInUse returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errNicknameInUse(client), expected);

    return (result);
}

bool    TestErrNoOrigin(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errNoOrigin method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "409 client :No origin specified";

    std::cout << "1) Test if errNoOrigin returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errNoOrigin(client), expected);

    return (result);
}

bool    TestErrNoSuchChannel(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errNoSuchChannel method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string expected = "403 client channel :No such channel";

    std::cout << "1) Test if errNoSuchChannel returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errNoSuchChannel(client, channel), expected);

    return (result);
}

bool    TestErrNoSuchNick(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errNoSuchNick method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string nick = "nick";
    std::string expected = "401 client nick :No such nick";

    std::cout << "1) Test if errNoSuchNick returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errNoSuchNick(client, nick), expected);

    return (result);
}

bool    TestErrTooManyChannels(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errTooManyChannels method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string expected = "405 client channel :You have joined too many channels";

    std::cout << "1) Test if errTooManyChannels returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errTooManyChannels(client, channel), expected);

    return (result);
}

bool    TestErrBadChannelKey(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errBadChannelKey method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string expected = "475 client channel :Cannot join channel (+k)";

    std::cout << "1) Test if errBadChannelKey returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errBadChannelKey(client, channel), expected);

    return (result);
}

bool    TestErrBannedFromChan(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errBannedFromChan method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string expected = "474 client channel :Cannot join channel (+b)";

    std::cout << "1) Test if errBannedFromChan returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errBannedFromChan(client, channel), expected);

    return (result);
}

bool    TestErrChannelIsFull(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errChannelIsFull method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string expected = "471 client channel :Cannot join channel (+l)";

    std::cout << "1) Test if errChannelIsFull returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errChannelIsFull(client, channel), expected);

    return (result);
}

bool    TestErrInputTooLong(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errInputTooLong method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "417 client :Input line was too long";

    std::cout << "1) Test if errInputTooLong returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errInputTooLong(client), expected);

    return (result);
}

bool    TestErrInviteOnlyChan(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errInviteOnlyChan method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string expected = "473 client channel :Cannot join channel (+i)";

    std::cout << "1) Test if errInviteOnlyChan returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errInviteOnlyChan(client, channel), expected);

    return (result);
}

bool    TestErrBadChanMask(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errBadChanMask method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string channel  = "channel";
    std::string expected = "476 channel :Bad Channel Mask";

    std::cout << "1) Test if errBadChanMask returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errBadChanMask(channel), expected);

    return (result);
}

bool    TestErrCannotSendToChan(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errCannotSendToChan method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string expected = "404 client channel :Cannot send to channel";

    std::cout << "1) Test if errCannotSendToChan returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errCannotSendToChan(client, channel), expected);

    return (result);
}

bool    TestErrNoRecipient(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errNoRecipient method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string command = "command";
    std::string expected = "411 client :No recipient given (command)";

    std::cout << "1) Test if errNoRecipient returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errNoRecipient(client, command), expected);

    return (result);
}

bool    TestErrNoTextToSend(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errNoTextToSend method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "412 client :No text to send";

    std::cout << "1) Test if errNoTextToSend returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errNoTextToSend(client), expected);

    return (result);
}

bool    TestErrNotOnChannel(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errNotOnChannel method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string expected = "442 client channel :You're not on that channel";

    std::cout << "1) Test if errNotOnChannel returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errNotOnChannel(client, channel), expected);

    return (result);
}

bool    TestErrNotRegistered(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errNotRegistered method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "451 client :You have not registered";

    std::cout << "1) Test if errNotRegistered returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errNotRegistered(client), expected);

    return (result);
}

bool    TestErrChanOPrivIsNeeded(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errChanOPrivIsNeeded method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string expected = "482 client channel :You're not channel operator";

    std::cout << "1) Test if errChanOPrivIsNeeded returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errChanOPrivIsNeeded(client, channel), expected);

    return (result);
}

bool    TestErrInvalidModeParam(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errInvalidModeParam method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string target = "target";
    char mode = 'm';
    std::string param = "param";
    std::string description = "description";
    std::string expected = "696 client target m param :description";

    std::cout << "1) Test if errInvalidModeParam returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errInvalidModeParam(client, target, mode, param, description), expected);

    return (result);
}

bool    TestErrUModeUnknownFlag(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errUModeUnknownFlag method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "501 client :Unknown MODE flag";

    std::cout << "1) Test if errUModeUnknownFlag returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errUModeUnknownFlag(client), expected);

    return (result);
}

bool    TestErrUnknownCommand(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errUnknownCommand method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string command = "command";
    std::string info = "info";
    std::string expected = "421 client command :info";

    std::cout << "1) Test if errUnknownCommand returns the correct error message (single subcommand):" << std::endl;
    result &= ASSERT_EQ(handler.errUnknownCommand(client, command, info), expected);

    std::string subcommand = "subcommand";
    expected = "421 client command subcommand :info";

    std::cout << "2) Test if errUnknownCommand returns the correct error message (with subcommand):" << std::endl;
    result &= ASSERT_EQ(handler.errUnknownCommand(client, command, subcommand, info), expected);

    return (result);
}

bool    TestErrUnknownMode(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errUnknownMode method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    char mode = 'm';
    std::string expected = "472 client m :is unknown mode char to me";

    std::cout << "1) Test if errUnknownMode returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errUnknownMode(client, mode), expected);

    return (result);
}

bool    TestErrUserOnChannel(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errUserOnChannel method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string nick = "nick";
    std::string expected = "443 client nick channel :is already on channel";

    std::cout << "1) Test if errUserOnChannel returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errUserOnChannel(client, channel, nick), expected);

    return (result);
}

bool    TestErrUserNotInChannel(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errUserNotInChannel method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "channel";
    std::string nick = "nick";
    std::string expected = "441 client nick channel :They aren't on that channel";

    std::cout << "1) Test if errUserNotInChannel returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errUserNotInChannel(client, channel, nick), expected);

    return (result);
}

bool    TestErrUsersDontMatch(void) {
    std::cout << "\033[0;34m" << "\nTesting for the errUsersDontMatch method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "502 client :Cant change mode for other users";

    std::cout << "1) Test if errUsersDontMatch returns the correct error message:" << std::endl;
    result &= ASSERT_EQ(handler.errUsersDontMatch(client), expected);

    return (result);
}

bool    TestRplWelcome(void) {
    std::cout << "\033[0;34m" << "\nTesting for the rplWelcome method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    handler.setHost("localhost");
    std::string expected = "001 client :Welcome to localhost IRC server!";

    std::cout << "1) Test if rplWelcome returns the correct welcome message:" << std::endl;
    result &= ASSERT_EQ(handler.rplWelcome(client), expected);

    return (result);
}

bool    TestRplEndOfNames(void) {
    std::cout << "\033[0;34m" << "\nTesting for the rplEndOfNames method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "#channel";
    std::string expected = "366 client #channel :End of /NAMES list";

    std::cout << "1) Test if rplEndOfNames returns the correct end of names message:" << std::endl;
    result &= ASSERT_EQ(handler.rplEndOfNames(client, channel), expected);

    return (result);
}

bool    TestRplNamReply(void) {
    std::cout << "\033[0;34m" << "\nTesting for the rplNamReply method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "#channel";
    std::string clientList = "user1 user2";
    char symbol = '=';
    std::string expected = "353 client = #channel user1 user2";

    std::cout << "1) Test if rplNamReply returns the correct name reply message:" << std::endl;
    result &= ASSERT_EQ(handler.rplNamReply(client, channel, clientList, symbol), expected);

    return (result);
}

bool    TestRplTopic(void) {
    std::cout << "\033[0;34m" << "\nTesting for the rplTopic method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "#channel";
    std::string topic = "This is a topic";
    std::string expected = "332 client #channel :This is a topic";

    std::cout << "1) Test if rplTopic returns the correct topic message:" << std::endl;
    result &= ASSERT_EQ(handler.rplTopic(client, channel, topic), expected);

    return (result);
}

bool    TestRplNoTopic(void) {
    std::cout << "\033[0;34m" << "\nTesting for the rplNoTopic method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "#channel";
    std::string expected = "331 client #channel :No topic is set";

    std::cout << "1) Test if rplNoTopic returns the correct no topic message:" << std::endl;
    result &= ASSERT_EQ(handler.rplNoTopic(client, channel), expected);

    return (result);
}

bool    TestRplList(void) {
    std::cout << "\033[0;34m" << "\nTesting for the rplList method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "#channel";
    std::string topic = "This is a topic";
    int numUsers = 5;
    std::string expected = "322 client #channel 5 :This is a topic";

    std::cout << "1) Test if rplList returns the correct list message with topic:" << std::endl;
    result &= ASSERT_EQ(handler.rplList(client, channel, topic, numUsers), expected);

    topic = "";
    expected = "322 client #channel 5";

    std::cout << "2) Test if rplList returns the correct list message without topic:" << std::endl;
    result &= ASSERT_EQ(handler.rplList(client, channel, topic, numUsers), expected);

    return (result);
}

bool    TestRplListEnd(void) {
    std::cout << "\033[0;34m" << "\nTesting for the rplListEnd method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string expected = "323 client :End of /LIST";

    std::cout << "1) Test if rplListEnd returns the correct list end message:" << std::endl;
    result &= ASSERT_EQ(handler.rplListEnd(client), expected);

    return (result);
}

bool    TestRplInviting(void) {
    std::cout << "\033[0;34m" << "\nTesting for the rplInviting method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    std::string channel = "#channel";
    std::string nick = "nick";
    std::string expected = "341 client nick #channel";

    std::cout << "1) Test if rplInviting returns the correct inviting message:" << std::endl;
    result &= ASSERT_EQ(handler.rplInviting(client, channel, nick), expected);

    return (result);
}

bool    TestRplUModeIs(void) {
    std::cout << "\033[0;34m" << "\nTesting for the rplUModeIs method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    int userModes = Client::INVISIBLE | Client::OPERATOR;
    std::string expected = "221 client +io";

    std::cout << "1) Test if rplUModeIs returns the correct user mode message:" << std::endl;
    result &= ASSERT_EQ(handler.rplUModeIs(client, userModes), expected);

    return (result);
}

bool    TestRplChannelModeIs(void) {
    std::cout << "\033[0;34m" << "\nTesting for the rplChannelModeIs method of MsgHandler:" << "\033[0m" << std::endl;
    bool result = true;

    MsgHandler handler;
    std::string client = "client";
    int chanModes = Channel::ANONYMOUS | Channel::INVITEONLY;
    std::string expected = "324 client +ai";

    std::cout << "1) Test if rplChannelModeIs returns the correct channel mode message:" << std::endl;
    result &= ASSERT_EQ(handler.rplChannelModeIs(client, chanModes), expected);

    return (result);
}
