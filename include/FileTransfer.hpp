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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class FileTransfer
{
	private:
		struct TransferInfo
		{
			int					_sender_fd;
			int					_receiver_fd;
			std::string			_file_name;
			std::vector<char>	_file_data;
			size_t				_bytes_sent;

			TransferInfo() : _sender_fd(0), _receiver_fd(0), _bytes_sent(0) {}
			TransferInfo(int s_fd, int r_fd, const std::string &f_name, const std::vector<char> &f_data)
				: _sender_fd(s_fd), _receiver_fd(r_fd), _file_name(f_name), _file_data(f_data), _bytes_sent(0) {}
		};

	public:
	// Constructor ============================================================
		FileTransfer(void);

	// Methods ================================================================
		void	requestTransfer(int sender_fd, int receiver_fd, const std::string &file_name);
		void	handleTransfer(int client_fd);
		// void	sendFileChunk(int client_fd);

		std::map<int, TransferInfo>	_transfers;

		void				sendFileChunk(int client_fd);
		std::vector<char>	readFile(const std::string &file_name);
};

#endif
