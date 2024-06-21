#include "Commands.hpp"

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
	else
		return false;
}

void Commands::commandPass( void )
{
	std::string message;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (_args.size() != 2)
	{
		message = RED + "Error: Number of invalid arguments\n" +
			"PASS <password>\n" + RESET;
	}
	else if (it->second.getStatus() == Client::AUTHENTICATED)
		message = RED + "Error: Client has already been authenticated\n" + RESET;
	else
	{
		std::string pass = _args[1];
		if (pass == _serverPass)
		{
			it->second.setStatus(Client::AUTHENTICATED);
			message = GREEN + "Your access has been approved!\n" + RESET;
		}
		else
			message = RED + "Error: Password incorrect\r\n" + RESET;
	}
	it->second.sendMessage(message);
	std::cout << message << std::endl;
}

void Commands::commandNick( void )
{
	std::string error;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (initialVerify(error, 2, "NICK <new_nickname>\n"))
	{
		std::string nick = _args[1];
		if (!validArg(nick))
			return ;
		else
			save(nick);
		return ;
	}
	it->second.sendMessage(error);
	std::cout << error << std::endl;
}

void Commands::commandUser( void )
{
	std::string error;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (initialVerify(error, 3, "USER <user> <host>\n"))
	{
		std::string user = _args[1];
		std::string host = _args[2];
		if (!validArg(user) || !validArg(host))
			return ;
		else
			save(user, host);
		return ;
	}
	it->second.sendMessage(error);
	std::cout << error << std::endl;
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
	std::cout << "Command Quit" << std::endl;
}
