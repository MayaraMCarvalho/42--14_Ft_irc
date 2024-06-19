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

#include "../include/FileTransfer.hpp"

// Constructor ================================================================
FileTransfer::FileTransfer(void) {}

// Methods ====================================================================
void FileTransfer::requestTransfer(int sender_fd, int receiver_fd, const std::string &file_name)
{
	std::vector<char>	file_data;

	file_data = readFile(file_name);
	if (!file_data.empty())
	{
		_transfers[sender_fd] = TransferInfo(sender_fd, receiver_fd, file_name, file_data);
		sendFileChunk(sender_fd);
	}
}

void FileTransfer::handleTransfer (int client_fd)
{
	if (_transfers.find(client_fd) != _transfers.end())
		sendFileChunk(client_fd);
}

void FileTransfer::sendFileChunk(int client_fd)
{
	TransferInfo	&transfer = _transfers[client_fd];
	size_t			chunk_size;
	size_t			remaining;
	size_t			to_send;
	ssize_t			sent;

	chunk_size = 512;
	remaining = transfer._file_data.size() - transfer._bytes_sent;
	to_send = std::min(chunk_size, remaining);
	sent = send(client_fd, &transfer._file_data[transfer._bytes_sent], to_send, 0);
	if (sent > 0)
		transfer._bytes_sent += sent;

	if (transfer._bytes_sent >= transfer._file_data.size())
		_transfers.erase(client_fd);
}

std::vector<char> FileTransfer::readFile(const std::string &file_name)
{
	std::ifstream	file(file_name.c_str(), std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << file_name << std::endl;
		return std::vector<char>();
	}

	file.seekg(0, std::ios::end);
	std::streampos file_size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> file_data;
	file_data.resize(static_cast<size_t>(file_size));
	file.read(&file_data[0], file_size);
	file.close();

	return (file_data);

	// return std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}
