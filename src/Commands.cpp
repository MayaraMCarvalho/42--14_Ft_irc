#include "Commands.hpp"

// Constructor & Destructor ===================================================
Commands::Commands(void) {}

Commands::~Commands(void) {}

// Getters ====================================================================

// Setters ====================================================================

// Methods ====================================================================
bool Commands::isCommand(const std::string &message)
{
	std::string command = message; // Parsing da mensagem

	std::map<std::string, void (Commands::*)()> cmdFuncs;
	cmdFuncs["NICK"] = &Commands::commandNick;
	cmdFuncs["JOIN"] = &Commands::commandJoin;
	cmdFuncs["PART"] = &Commands::commandPart;
	cmdFuncs["PRIVMSG"] = &Commands::commandPrivMsg;

	std::map<std::string, void (Commands::*)()>::iterator it = cmdFuncs.find(command);
	if (it != cmdFuncs.end())
	{
		(this->*(it->second))();
		return true;
	}
	else
		return false;
}

void Commands::commandNick(void)
{
	std::cout << GREEN << "Command Nick" << std::endl;
}

void Commands::commandJoin(void)
{
	std::cout << GREEN << "Command Nick" << std::endl;
}

void Commands::commandPart(void)
{
	std::cout << GREEN << "Command Nick" << std::endl;
}

void Commands::commandPrivMsg(void)
{
	std::cout << GREEN << "Command Nick" << std::endl;
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
