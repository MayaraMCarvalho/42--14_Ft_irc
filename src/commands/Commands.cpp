/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:47:14 by macarval          #+#    #+#             */
/*   Updated: 2024/07/25 18:56:56 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "IrcServer.hpp"

// Constructor & Destructor ===================================================
Commands::Commands( IRCServer& server ) : _server(server),
	_clients(_server.getClients()), _channels(_server.getChannels()),
	_serverPass(_server.getPassword()),
	_host(_server.getMsgHandler().getHost()) {}

Commands::~Commands(void) {}

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
	cmdFuncs[PASS] = &Commands::commandPass; // Ok
	cmdFuncs[NICK] = &Commands::commandNick; // Ok
	cmdFuncs[USER] = &Commands::commandUser; // Ok
	cmdFuncs[JOIN] = &Commands::commandJoin; //
	cmdFuncs[PART] = &Commands::commandPart; //
	cmdFuncs[PRIVMSG] = &Commands::commandPrivMsg; //
	cmdFuncs[KICK] = &Commands::commandKick; //
	cmdFuncs[INVITE] = &Commands::commandInvite; //
	cmdFuncs[TOPIC] = &Commands::commandTopic; //
	cmdFuncs[MODE] = &Commands::commandMode; // Faltam os RPL's
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
	if (validSetup() && initValidation(3))
	{
		std::string	nick = _args[1];
		std::string	channelName = _args[2];

		if (validArg(channelName) && validChannelName(channelName)
			&& verifyChannel(channelName) && verifyChanOp(channelName)
			&& validArg(nick) && verifyInvite(nick, channelName))
		{
			_channels.get(channelName)->second.addInvite(nick);
			printInfo(getInviting(nick, channelName));
			sendInviting(nick, channelName);
		}
	}
}

void Commands::sendInviting(std::string &nick, std::string &channelName)
{
	std::string	user = _clients.getNick(_fd);
	std::string	info;

	info = CYAN + ":" + user + "!" + user + "@" + _host + " INVITE "
			+ nick + " :" + channelName + "" + RESET;

	_clients.getClientByNick(nick)->second.sendMessage(info);
}
