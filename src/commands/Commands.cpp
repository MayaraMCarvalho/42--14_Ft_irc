/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:47:14 by macarval          #+#    #+#             */
/*   Updated: 2024/07/22 12:28:15 by macarval         ###   ########.fr       */
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
bool Commands::isCommand(int clientFd, const std::string &message)
{
	std::map<std::string, void (Commands::*)()> cmdFuncs;

	_fd = clientFd;
	cmdFuncs[PASS] = &Commands::commandPass; // Ok
	cmdFuncs[NICK] = &Commands::commandNick; // Ok
	cmdFuncs[USER] = &Commands::commandUser; // Ok
	cmdFuncs[JOIN] = &Commands::commandJoin; // Ok
	cmdFuncs[PART] = &Commands::commandPart; // Ok
	cmdFuncs[PRIVMSG] = &Commands::commandPrivMsg; // F1 (RPL_AWAY)
	cmdFuncs[KICK] = &Commands::commandKick; // Ok
	cmdFuncs[INVITE] = &Commands::commandInvite;
	cmdFuncs[TOPIC] = &Commands::commandTopic;
	cmdFuncs[MODE] = &Commands::commandMode;
	cmdFuncs[QUIT] = &Commands::commandQuit; // Ok

	parsingArgs(message);
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
	if (initValidation(3))
	{
		std::string	nick = _args[1];
		std::string	channelName = _args[2];

		if (validArg(channelName) && validArg(nick)
			&& verifyChannel(channelName) && verifyChanOp(channelName)
			&& verifyInvite(nick, channelName))
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
			+ nick + " :" + channelName + "" + RES;

	_clients.getClientByNick(nick)->second.sendMessage(info);
	std::cout << info << std::endl; 
}

void Commands::commandTopic( void )
{
	std::cout << "Command Topic" << std::endl;
}

void Commands::commandMode( void )
{
	std::cout << "Command Mode" << std::endl;
}
