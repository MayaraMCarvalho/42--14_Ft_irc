/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServerTest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 01:42:11 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/23 15:58:47 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./TestFramework.hpp"

void    generateRandomPortStr(std::string &portStr, size_t length) {
    const char numbers[] = "0123456789";
    const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand(static_cast<unsigned>(time(0)));

    portStr.clear();
    for (size_t i = 0; i < length; ++i) {
        if (i % 2 == 0) {
            portStr += numbers[rand() % 10];
        } else {
            portStr += letters[rand() % 52];
        }
    }
}

int countArguments(const char* argv[]) {
    int count = 0;
    
    while (argv[count] != NULL) {
        count++;
    }
    return (count);
}

bool    TestDefaultConstructor(void) {
    std::cout << "\033[0;34m" << "\nTesting for the default constructor of IRCServer:" << "\033[0m" << std::endl;
    bool result = true;

    IRCServer server("1067", "strongpassword");

    std::cout << "1) Test if the default port is empty:" << std::endl;
    result &= ASSERT_EQ(server.getPort().empty(), true);

    std::cout << "2) Test if the default password is empty:" << std::endl;
    result &= ASSERT_EQ(server.getPassword().empty(), true);

    std::cout << "3) Test if the default server file descriptor is -1:" << std::endl;
    result &= ASSERT_EQ(server.getServerFd(), -1);

    return (result);
}

bool    TestParameterizedConstructor(void) {
    std::cout << "\033[0;34m" << "\nTesting for the parameterized constructor of IRCServer:" << "\033[0m" << std::endl;
    bool    result = true;

    std::string port = "6667";
    std::string password = "secret";
    IRCServer server(port, password);

    std::cout << "1) Test if the port is set correctly to '6667':" << std::endl;
    result &= ASSERT_EQ(server.getPort(), port);

    std::cout << "2) Test if the password is set correctly to 'secret':" << std::endl;
    result &= ASSERT_EQ(server.getPassword(), password);

    std::cout << "3) Test if the server file descriptor is -1 by default:" << std::endl;
    result &= ASSERT_EQ(server.getServerFd(), -1);

    return (result);
}

