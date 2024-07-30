/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:43:29 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/26 17:20:19 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/TestFramework.hpp"
#include "./include/Helpers.hpp"

// Channel
bool    TestChannelConstructor(void);
bool    TestChannelCopyConstructor(void);
bool    TestChannelAssignmentOperator(void);
bool    TestChannelGetters(void);
bool    TestChannelGetUserLimit(void);
bool    TestChannelGetNumUsers(void);
bool    TestChannelGetChannelMode(void);
bool    TestChannelGetChannelModeFlags(void);
bool    TestChannelGetUserMode(void);
bool    TestChannelGetUserModeFlags(void);
bool    TestChannelGetPrefix(void);
bool    TestChannelUserIsInChannel(void);
bool    TestChannelUserCanJoin(void);
bool    TestChannelEmpty(void);
bool    TestChannelSetTopic(void);
bool    TestChannelSetKey(void);
bool    TestChannelSetUserLimit(void);
bool    TestSetChannelMode(void);
bool    TestSetChannelModeFlags(void);
bool    TestSetUserMode(void);
bool    TestSetUserModeFlags(void);
bool    TestAddUser(void);
bool    TestRemoveUser(void);
bool    TestSendToAll(void);
bool    TestInviteManagement(void);

// ChannelList
//bool TestChannelListConstructor(void);
bool    TestChannelListCopyConstructor(void);
bool    TestChannelListAssignmentOperator(void);
bool    TestChannelListAdd(void);
//bool    TestChannelListRemove(void);
bool    TestChannelListJoin(void);
bool    TestChannelListPart(void);
bool    TestChannelListPartDisconnectedClient(void);
bool    TestChannelListUserCanJoin(void);
bool    TestChannelListUserHasInvite(void);
bool    TestChannelListInviteUser(void);

// Helpers
bool    runTest(bool (*testFunc)(void));

// Client
bool    TestClientDefaultConstructor(void);
bool    TestClientParameterizedConstructor(void);
bool    TestClientCopyConstructor(void);
bool    TestClientAssignmentOperator(void);
//bool    TestClientGetAndSetNick(void);
bool    TestClientGetAndSetUser(void);
bool    TestClientGetAndSetHost(void);
bool    TestClientGetFullId(void);
bool    TestClientGetAndSetFD(void);
bool    TestClientGetChannelList(void);
bool    TestClientGetAndSetStatus(void);
bool    TestClientGetModeFlags(void);
bool    TestClientGetMode(void);
bool    TestClientSetModeFlags(void);
bool    TestClientSetMode(void);
bool    TestClientIsInChannel(void);
bool    TestClientAddChannel(void);
bool    TestClientRemoveChannel(void);
void    mockSendMessage(int fd, const std::string &msg);
bool    TestClientSendMessage(void);

// ClientList
bool    TestDefaultConstructorClientList(void);
bool    TestGetClientByNick(void);
bool    TestGetClientByUser(void);
bool    TestGetNick(void);
bool    TestGetUser(void);
bool    TestGetFDByNick(void);
bool    TestGetFDByUser(void);
bool    TestEnd(void);
bool    TestSetNick(void);
bool    TestSetUser(void);
bool    TestAddClient(void);
bool    TestAddClientWithAddress(void);
bool    TestAddMultipleClients(void);
bool    TestAddClientWithSameFd(void);
bool    TestAddClientWithHostname(void);
bool    TestRemoveClientByNick(void);
bool    TestRemoveClientByUser(void);
bool    TestIsValidNick(void);
bool    TestIsValidUser(void);
bool    TestIsSpecialChar(void);

bool    TestAddAndGetClient(void);
bool    TestRemoveClient(void);

// Command
bool    TestCommandJoin(void);
//bool    TestIsCommand(void);
//bool    testCommandPart(void);

