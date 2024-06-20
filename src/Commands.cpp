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

	cmdFuncs["NICK"] = &Commands::commandNick;
	cmdFuncs["USER"] = &Commands::commandUser;
	cmdFuncs["JOIN"] = &Commands::commandJoin;
	cmdFuncs["PART"] = &Commands::commandPart;
	cmdFuncs["PRIVMSG"] = &Commands::commandPrivMsg;

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

	if(_args.size() != 2)
	{
		message = RED + "Error: Number of invalid arguments\n" +
			"NICK <new_nickname>\n"  + RESET;
		it->second.sendMessage(message);
			std::cout << message << std::endl;
	}
	else
	{
		std::string nick = _args[1];
		if (!validationsNick(nick))
			return ;
		else
		{
			_clients.setNick(_fd, nick);
			_clients.updateNick(_fd, nick);

			message = GREEN + "Nickname update successfully: "
				+ it->second.getNick() + "\n" + RESET;
			it->second.sendMessage(message);
			std::cout << message << std::endl;
		}
	}
}

bool Commands::validationsNick(std::string &nick)
{
	std::map<int, Client>::iterator it = _clients.getClientByNick(nick);
	std::string message = "";

	if (nick.size() > NICKNAME_MAX_LENGTH)
		message = RED + "Error: Nickname too long\n" + RESET;
	else if (!(nick.find_first_not_of(ALPHA_NUM_SET) == std::string::npos))
		message = RED + "Error: Prohibited characters found\n" + RESET;
	else if (it != _clients.end())
		message = RED + "Error: Nickname already exists\n" + RESET;
	else
		return true;
	it = _clients.getClient(_fd);
	it->second.sendMessage(message);
	std::cout << message << std::endl;
	return false;
}

void Commands::commandUser( void )
{
	std::cout << GREEN << "Command User: " << _clients.getNick(_fd) << std::endl;
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
