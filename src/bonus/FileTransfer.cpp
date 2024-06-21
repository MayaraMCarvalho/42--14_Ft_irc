/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileTransfer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:43:46 by lucperei          #+#    #+#             */
/*   Updated: 2024/05/25 11:35:56 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileTransfer.hpp"

// Constructor ================================================================
FileTransfer::FileTransfer(void) {}

// Methods ====================================================================
void FileTransfer::requestTransfer(int senderFd, int receiverFd, const std::string &fileName)
{
	std::vector<char>	fileData;

	fileData = readFile(fileName);
	if (!fileData.empty())
	{
		_transfers[senderFd] = TransferInfo(senderFd, receiverFd, fileName, fileData);
		sendFileChunk(senderFd);
	}
}

void FileTransfer::handleTransfer (int clientFd)
{
	if (_transfers.find(clientFd) != _transfers.end())
		sendFileChunk(clientFd);
}

void FileTransfer::sendFileChunk(int clientFd)
{
	TransferInfo	&transfer = _transfers[clientFd];
	size_t			chunkSize;
	size_t			remaining;
	size_t			toSend;
	ssize_t			sent;

	chunkSize = 512;
	remaining = transfer._fileData.size() - transfer._bytesSent;
	toSend = std::min(chunkSize, remaining);
	sent = send(clientFd, &transfer._fileData[transfer._bytesSent], toSend, 0);
	if (sent > 0)
		transfer._bytesSent += sent;

	if (transfer._bytesSent >= transfer._fileData.size())
		_transfers.erase(clientFd);
}

std::vector<char> FileTransfer::readFile(const std::string &fileName)
{
	std::ifstream	file(fileName.c_str(), std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << fileName << std::endl;
		return std::vector<char>();
	}

	file.seekg(0, std::ios::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> fileData;
	fileData.resize(static_cast<size_t>(fileSize));
	file.read(&fileData[0], fileSize);
	file.close();

	return (fileData);

	// return std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}