//IrcServer
bool    TestDefaultConstructor(void);
bool    TestParameterizedConstructor(void);
bool    TestGetPort(void);
bool    TestGetPassword(void);
bool    TestGetServerFd(void);
bool    TestGetPollFds(void);
// bool    TestGetFileTransfer(void);
// bool    TestGetBot(void);
bool    TestGetClients(void);
//bool    TestGetChannels(void);
bool    TestSetPassword(void);
bool    TestSetServerFd(void);
bool    TestSetPollFds(void);
bool    TestSetBot(void);
//bool    TestSetChannels(void);
bool    TestSetupServerSuccess(void);
//bool    TestSetupServerSocketFailure(void);

bool TestHandleClientMessageEmpty(void);
bool TestSetupSignalHandlers();
//bool TestAuthenticate_ValidUser();
//bool TestAuthenticate_InvalidPassword();
//bool TestAuthenticate_UserNotFound();

// MsgHandler
bool    TestDefaultConstructorMsgHandler(void);
bool    TestParameterizedConstructorMsgHandler(void);
bool    TestCopyConstructorMsgHandler(void);
bool    TestAssignmentOperatorMsgHandler(void);
bool    TestSendMessage(void);
bool    TestSendMessageWithFrom(void);
bool    TestSendPop(void);
bool    TestSendPush(void);
bool    TestRemoveSendChars(void);
bool    TestSendLength(void);
bool    TestRecvPush(void);
bool    TestRecvPop(void);
bool    TestRecvLength(void);
bool    TestResetQueues(void);
bool    TestErrNeedMoreParams(void);
bool    TestErrAlreadyRegistered(void);
bool    TestErrPasswordMismatch(void);
bool    TestErrErroneusNickname(void);
bool    TestErrNoNickNameGiven(void);
bool    TestErrNicknameInUse(void);
bool    TestErrNoOrigin(void);
bool    TestErrNoSuchChannel(void);
bool    TestErrNoSuchNick(void);
bool    TestErrTooManyChannels(void);
bool    TestErrBadChannelKey(void);
bool    TestErrBannedFromChan(void);
bool    TestErrChannelIsFull(void);
bool    TestErrInputTooLong(void);
bool    TestErrInviteOnlyChan(void);
bool    TestErrBadChanMask(void);
bool    TestErrCannotSendToChan(void);
bool    TestErrNoRecipient(void);
bool    TestErrNoTextToSend(void);
bool    TestErrNotOnChannel(void);
bool    TestErrNotRegistered(void);
bool    TestErrChanOPrivIsNeeded(void);
bool    TestErrInvalidModeParam(void);
bool    TestErrUModeUnknownFlag(void);
bool    TestErrUnknownCommand(void);
bool    TestErrUnknownMode(void);
bool    TestErrUserOnChannel(void);
bool    TestErrUserNotInChannel(void);
bool    TestErrUsersDontMatch(void);
bool    TestRplWelcome(void);
bool    TestRplEndOfNames(void);
bool    TestRplNamReply(void);
bool    TestRplTopic(void);
bool    TestRplNoTopic(void);
bool    TestRplList(void);
bool    TestRplListEnd(void);
bool    TestRplInviting(void);
bool    TestRplUModeIs(void);
bool    TestRplChannelModeIs(void);

// Bot
bool    TestBotConstructors(void);
bool    TestBotGettersSetters(void);
bool    TestBotRespondToMessage(void);

// FileTransfer
bool    TestRequestTransfer(void);
bool    TestHandleTransfer(void);
bool    TestSendFileChunk(void);
bool    TestReadFile(void);


