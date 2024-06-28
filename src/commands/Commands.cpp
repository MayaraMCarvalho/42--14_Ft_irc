/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:47:14 by macarval          #+#    #+#             */
/*   Updated: 2024/06/28 14:19:32 by macarval         ###   ########.fr       */
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
bool Commands::isCommand(int clientFd, const std::string &message)
{
	std::map<std::string, void (Commands::*)()> cmdFuncs;
	_fd = clientFd;

	cmdFuncs[PASS] = &Commands::commandPass; // OK
	cmdFuncs[NICK] = &Commands::commandNick; // OK
	cmdFuncs[USER] = &Commands::commandUser; // OK
	cmdFuncs[JOIN] = &Commands::commandJoin; // OK
	cmdFuncs[PART] = &Commands::commandPart; // OK
	cmdFuncs[PRIVMSG] = &Commands::commandPrivMsg; // OK
	cmdFuncs[KICK] = &Commands::commandKick;
	cmdFuncs[INVITE] = &Commands::commandInvite;
	cmdFuncs[TOPIC] = &Commands::commandTopic;
	cmdFuncs[MODE] = &Commands::commandMode;
	cmdFuncs[QUIT] = &Commands::commandQuit; // OK

	parsingArgs(message);

	std::map<std::string, void (Commands::*)()>::iterator it = cmdFuncs.find(_args[0]);
	if (it != cmdFuncs.end())
	{
		(this->*(it->second))();
		return true;
	}

	return false;
}

void Commands::commandKick( void )
{
	std::cout << "Command Kick" << std::endl;
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
