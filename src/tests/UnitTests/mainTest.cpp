/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:43:29 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/23 20:23:22 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./TestFramework.hpp"

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
//bool    TestIsCommand(void);

//bool    testCommandJoin(void);
//bool    testCommandPart(void);

bool    runTest(bool (*testFunc)(void)) {
    if (testFunc()) {
        return (true);
    } else {
        return (false);
    }
}

int main(void) {
    int passedTests = 0;
    int failedTests = 0;

    std::cout << "\033[1;35m" << "\n ### Testing IrcServer ###" << "\033[0m" << std::endl;
    if (runTest(TestDefaultConstructor)) passedTests++; else failedTests++;
    if (runTest(TestParameterizedConstructor)) passedTests++; else failedTests++;
    if (runTest(TestGetPort)) passedTests++; else failedTests++;
    if (runTest(TestGetPassword)) passedTests++; else failedTests++;
    if (runTest(TestGetServerFd)) passedTests++; else failedTests++;
    if (runTest(TestGetPollFds)) passedTests++; else failedTests++;
    // if (runTest(TestGetFileTransfer)) passedTests++; else failedTests++;
    // if (runTest(TestGetBot)) passedTests++; else failedTests++;
    if (runTest(TestGetClients)) passedTests++; else failedTests++;
    //if (runTest(TestGetChannels)) passedTests++; else failedTests++;
    if (runTest(TestSetPassword)) passedTests++; else failedTests++;
    if (runTest(TestSetServerFd)) passedTests++; else failedTests++;
    if (runTest(TestSetPollFds)) passedTests++; else failedTests++;
    //if (runTest(TestSetBot)) passedTests++; else failedTests++;
    //if (runTest(TestSetChannels)) passedTests++; else failedTests++;
    if (runTest(TestSetupServerSuccess)) passedTests++; else failedTests++;
    //if (runTest(TestSetupServerSocketFailure)) passedTests++; else failedTests++;


    if (runTest(TestHandleClientMessageEmpty)) passedTests++; else failedTests++;



    if (runTest(TestSetupSignalHandlers)) passedTests++; else failedTests++;
    //if (runTest(TestAuthenticate_ValidUser)) passedTests++; else failedTests++;
    //if (runTest(TestAuthenticate_InvalidPassword)) passedTests++; else failedTests++;
    //if (runTest(TestAuthenticate_UserNotFound)) passedTests++; else failedTests++;

    std::cout << "\033[1;35m" << "\n ### Testing Client ###" << "\033[0m" << std::endl;
    if (runTest(TestClientDefaultConstructor)) passedTests++; else failedTests++;
    if (runTest(TestClientParameterizedConstructor)) passedTests++; else failedTests++;
    if (runTest(TestClientCopyConstructor)) passedTests++; else failedTests++;
    if (runTest(TestClientAssignmentOperator)) passedTests++; else failedTests++;
    // if (runTest(TestClientGetAndSetNick)) passedTests++; else failedTests++;
    if (runTest(TestClientGetAndSetUser)) passedTests++; else failedTests++;
    if (runTest(TestClientGetAndSetHost)) passedTests++; else failedTests++;
    if (runTest(TestClientGetFullId)) passedTests++; else failedTests++;
    if (runTest(TestClientGetAndSetFD)) passedTests++; else failedTests++;
    if (runTest(TestClientGetChannelList)) passedTests++; else failedTests++;
    if (runTest(TestClientGetAndSetStatus)) passedTests++; else failedTests++;
    if (runTest(TestClientGetMode)) passedTests++; else failedTests++;
    if (runTest(TestClientGetModeFlags)) passedTests++; else failedTests++;
    if (runTest(TestClientSetModeFlags)) passedTests++; else failedTests++;
    if (runTest(TestClientSetMode)) passedTests++; else failedTests++;
    if (runTest(TestClientIsInChannel)) passedTests++; else failedTests++;
    if (runTest(TestClientAddChannel)) passedTests++; else failedTests++;
    if (runTest(TestClientRemoveChannel)) passedTests++; else failedTests++;
    if (runTest(TestClientSendMessage)) passedTests++; else failedTests++;


    std::cout << "\033[1;35m" << "\n ### Testing ClientList ###" << "\033[0m" << std::endl;
    if (runTest(TestDefaultConstructorClientList)) passedTests++; else failedTests++;
    if (runTest(TestGetClientByNick)) passedTests++; else failedTests++;
    if (runTest(TestGetClientByUser)) passedTests++; else failedTests++;
    if (runTest(TestGetNick)) passedTests++; else failedTests++;
    if (runTest(TestGetUser)) passedTests++; else failedTests++;
    if (runTest(TestGetFDByNick)) passedTests++; else failedTests++;
    if (runTest(TestGetFDByUser)) passedTests++; else failedTests++;
    if (runTest(TestEnd)) passedTests++; else failedTests++;
    if (runTest(TestSetNick)) passedTests++; else failedTests++;
    if (runTest(TestSetUser)) passedTests++; else failedTests++;
    if (runTest(TestAddClient)) passedTests++; else failedTests++;
    if (runTest(TestAddClientWithAddress)) passedTests++; else failedTests++;
    if (runTest(TestAddMultipleClients)) passedTests++; else failedTests++;
    if (runTest(TestAddClientWithSameFd)) passedTests++; else failedTests++;
    if (runTest(TestAddClientWithHostname)) passedTests++; else failedTests++;
    if (runTest(TestRemoveClient)) passedTests++; else failedTests++;  
    if (runTest(TestRemoveClientByNick)) passedTests++; else failedTests++;
    if (runTest(TestRemoveClientByUser)) passedTests++; else failedTests++;
    if (runTest(TestIsValidNick)) passedTests++; else failedTests++;
    if (runTest(TestIsValidUser)) passedTests++; else failedTests++;
    if (runTest(TestIsSpecialChar)) passedTests++; else failedTests++;
    //f (runTest(TestIsCommand, "TestIsCommand")) passedTests++; else failedTests++;

    //if (runTest(testCommandJoin, "testCommandJoin")) passedTests++; else failedTests++;
    //if (runTest(testCommandPart, "testCommandPart")) passedTests++; else failedTests++;
    
    std::cout << "\033[0;32m" << "\nTests passed: " << passedTests << "\033[0m" << std::endl;
    std::cout << "\033[0;31m" << "Tests failed: " << failedTests << "\033[0m" << std::endl;
    std::cout << "All tests completed." << std::endl;
    return (0);
}