int main(void) {
    int passedTests = 0;
    int failedTests = 0;

    int passedTestsChannel = 0;
    int failedTestsChannel = 0;

    std::cout << "\033[1;35m" << "\n ### Testing Channel ###" << "\033[0m" << std::endl;
    if (runTest(TestChannelConstructor)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelCopyConstructor)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelAssignmentOperator)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelGetters)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelGetUserLimit)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelGetNumUsers)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelGetChannelMode)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelGetChannelModeFlags)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelGetUserMode)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelGetUserModeFlags)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelGetPrefix)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelUserIsInChannel)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelUserCanJoin)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelEmpty)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelSetTopic)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelSetKey)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestChannelSetUserLimit)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestSetChannelMode)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestSetChannelModeFlags)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestSetUserMode)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestSetUserModeFlags)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestAddUser)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestRemoveUser)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestSendToAll)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }
    if (runTest(TestInviteManagement)) { passedTests++; passedTestsChannel++; } else { failedTests++; failedTestsChannel++; }

    int passedTestsChannelList = 0;
    int failedTestsChannelList = 0;
    std::cout << "\033[1;35m" << "\n ### Testing ChannelList ###" << "\033[0m" << std::endl;
    //if (runTest(TestChannelListConstructor)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }
    if (runTest(TestChannelListCopyConstructor)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }
    if (runTest(TestChannelListAssignmentOperator)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }
    if (runTest(TestChannelListAdd)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }
    //if (runTest(TestChannelListRemove)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }
    if (runTest(TestChannelListJoin)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }
    if (runTest(TestChannelListPart)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }
    if (runTest(TestChannelListPartDisconnectedClient)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }
    if (runTest(TestChannelListUserCanJoin)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }
    if (runTest(TestChannelListUserHasInvite)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }
    if (runTest(TestChannelListInviteUser)) { passedTests++; passedTestsChannelList++; } else { failedTests++; failedTestsChannelList++; }

    int clientTestPassed = 0;
    int clientTestFailed = 0;

    std::cout << "\033[1;35m" << "\n ### Testing Client ###" << "\033[0m" << std::endl;
    if (runTest(TestClientDefaultConstructor)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientParameterizedConstructor)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientCopyConstructor)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientAssignmentOperator)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    // if (runTest(TestClientGetAndSetNick)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientGetAndSetUser)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientGetAndSetHost)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientGetFullId)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientGetAndSetFD)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientGetChannelList)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientGetAndSetStatus)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientGetMode)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientGetModeFlags)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientSetModeFlags)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientSetMode)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientIsInChannel)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientAddChannel)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientRemoveChannel)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }
    if (runTest(TestClientSendMessage)) { passedTests++; clientTestPassed++; } else { failedTests++; clientTestFailed++; }

    int clientListTestPassed = 0;
    int clientListTestFailed = 0;
    
    std::cout << "\033[1;35m" << "\n ### Testing ClientList ###" << "\033[0m" << std::endl;
    if (runTest(TestDefaultConstructorClientList)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestGetClientByNick)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestGetClientByUser)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestGetNick)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestGetUser)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestGetFDByNick)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestGetFDByUser)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestEnd)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestSetNick)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestSetUser)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestAddClient)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestAddClientWithAddress)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestAddMultipleClients)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestAddClientWithSameFd)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestAddClientWithHostname)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestRemoveClient)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }  
    if (runTest(TestRemoveClientByNick)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestRemoveClientByUser)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestIsValidNick)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestIsValidUser)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    if (runTest(TestIsSpecialChar)) { passedTests++; clientListTestPassed++; } else { failedTests++; clientListTestFailed++; }
    

    int commandTestPassed = 0;
    int commandTestFailed = 0;
    
    std::cout << "\033[1;35m" << "\n ### Testing Command ###" << "\033[0m" << std::endl;
    if (runTest(TestCommandJoin)) { passedTests++; commandTestPassed++; } else { failedTests++; commandTestFailed++; }


    int ircServerTestsPassed = 0;
    int ircServerTestsFailed = 0;

    std::cout << "\033[1;35m" << "\n ### Testing IrcServer ###" << "\033[0m" << std::endl;
    //if (runTest(TestDefaultConstructor)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestParameterizedConstructor)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestGetPort)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestGetPassword)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestGetServerFd)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestGetPollFds)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestGetClients)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestSetPassword)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestSetServerFd)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestSetPollFds)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestSetupServerSuccess)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestHandleClientMessageEmpty)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }
    if (runTest(TestSetupSignalHandlers)) { passedTests++; ircServerTestsPassed++; } else { failedTests++; ircServerTestsFailed++; }

    int msgHandlerTestPassed = 0;
    int msgHandlerTestFailed = 0;

    std::cout << "\033[1;35m" << "\n ### Testing MsgHandler ###" << "\033[0m" << std::endl;
    if (runTest(TestDefaultConstructorMsgHandler)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestParameterizedConstructorMsgHandler)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestCopyConstructorMsgHandler)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestAssignmentOperatorMsgHandler)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestSendMessage)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestSendMessageWithFrom)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestSendPop)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestSendPush)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRemoveSendChars)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestSendLength)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRecvPush)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRecvPop)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRecvLength)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestResetQueues)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrNeedMoreParams)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrAlreadyRegistered)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrPasswordMismatch)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrErroneusNickname)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrNoNickNameGiven)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrNicknameInUse)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrNoOrigin)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrNoSuchChannel)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrNoSuchNick)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrTooManyChannels)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrBadChannelKey)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrBannedFromChan)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrChannelIsFull)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrInputTooLong)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrInviteOnlyChan)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrBadChanMask)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrCannotSendToChan)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrNoRecipient)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrNoTextToSend)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrNotOnChannel)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrNotRegistered)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrChanOPrivIsNeeded)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrInvalidModeParam)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrUModeUnknownFlag)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrUnknownCommand)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrUnknownMode)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrUserOnChannel)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrUserNotInChannel)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestErrUsersDontMatch)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRplWelcome)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRplEndOfNames)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRplNamReply)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRplTopic)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRplNoTopic)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRplList)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRplListEnd)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRplInviting)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRplUModeIs)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }
    if (runTest(TestRplChannelModeIs)) { passedTests++; msgHandlerTestPassed++; } else { failedTests++; msgHandlerTestFailed++; }

    int botTestPassed = 0;
    int botTestFailed = 0;

    std::cout << "\033[1;35m" << "\n ### Testing Bot ###" << "\033[0m" << std::endl;
    if (runTest(TestBotConstructors)) { passedTests++; botTestPassed++; } else { failedTests++; botTestFailed++; }
    if (runTest(TestBotGettersSetters)) { passedTests++; botTestPassed++; } else { failedTests++; botTestFailed++; }
    if (runTest(TestBotRespondToMessage)) { passedTests++; botTestPassed++; } else { failedTests++; botTestFailed++; }

    int fileTransferTestPassed = 0;
    int fileTransferTestFailed = 0;

    std::cout << "\033[1;35m" << "\n ### Testing FileTransfer ###" << "\033[0m" << std::endl;
    if (runTest(TestRequestTransfer)) { passedTests++; fileTransferTestPassed++; } else { failedTests++; fileTransferTestFailed++; }
    if (runTest(TestHandleTransfer)) { passedTests++; fileTransferTestPassed++; } else { failedTests++; fileTransferTestFailed++; }
    if (runTest(TestSendFileChunk)) { passedTests++; fileTransferTestPassed++; } else { failedTests++; fileTransferTestFailed++; }
    if (runTest(TestReadFile)) { passedTests++; fileTransferTestPassed++; } else { failedTests++; fileTransferTestFailed++; }




    int totalTests = passedTests + failedTests;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|      Class      |"  <<   "\033[1;32m Qtd. Passed " << "\033[1;34m|" << "\033[1;31m Qtd. Failed \033[1;34m|"  <<   "\033[1;32m Percent. Passed " << "\033[1;34m|" << "\033[1;31m Percent. Failed \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|   Chanel Test   |"  <<   "\033[1;32m     " << passedTestsChannel << "      \033[1;34m|      " << "\033[1;31m" << failedTestsChannel << "      \033[1;34m|      \033[1;32m" << calculatePassPercentage(totalTests, passedTestsChannel) << "%     \033[1;34m| \033[1;31m      " << calculatePassPercentage(totalTests, failedTestsChannel) << "%     \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m| ChanelList Test |"  <<   "\033[1;32m     " << passedTestsChannelList << "       \033[1;34m|      " << "\033[1;31m" << failedTestsChannelList << "      \033[1;34m|       \033[1;32m" <<  calculatePassPercentage(totalTests, passedTestsChannelList) << "%     \033[1;34m| \033[1;31m      " << calculatePassPercentage(totalTests, failedTestsChannelList) << "%     \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|   Client Test   |"  <<   "\033[1;32m     " << clientTestPassed << "      \033[1;34m|      \033[1;31m" << clientTestFailed << "      \033[1;34m|       \033[1;32m" <<    calculatePassPercentage(totalTests, clientTestPassed) << "%     \033[1;34m| \033[1;31m      " << calculatePassPercentage(totalTests, clientTestFailed) << "%     \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m| ClientList Test |"  <<   "\033[1;32m     " << clientListTestPassed << "      \033[1;34m|      \033[1;31m" << clientTestFailed << "      \033[1;34m|      \033[1;32m" << calculatePassPercentage(totalTests, clientListTestPassed) << "%     \033[1;34m| \033[1;31m      " << calculatePassPercentage(totalTests, clientListTestFailed) << "%     \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|    Commands     |"  <<   "\033[1;32m     " << commandTestPassed << "       \033[1;34m|" << "\033[1;31m      " << commandTestFailed << "      \033[1;34m|" <<   "\033[1;32m       " << calculatePassPercentage(totalTests, commandTestPassed) << "%     \033[1;34m|" << "\033[1;31m       " << calculatePassPercentage(totalTests, commandTestFailed) << "%     \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|    IrcServer    |"  <<   "\033[1;32m     " << ircServerTestsPassed << "       \033[1;34m|" << "\033[1;31m      " << ircServerTestsFailed << "      \033[1;34m|" <<   "\033[1;32m       " << calculatePassPercentage(totalTests, ircServerTestsPassed) << "%     \033[1;34m|" << "\033[1;31m       " << calculatePassPercentage(totalTests, ircServerTestsFailed) << "%     \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|    MsgHandler   |"  <<   "\033[1;32m     " << msgHandlerTestPassed << "      \033[1;34m|" << "\033[1;31m      " << msgHandlerTestFailed << "      \033[1;34m|" <<   "\033[1;32m       " << calculatePassPercentage(totalTests, msgHandlerTestPassed) << "%    \033[1;34m|" << "\033[1;31m       " << calculatePassPercentage(totalTests, msgHandlerTestFailed) << "%     \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|       Bot       |"  <<   "\033[1;32m     " << botTestPassed << "       \033[1;34m|" << "\033[1;31m      " << botTestFailed << "      \033[1;34m|" << "\033[1;32m       " << calculatePassPercentage(totalTests, botTestPassed) << "%     \033[1;34m|" << "\033[1;31m       " << calculatePassPercentage(totalTests, botTestFailed) << "%     \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|   FileTransfer  |"  <<   "\033[1;32m     " << fileTransferTestPassed << "       \033[1;34m|" << "\033[1;31m      " << fileTransferTestFailed << "      \033[1;34m|" << "\033[1;32m       " << calculatePassPercentage(totalTests, fileTransferTestPassed) << "%     \033[1;34m|" << "\033[1;31m       " << calculatePassPercentage(totalTests, fileTransferTestFailed) << "%     \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-----------------------------------------------------------------------------------" << "\033[0m" << std::endl;
  
    std::cout << "\n\n\033[1;34m-------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|" << "\033[1;32m     Tests Passed " << "\033[1;34m  | " << "\033[1;31m   Tests Failed    \033[1;34m|" << std::endl;
    std::cout << "\033[1;34m-------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|   Qtd   | Percent. |   Qtd   | Percent. |" << std::endl;
    std::cout << "\033[1;34m-------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m|" <<   "\033[1;32m   " << passedTests << "\033[1;34m   |\033[1;32m " << calculatePassPercentage(totalTests, passedTests) << "% \033[1;34m  |   \033[1;31m" << failedTests << "\033[1;34m    |\033[1;31m " <<  calculatePassPercentage(totalTests, failedTests) <<  "%\033[1;34m   |\033[0m" << std::endl;
    std::cout << "\033[1;34m-------------------------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1;34m| Total tests run    |         " << totalTests << "        |\033[0m" << std::endl;
    std::cout << "\033[1;34m-------------------------------------------" << "\033[0m\n" << std::endl;
    
    return (0);
}