#include "Commands.hpp"

// Constructor & Destructor ===================================================
Commands::Commands(ClientList &clients, int fd) : _clients(clients), _fd(fd) {}

Commands::~Commands(void) {}

// Getters ====================================================================

// Setters ====================================================================

// Methods ====================================================================
bool Commands::isCommand(const std::string &message)
{
	std::map<std::string, void (Commands::*)()> cmdFuncs;

	cmdFuncs[NICK] = &Commands::commandNick;
	cmdFuncs[USER] = &Commands::commandUser;
	cmdFuncs[JOIN] = &Commands::commandJoin;
	cmdFuncs[PART] = &Commands::commandPart;
	cmdFuncs[PRIVMSG] = &Commands::commandPrivMsg;

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

void Commands::parsingArgs(const std::string &message)
{
	std::string token;
	std::istringstream tokenStream(message);

	while (std::getline(tokenStream, token, ' '))
		_args.push_back(token);
}

void Commands::commandNick( void )
{
	std::string message;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (_args.size() != 2)
	{
		message = RED + "Error: Number of invalid arguments\n" +
			"NICK <new_nickname>\n" + RESET;
	}
	// else if (it->second.getStatus() != 2)
	// 	message = RED + "Error: Unauthenticated clients\n" + RESET;
	else
	{
		std::string nick = _args[1];
		if (!validationsArg(nick))
			return ;
		else
			saveNick(nick);
		return ;
	}
	it->second.sendMessage(message);
	std::cout << message << std::endl;
}

void Commands::commandUser( void )
{
	std::string message;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (_args.size() != 3)
	{
		message = RED + "Error: Number of invalid arguments\n" +
			"USER <user> <host>\n" + RESET;
	}
	// else if (it->second.getStatus() != 2)
	// 	message = RED + "Error: Unauthenticated clients\n" + RESET;
	else
	{
		std::string user = _args[1];
		std::string host = _args[2];
		if (!validationsArg(user) || !validationsArg(host))
			return ;
		else
			saveUser(user, host);
		return ;
	}
	it->second.sendMessage(message);
	std::cout << message << std::endl;
}

void Commands::commandJoin( void )
{
	std::cout << GREEN << "Command Join: " << _clients.getNick(_fd) << std::endl;
}

void Commands::commandPart( void )
{
	std::cout << GREEN << "Command Part: " << _clients.getNick(_fd) << std::endl;
}

void Commands::commandPrivMsg( void )
{
	std::cout << GREEN << "Command PrivMsg: " << _clients.getNick(_fd) << std::endl;
}

// Exceptions =================================================================

// void		authenticate(Client &client, const std::string &pass, const std::string &serverPass);

// void Client::authenticate(Client &client, const std::string &pass, const std::string &serverPass)
// {
// 	std::string message;

// 	if (pass == serverPass)
// 	{
// 		client.au
// 		message = ":server 001 " + client._nickname + " :Welcome to the IRC server\r\n";
// 		send(client._fd, message.c_str(), message.length(), 0);
// 	}
// 	else
// 	{
// 		client._authenticated = false;//Verificar se é realmente necessário
// 		message = ":server 464 " + client._nickname + " :Password incorrect\r\n";
// 		send(client._fd, message.c_str(), message.length(), 0);
// 	}
// }
