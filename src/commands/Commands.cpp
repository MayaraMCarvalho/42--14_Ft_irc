/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:47:14 by macarval          #+#    #+#             */
/*   Updated: 2024/07/11 05:35:15 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "IrcServer.hpp"

// Constructor & Destructor ===================================================
Commands::Commands( IRCServer& server ) : _server(server),
	_clients(_server.getClients()), _channels(_server.getChannels()),
	_serverPass(_server.getPassword()) {}

Commands::~Commands(void) {}

// Getters ====================================================================

// Setters ====================================================================

// Methods ====================================================================

void Commands::extractCommands(int clientFd) {
	MsgHandler &msgHandler = _server.getMsgHandler();

	if (msgHandler.recvLength(clientFd) < 1)
		return;
	try {
		std::string &str = msgHandler.recvPop(clientFd);

		size_t startIdx = 0;
		size_t endIdx = str.find("\r\n");

		if (endIdx == std::string::npos &&
				(str.find('\n') != std::string::npos ||
					str.find('\r') != std::string::npos)) {
			std::cerr << RED << "Message contains invalid line end characters: "
			<< BYELLOW << str << RESET << std::endl;
			str.clear();
			return;
		}

		while (endIdx != std::string::npos) {
			if (!isCommand(clientFd,
					str.substr(startIdx, endIdx - startIdx))) {
				sendMessage(clientFd,
					_server.getMsgHandler().errUnknownCommand(
						_clients.getNick(clientFd),
						str.substr(startIdx, endIdx - startIdx),
						"unknown command"));
			}

			if (_server.getIsFdDisconnected())
				return;

			startIdx = endIdx + 2;
			endIdx = str.find("\r\n", startIdx);
		}

		if (startIdx == 0 || _server.getIsFdDisconnected())
			return;

		if (startIdx < str.length())
			str = str.substr(startIdx);
		else
			str.clear();

	} catch(std::out_of_range &e) {
		std::cerr << RED
			<< "Out of range exception caught while processing client messages"
			<< RESET << std::endl;
	}
}

bool Commands::isCommand(int clientFd, const std::string &message)
{
	std::map<std::string, void (Commands::*)()> cmdFuncs;

	_fd = clientFd;
	cmdFuncs[PASS] = &Commands::commandPass; // Ok c/ ressalvas
	cmdFuncs[NICK] = &Commands::commandNick; // Ok
	cmdFuncs[USER] = &Commands::commandUser; // Ok
	cmdFuncs[JOIN] = &Commands::commandJoin; //	F4
	cmdFuncs[PART] = &Commands::commandPart; //
	cmdFuncs[PRIVMSG] = &Commands::commandPrivMsg; //	F1
	cmdFuncs[KICK] = &Commands::commandKick; //
	cmdFuncs[INVITE] = &Commands::commandInvite;
	cmdFuncs[TOPIC] = &Commands::commandTopic;
	cmdFuncs[MODE] = &Commands::commandMode;
	cmdFuncs[QUIT] = &Commands::commandQuit; //

	std::cout << CYAN << "Received message from client " << clientFd
				<< ": " << BYELLOW << message << RESET << std::endl;

	parsingArgs(message);
	strToUpper(_args[0]);
	std::map<std::string, void (Commands::*)()>::iterator it =
		cmdFuncs.find(_args[0]);
	if (it != cmdFuncs.end())
	{
		(this->*(it->second))();
		return true;
	}
	return false;
}

void Commands::parsingArgs(const std::string &message)
{
	std::string			token;
	std::istringstream	tokenStream(message);

	while (std::getline(tokenStream, token, ' '))
		_args.push_back(token);
}

void Commands::commandInvite( void )
{
 std::cout << "Command Invite" << std::endl;
}

void Commands::commandTopic( void )
{
	std::cout << "Command Topic" << std::endl;
}

void Commands::commandMode( void )
{
	std::cout << "Command Mode" << std::endl;
}
