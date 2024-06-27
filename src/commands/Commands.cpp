#include "Commands.hpp"
#include "IrcServer.hpp"

// Constructor & Destructor ===================================================
Commands::Commands(ClientList &clients, ChannelList &channels,
	int fd, const std::string &pass) :
		_clients(clients), _channels(channels), _fd(fd), _serverPass(pass) {}

Commands::~Commands(void) {}

// Getters ====================================================================

// Setters ====================================================================

// Methods ====================================================================
bool Commands::isCommand(const std::string &message)
{
	std::map<std::string, void (Commands::*)()> cmdFuncs;

	cmdFuncs[PASS] = &Commands::commandPass;
	cmdFuncs[NICK] = &Commands::commandNick;
	cmdFuncs[USER] = &Commands::commandUser;
	cmdFuncs[JOIN] = &Commands::commandJoin;
	cmdFuncs[PART] = &Commands::commandPart;
	cmdFuncs[PRIVMSG] = &Commands::commandPrivMsg;
	cmdFuncs[KICK] = &Commands::commandKick;
	cmdFuncs[INVITE] = &Commands::commandInvite;
	cmdFuncs[TOPIC] = &Commands::commandTopic;
	cmdFuncs[MODE] = &Commands::commandMode;
	cmdFuncs[QUIT] = &Commands::commandQuit;

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

void Commands::commandQuit( void )
{
	if (initialVerify(1, "QUIT <message(optional)>\n"))
	{
		std::string message = RED + "Client " + BYELLOW + intToString(_fd)
			+ RED + " left the channel ";

		for (std::map<std::string, Channel>::iterator it = _channels.begin();
			it != _channels.end(); ++it)
		{
			if (it->second.userIsInChannel(_fd))
				it->second.sendToAll(message + BCYAN + it->second.getName()
					+ RESET + getClientMessage());
		}

		quitServer();
	}
}

void Commands::quitServer( void )
{
	IRCServer server;

	server.removeClient(_fd);
	_channels.partDisconnectedClient(_fd);
	std::cout << RED << "Client disconnected: ";
	std::cout << BYELLOW << _fd << RESET << std::endl;
}

std::string Commands::getClientMessage( void )
{
	std::string messageClient = "";

	if (_args.size() > 1)
	{
		std::string message = getMessage(1);
		if (validMessage(message))
		{
			messageClient = BLUE + "\nAnd sent the following farewell message: "
				+ BGREEN + messageClient + RESET;
		}
	}
	return messageClient;
}
