/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileTransferTest.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 02:53:00 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/26 16:58:21 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/TestFramework.hpp"

void createTestFile(const std::string &fileName, const std::vector<char> &fileData) {
    std::ofstream file(fileName.c_str());
    file.write(&fileData[0], fileData.size());
    file.close();
}

bool TestRequestTransfer(void) {
    std::cout << "\033[0;34m\nTesting FileTransfer requestTransfer method:\033[0m" << std::endl;
    bool result = true;

    FileTransfer fileTransfer;
    int senderFd = 1;
    int receiverFd = 2;
    std::string fileName = "test_file.txt";
    std::vector<char> fileData(20, ' ');

    std::ofstream file(fileName.c_str());
    file.write(&fileData[0], fileData.size());
    file.close();

    fileTransfer.requestTransfer(senderFd, receiverFd, fileName);

    std::cout << "1) Test if a transfer is initiated:" << std::endl;
    result &= ASSERT_TRUE(fileTransfer.getSenderFd(senderFd) == senderFd);
    result &= ASSERT_TRUE(fileTransfer.getReceiverFd(senderFd) == receiverFd);
    result &= ASSERT_TRUE(fileTransfer.getFileName(senderFd) == fileName);
    result &= ASSERT_TRUE(fileTransfer.getFileData(senderFd) == fileData);

    return (result);
}

bool    TestHandleTransfer(void) {
    std::cout << "\033[0;34m\nTesting FileTransfer handleTransfer method:\033[0m" << std::endl;
    bool result = true;

    FileTransfer fileTransfer;
    int socketPair[2];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socketPair) == -1) {
        std::cerr << "Failed to create socket pair" << std::endl;
        return false;
    }

    int senderFd = socketPair[0];
    int receiverFd = socketPair[1];
    std::string fileName = "test_file.txt";
    std::vector<char> fileData(1024, 'A');

    createTestFile(fileName, fileData);

    std::cout << "1) Test if handleTransfer sends a file chunk correctly:" << std::endl;
    fileTransfer.requestTransfer(senderFd, receiverFd, fileName);
    fileTransfer.handleTransfer(senderFd);

    char buffer[512];
    ssize_t bytesRead = recv(receiverFd, buffer, sizeof(buffer), 0);
    result &= ASSERT_TRUE(bytesRead > 0);
    std::cout << (result ? "Passed" : "Failed") << std::endl;

    std::cout << "2) Test if handleTransfer does nothing when clientFd is not present in _transfers:" << std::endl;
    int nonExistentFd = 3;
    fileTransfer.handleTransfer(nonExistentFd);

    bytesRead = recv(receiverFd, buffer, sizeof(buffer), 0);
    result &= ASSERT_FALSE(bytesRead == -1 && errno == EAGAIN);

    close(senderFd);
    close(receiverFd);

    return (result);
}

bool    TestSendFileChunk(void) {
    std::cout << "\033[0;34m\nTesting FileTransfer sendFileChunk method:\033[0m" << std::endl;
    bool result = true;

    FileTransfer fileTransfer;
    int socketPair[2];
    
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socketPair) == -1) {
        std::cerr << "Failed to create socket pair" << std::endl;
        return false;
    }

    int senderFd = socketPair[0];
    int receiverFd = socketPair[1];
    std::string fileName = "test_file.txt";
    std::vector<char> fileData(1024, 'A');

    createTestFile(fileName, fileData);

    std::cout << "1) Test if sendFileChunk sends a file chunk correctly:" << std::endl;
    fileTransfer.requestTransfer(senderFd, receiverFd, fileName);
    fileTransfer.sendFileChunk(senderFd);

    char buffer[512];
    ssize_t bytesRead = recv(receiverFd, buffer, sizeof(buffer), 0);
    result &= ASSERT_TRUE(bytesRead > 0);

    close(senderFd);
    close(receiverFd);

    return (result);
}

bool    TestReadFile(void) {
    std::cout << "\033[0;34m\nTesting FileTransfer readFile method:\033[0m" << std::endl;
    bool result = true;

    FileTransfer fileTransfer;
    std::string fileName = "test_file.txt";
    std::vector<char> fileData(1024, 'A');  // Usa um vetor de 1024 caracteres 'A'
    createTestFile(fileName, fileData);

    // Teste 1: Verificar se readFile lê o conteúdo do arquivo corretamente
    std::cout << "1) Test if readFile reads the file content correctly:" << std::endl;
    std::vector<char> readData = fileTransfer.readFile(fileName);
    result &= ASSERT_TRUE(readData == fileData);

    // Teste 2: Verificar se readFile retorna um vetor vazio quando o arquivo não existe
    std::cout << "2) Test if readFile returns an empty vector when the file does not exist:" << std::endl;
    std::string nonExistentFileName = "non_existent_file.txt";
    std::vector<char> emptyData = fileTransfer.readFile(nonExistentFileName);
    result &= ASSERT_TRUE(emptyData.empty());

    // Teste 3: Verificar se readFile retorna um vetor vazio quando o arquivo está vazio
    std::cout << "3) Test if readFile returns an empty vector when the file is empty:" << std::endl;
    std::string emptyFileName = "empty_file.txt";
    std::ofstream emptyFile(emptyFileName.c_str(), std::ios::binary);
    emptyFile.close();
    emptyData = fileTransfer.readFile(emptyFileName);
    result &= ASSERT_TRUE(emptyData.empty());

    return (result);
}
