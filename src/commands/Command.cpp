/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:47:14 by macarval          #+#    #+#             */
/*   Updated: 2024/08/06 17:15:36 by macarval         ###   ########.fr       */
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
	cmdFuncs[PASS] = &Commands::commandPass;
	cmdFuncs[NICK] = &Commands::commandNick;
	cmdFuncs[USER] = &Commands::commandUser;
	cmdFuncs[JOIN] = &Commands::commandJoin;
	cmdFuncs[PART] = &Commands::commandPart;
	cmdFuncs[KICK] = &Commands::commandKick;
	cmdFuncs[MODE] = &Commands::commandMode;
	cmdFuncs[QUIT] = &Commands::commandQuit;
	cmdFuncs[TOPIC] = &Commands::commandTopic;
	cmdFuncs[INVITE] = &Commands::commandInvite;
	cmdFuncs[PRIVMSG] = &Commands::commandPrivMsg;

	std::cout << CYAN << "Received message from client " << clientFd
				<< ": " << BYELLOW << message << RESET << std::endl;

	parsingArgs(message, ' ', _args);

	if (_args.size() > 0)
	{
		strToUpper(_args[0]);
		std::map<std::string, void (Commands::*)()>::iterator it =
			cmdFuncs.find(_args[0]);
		if (it != cmdFuncs.end())
		{
			(this->*(it->second))();
			return true;
		}
	}
	return false;
}

void Commands::parsingArgs(const std::string &message, char c,
						   std::vector<std::string>	&vector)
{
	std::string			token;
	std::istringstream	tokenStream(message);

	while (std::getline(tokenStream, token, c))
	{
		if (!token.empty())
			vector.push_back(token);
	}
}

void Commands::commandTopic( void )
{
	if (validSetup() && initValidation(2))
	{
		std::string	channelName = _args[1];
		std::string	topic = "";

		if (validArg(channelName)&& validChannelName(channelName)
			&& verifyChannel(channelName))
		{
			if (_args.size() > 2)
			{
				topic = getMessage(2);
				if (verifyChanOp(channelName) && validMessage(topic))
				{
					_channels.get(channelName)->second.setTopic(topic);
					std::string message = BCYAN +
						_clients.getClient(_fd)->second.getFullId() + " TOPIC "
						+ BYELLOW + channelName + PURPLE + " :" + topic + RESET;
					sendMessage(_channels.get(channelName), message);
				}
			}
			else
				printInfo(getTopic(channelName));
		}
	}
}
