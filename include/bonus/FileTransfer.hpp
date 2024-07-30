/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileTransfer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:39:30 by lucperei          #+#    #+#             */
/*   Updated: 2024/05/24 01:21:16 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_TRANSFER_HPP
#define FILE_TRANSFER_HPP

#include <sys/socket.h>
#include <string>
#include <vector>
#include <map>

class FileTransfer
{
	private:
		struct TransferInfo
		{
			int					_senderFd;
			int					_receiverFd;
			std::string			_fileName;
			std::vector<char>	_fileData;
			size_t				_bytesSent;

			TransferInfo() : _senderFd(0), _receiverFd(0), _bytesSent(0) {}
			TransferInfo(int sFd, int rFd, const std::string &fName, const std::vector<char> &fData)
				: _senderFd(sFd), _receiverFd(rFd), _fileName(fName), _fileData(fData), _bytesSent(0) {}
		};

	public:
	// Constructor ============================================================
		FileTransfer(void);

	// Getter ============================================================
		int getSenderFd(int fd) const;
		int getReceiverFd(int fd) const;
		std::string getFileName(int fd) const;
		 std::vector<char> getFileData(int fd) const;
		std::map<int, TransferInfo> getTransfers(void) const;

	// Methods ================================================================
		void	requestTransfer(int senderFd, int receiverFd, const std::string &fileName);
		void	handleTransfer(int clientFd);
		void	sendFileChunk(int clientFd);
		std::vector<char>	readFile(const std::string &fileName);
		TransferInfo getTransferInfo(int fd) const;

		std::map<int, TransferInfo>	_transfers;

};

#endif