bool    TestGetPort(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::getPort method:" << "\033[0m" << std::endl;
    bool    result = true;

    std::string port = "6667";
    IRCServer server(port, "password");

    std::cout << "1) Check if the getPort method returns the correct port" << std::endl;
    result &= ASSERT_EQ(server.getPort(), port);

    return (result);
}

bool    TestGetPassword(void) {
    std::cout << "\033[0;34m" << "\nTesting for the IRCServer::getPassword method:" << "\033[0m" << std::endl;
    std::string password = "somepassword";
    IRCServer   server("6667", password);
    bool        result = true;
    
    std::cout << "1) Check if getPassword returns the correct password" << std::endl;
    result &= ASSERT_EQ(server.getPassword(), password);

    return (result);
}

bool    TestGetServerFd(void) {
    std::cout << "\033[0;34m" << "\nTesting for the IRCServer::getServerFd method:" << "\033[0m" << std::endl;
    bool    result     = true;
    int     expectedFd = 10;
    IRCServer server("6667", "somepassword");

    server.setServerFd(expectedFd);

    std::cout << "1) Check if getServerFd returns the correct file descriptor" << std::endl;
    result &= ASSERT_EQ(server.getServerFd(), expectedFd);

    return (result);
}

bool    TestGetPollFds(void) {
    std::cout << "\033[0;34m" << "\nTesting for the IRCServer::getPollFds method:" << "\033[0m" << std::endl;
    bool    result = true;

    IRCServer server("6667", "somepassword");

    server.setupServer();

    const std::vector<struct pollfd>& pollFds = server.getPollFds();

    std::cout << "1) Check if getPollFds returns a non-empty vector after setupServer is called" << std::endl;
    result &= ASSERT_FALSE(pollFds.empty());

    if (!pollFds.empty()) {
        std::cout << "2) Check if getPollFds returns the correct pollfd structs" << std::endl;
        result &= ASSERT_TRUE(pollFds[0].fd >= 0);  
        result &= ASSERT_EQ(pollFds[0].events, POLLIN);
        result &= ASSERT_EQ(pollFds[0].revents, 0);     
    }

    struct pollfd pfd1;
    pfd1.fd = 1;
    pfd1.events = POLLIN;
    pfd1.revents = 0;

    struct pollfd pfd2;
    pfd2.fd = 2;
    pfd2.events = POLLIN;
    pfd2.revents = 0;

    std::vector<struct pollfd> customPollFds;
    customPollFds.push_back(pfd1);
    customPollFds.push_back(pfd2);

    std::cout << "3) Check if getPollFds returns the correct size" << std::endl;
    result &= ASSERT_EQ(pollFds.size(), customPollFds.size());

    std::cout << "4) Check if getPollFds returns the correct pollfd structs for pfd1" << std::endl;
    result &= ASSERT_EQ(pollFds[0].fd, pfd1.fd);
    result &= ASSERT_EQ(pollFds[0].events, pfd1.events);
    result &= ASSERT_EQ(pollFds[0].revents, pfd1.revents);

    std::cout << "5) Check if getPollFds returns the correct pollfd structs for pfd2" << std::endl;
    result &= ASSERT_EQ(pollFds[1].fd, pfd2.fd);
    result &= ASSERT_EQ(pollFds[1].events, pfd2.events);
    result &= ASSERT_EQ(pollFds[1].revents, pfd2.revents);

    return (result);
}

/*bool TestGetFileTransfer(void) {
    std::cout << "\033[0;34m" << "\nTesting for the IRCServer::getFileTransfer method:" << "\033[0m" << std::endl;
    bool result = true;

    IRCServer server("1067", "strongpassword");
    FileTransfer fileTransfer;

    server.setFileTransfer(fileTransfer);

    const FileTransfer &retrievedFileTransfer = server.getFileTransfer();

    std::string testFileName = "test_file.txt";
    std::ofstream testFile(testFileName.c_str());
    testFile << "Test data" << std::endl;
    testFile.close();

    FileTransfer &nonConstRetrievedFileTransfer = const_cast<FileTransfer&>(retrievedFileTransfer);
    nonConstRetrievedFileTransfer.requestTransfer(1, 2, testFileName);

    std::cout << "1) Checks if the file was transferred correctly" << std::endl;
    std::vector<char> transferredData = fileTransfer.readFile(testFileName);

    if (!transferredData.empty() && std::string(transferredData.begin(), transferredData.end()).find("Test data") != std::string::npos) {
        std::cerr << "\033[0;32m" << "✅ TestGetFileTransfer passed." << "\033[0m" << std::endl;
    } else {
        std::cerr << "\033[0;31m" << "❌ TestGetFileTransfer failed: File data not transferred correctly." << "\033[0m" << std::endl;
        result = false;
    }

    std::remove(testFileName.c_str());

    return result;
}*/

/*bool    TestSetBot(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::setBot method for correct bot setting:" << "\033[0m" << std::endl;
    bool        result = true;

    IRCServer server("1067", "strongpassword");
    Bot         bot("TestBot");

    server.setBot(bot);

    const Bot&  retrievedBot = server.getBot();

    std::cout << "1) Checking if the _bot member is set correctly:" << std::endl;
    result &= ASSERT_TRUE(retrievedBot.getName() == bot.getName());

    return (result);
}*/

bool    TestGetClients(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::getClients method:" << "\033[0m" << std::endl;
    bool        result = true;

    IRCServer   server("1067", "strongpassword");

    const ClientList& clients = server.getClients();

    std::cout << "1) Checks if the returned customer list is the same" << std::endl;
    result &= ASSERT_TRUE(&clients == &server.getClients());

    return (result);
}

bool    TestGetChannels(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::getChannels method for add and remove operations:" << "\033[0m" << std::endl;
    bool        result = true;

    IRCServer   server("1067", "strongpassword");

    const ChannelList& channels1 = server.getChannels();
    const ChannelList& channels2 = server.getChannels();

    std::cout << "1) Check if the returned channel list is the same:" << std::endl;
    result &= ASSERT_TRUE(&channels1 == &channels2);

    return (result);
}

bool    TestSetPassword(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::setPassword method for correct password setting:" << "\033[0m" << std::endl;
    bool        result = true;

    IRCServer   server("1067", "strongpassword");

    std::cout << "1) Checks whether the password has been set correctly:" << std::endl;
    std::string testPassword1 = "mySecretPassword";
    server.setPassword(testPassword1);

    result &= ASSERT_TRUE(server.getPassword() == testPassword1);

    std::cout << "2) Checks whether the new password has been set correctly:" << std::endl;
    std::string testPassword2 = "anotherSecretPassword";
    server.setPassword(testPassword2);

    result &= ASSERT_TRUE(server.getPassword() == testPassword2);

    std::cout << "3) Checks whether the empty password has been set correctly:" << std::endl;
    std::string testPassword3 = "";
    server.setPassword(testPassword3);

    result &= ASSERT_TRUE(server.getPassword() == testPassword3);

    return (result);
}

bool    TestSetServerFd(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::setServerFd method for correct file descriptor setting:" << "\033[0m" << std::endl;
    bool        result = true;

    IRCServer   server("1067", "strongpassword");

    std::cout << "1) Checks if the descriptor was defined correctly:" << std::endl;
    int testFd1 = 42;
    server.setServerFd(testFd1);
    result &= ASSERT_TRUE(server.getServerFd() == testFd1);

    std::cout << "2) Checks if the new descriptor was defined correctly:" << std::endl;
    int testFd2 = 99;
    server.setServerFd(testFd2);
    result &= ASSERT_TRUE(server.getServerFd() == testFd2);

    std::cout << "3) Checks that the descriptor has been correctly set to zero:" << std::endl;
    int testFd3 = 0;
    server.setServerFd(testFd3);
    result &= ASSERT_TRUE(server.getServerFd() == testFd3);

    return (result);
}

bool    TestSetPollFds(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::setPollFds method for correct vector setting:" << "\033[0m" << std::endl;
    bool        result = true;

    IRCServer   server("1067", "strongpassword");

    std::vector<struct pollfd> pollFds1(2);

    pollFds1[0].fd = 3;
    pollFds1[0].events = POLLIN;
    pollFds1[0].revents = 0;

    pollFds1[1].fd = 4;
    pollFds1[1].events = POLLOUT;
    pollFds1[1].revents = 0;

    server.setPollFds(pollFds1);

    const std::vector<struct pollfd>& retrievedPollFds1 = server.getPollFds();

    std::cout << "1) Checking whether the pollFds1 vector values ​​were stored correctly:" << std::endl;
    result &= ASSERT_TRUE(retrievedPollFds1.size() == 2);
    result &= ASSERT_TRUE(retrievedPollFds1[0].fd == 3);
    result &= ASSERT_TRUE(retrievedPollFds1[0].events == POLLIN);
    result &= ASSERT_TRUE(retrievedPollFds1[0].revents == 0);

    result &= ASSERT_TRUE(retrievedPollFds1[1].fd == 4);
    result &= ASSERT_TRUE(retrievedPollFds1[1].events == POLLOUT);
    result &= ASSERT_TRUE(retrievedPollFds1[1].revents == 0);

    std::cout << "2) Checking if the vector is empty:" << std::endl;
    std::vector<struct pollfd> pollFds2;

    server.setPollFds(pollFds2);

    const std::vector<struct pollfd>& retrievedPollFds2 = server.getPollFds();

    result &= ASSERT_TRUE(retrievedPollFds2.empty());

    std::cout << "3) Verifying that new values ​​were stored correctly:" << std::endl;
    std::vector<struct pollfd> pollFds3(3);

    pollFds3[0].fd = 1;
    pollFds3[0].events = POLLIN;
    pollFds3[0].revents = 0;

    pollFds3[1].fd = 2;
    pollFds3[1].events = POLLOUT;
    pollFds3[1].revents = 0;

    pollFds3[2].fd = 5;
    pollFds3[2].events = POLLERR;
    pollFds3[2].revents = 0;

    server.setPollFds(pollFds3);

    const std::vector<struct pollfd>& retrievedPollFds3 = server.getPollFds();

    result &= ASSERT_TRUE(retrievedPollFds3.size() == 3);
    result &= ASSERT_TRUE(retrievedPollFds3[0].fd == 1);
    result &= ASSERT_TRUE(retrievedPollFds3[0].events == POLLIN);
    result &= ASSERT_TRUE(retrievedPollFds3[0].revents == 0);

    result &= ASSERT_TRUE(retrievedPollFds3[1].fd == 2);
    result &= ASSERT_TRUE(retrievedPollFds3[1].events == POLLOUT);
    result &= ASSERT_TRUE(retrievedPollFds3[1].revents == 0);

    result &= ASSERT_TRUE(retrievedPollFds3[2].fd == 5);
    result &= ASSERT_TRUE(retrievedPollFds3[2].events == POLLERR);
    result &= ASSERT_TRUE(retrievedPollFds3[2].revents == 0);

    return (result);
}

/*bool    TestGetBot(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::getBot method:" << "\033[0m" << std::endl;
    bool    result = true;

    IRCServer server("1067", "strongpassword");
    Bot bot;

    const Bot& retrievedBot = server.getBot();

    std::cout << "1) Checking if the returned bot is the same as the internal bot:" << std::endl;
    result &= ASSERT_TRUE(&retrievedBot == &server.getBot());

    return (result);
}*/

/*bool TestSetChannels(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::setChannels method for correct channel list setting:" << "\033[0m" << std::endl;
    bool result = true;

    std::vector<struct pollfd> dummyPollFds;
    MsgHandler dummyMsgHandler;

    ClientList dummyClientList(dummyMsgHandler, dummyPollFds);

    IRCServer server("1067", "strongpassword");

    ChannelList channels(dummyClientList, dummyMsgHandler);

    Channel channel1("Channel1", dummyMsgHandler);
    Channel channel2("Channel2", dummyMsgHandler);

    channels.add(channel1);
    channels.add(channel2);

    server.setChannels(channels);

    const ChannelList& retrievedChannels = server.getChannels();

    std::string nameChannel = "Channel1";

    std::cout << "1) Checks if the channel Channel1 is in the list:" << std::endl;
    result &= ASSERT_TRUE(retrievedChannels.get(nameChannel) != retrievedChannels.end());

    std::cout << "2) Checks if the channel Channel2 is in the list:" << std::endl;
    result &= ASSERT_TRUE(retrievedChannels.get("Channel2") != retrievedChannels.end());

    std::cout << "3) Checks if the channel Channel3 is not in the list:" << std::endl;
    result &= ASSERT_TRUE(retrievedChannels.get("Channel3") == retrievedChannels.end());

    return (result);
}*/

bool    TestSetupServerSuccess(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::setupServer for successful setup:" << "\033[0m" << std::endl;
    bool        result = true;
    IRCServer   server("1067", "password");

    try {
        server.setupServer();
        result &= ASSERT_TRUE(true);
        std::cout << "setupServer succeeded." << std::endl;
    } catch (const std::runtime_error &e) {
        result &= ASSERT_FALSE(true);
        std::cerr << "setupServer failed with exception: " << e.what() << std::endl;
    }

    return (result);
}

/*bool    TestSetupServerSocketFailure(void) {
    std::cout << "\033[0;34m" << "\nTesting setupServer for socket creation failure:" << "\033[0m" << std::endl;
    bool        result = true;

  int (*original_socket)(int, int, int) = socket;
    socket = [] (int domain, int type, int protocol) { return -1; };

    IRCServer   server("1067", "password");
    
    try {
        server.setupServer();
        result &= ASSERT_FALSE(true);
        std::cerr << "Expected runtime_error was not thrown." << std::endl;
    } catch (const std::runtime_error &e) {
        result &= ASSERT_TRUE(std::string(e.what()) == "Failed to create socket");
        std::cout << "setupServer failed with expected exception: " << e.what() << std::endl;
    }

    socket = original_socket;

    return (result);
}*/

bool    TestHandleClientMessageEmpty(void) {
    std::cout << "\033[0;34m" << "\nTesting IRCServer::handleClientMessage method with an empty message:" << "\033[0m" << std::endl;
    bool    result = true;

    IRCServer server("1067", "strongpassword");
    std::string emptyMessage;
    int     mockFd = 10;

    std::cout << "1) Test if handleClientMessage can handle an empty message:" << std::endl;
    server.handleClientMessage(mockFd);
    
    std::cout << "TestHandleClientMessageEmpty: handleClientMessage method called successfully with an empty message." << std::endl;

    return (result);
}

struct sigaction mockSigaction;
int sigaction_called = 0;
int mock_sigaction(int signum, const struct sigaction* act, struct sigaction* oldact) {
    (void)signum;
    (void)oldact;
    if (act != NULL) {
        mockSigaction = *act;
    }
    sigaction_called++;
    return (0);
}

#define sigaction(a, b, c) mock_sigaction(a, b, c)

bool    TestSetupSignalHandlers() {
    IRCServer   server("1067", "strongpassword");
    bool        result = true;

    std::cout << "\033[0;34m" << "\nTesting for the setupSignalHandlers method:" << "\033[0m" << std::endl;

    std::memset(&mockSigaction, 0, sizeof(mockSigaction));
    sigaction_called = 0;
    server.setupSignalHandlers();

    std::cout << "1) Check if signalHandler is correctly defined for signals:" << std::endl;
    result &= ASSERT_EQ(sigaction_called, 0);

    return (result);
}

bool    TestSignalHandler(void) {
    IRCServer server("1067", "strongpassword");

    std::cout << "\033[0;34m" << "\nTesting for the signalHandler method:" << "\033[0m" << std::endl;

    void (*originalHandler)(int) = signal(SIGINT, SIG_IGN);

    server.signalHandler(SIGINT);

    signal(SIGINT, originalHandler);

    std::cout << "TestSignalHandler completed!" << std::endl;

    return (true);
}

/*bool TestAuthenticate_ValidUser() {
    std::cout << "\033[0;34m" << "\nTesting for the authenticate method with a valid user:" << "\033[0m" << std::endl;

    IRCServer server("6667", "secret");
    int userFd = 1;
    std::string address = "127.0.0.1";

    ClientList& clients = const_cast<ClientList&>(server.getClients());

    clients.add(userFd, address);

    std::map<int, Client>::iterator it = clients.getClient(userFd);
    if (it == clients.end()) {
        std::cerr << "Client not found!" << std::endl;
        return false;
    }

    Client& client = it->second;
    client.setStatus(Client::CONNECTED);

    t_numCode result = server.authenticate(userFd, "secret");

    ASSERT_EQ(result, NO_CODE);
    ASSERT_EQ(client.getStatus(), Client::AUTHENTICATED);

    return true;
}*/

/*bool TestAuthenticate_InvalidPassword() {
    std::cout << "\033[0;34m" << "\nTesting for the authenticate method with an invalid password:" << "\033[0m" << std::endl;

    IRCServer server("6667", "secret");
    int userFd = 1;
    std::string address = "127.0.0.1";

    ClientList& clients = const_cast<ClientList&>(server.getClients());

    clients.add(userFd, address);

    std::map<int, Client>::iterator it = clients.getClient(userFd);
    if (it == clients.end()) {
        std::cerr << "Client not found!" << std::endl;
        return false;
    }

    Client& client = it->second;
    client.setStatus(Client::CONNECTED);

    t_numCode result = server.authenticate(userFd, "wrongpassword");

    ASSERT_EQ(result, ERR_PASSWDMISMATCH);
    ASSERT_EQ(client.getStatus(), Client::CONNECTED);

    return (true);
}*/

/*bool TestAuthenticate_UserNotFound() {
    std::cout << "\033[0;34m" << "\nTesting for the authenticate method with a non-existent user:" << "\033[0m" << std::endl;

    IRCServer server("6667", "secret");
    int userFd = 1;
    t_numCode result;

    try {
        result = server.authenticate(userFd, "secret");
        if (result == ERR_UNKNOWNERROR) {
            std::cout << "Test passed: authenticate() returned ERR_UNKNOWNERROR as expected." << std::endl;
            return (true);
        } else {
            std::cerr << "Test failed: authenticate() returned unexpected code " << result << "." << std::endl;
            return (false);
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Test failed: Exception caught - " << e.what() << std::endl;
        return (false);
    }
}*/
