#include "Commands.hpp"

// Constructor & Destructor ===================================================
Commands::Commands(ClientList &clients, ChannelList &channels, int fd) :
		_clients(clients), _channels(channels), _fd(fd) {}

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

void Commands::commandJoin( void )
{
	std::string error;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (initialVerify(error, 2, "JOIN <#channel_name>\n"))
	{
		std::string channel = _args[1];

		if (validChannel(channel, error))
		{
			if (!validArg(channel))
				return ;
			else
			{
				_channels.join(_fd, channel);
				error = GREEN + "User successfully join the channel " +
					channel + "!\n" + RESET;
			}
		}
	}
	it->second.sendMessage(error);
	std::cout << error << std::endl;
}

void Commands::commandPart( void )
{
	std::string error;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (initialVerify(error, 2, "PART <#channel_name>\n"))
	{
		std::string channel = _args[1];

		if (validChannel(channel, error))
		{
			if (!validArg(channel))
				return ;
			else
			{
				_channels.part(_fd, channel);
				error = GREEN + "User successfully part the channel " +
					channel + "!\n" + RESET;
			}
		}
	}
	it->second.sendMessage(error);
	std::cout << error << std::endl;
}

void Commands::commandPrivMsg( void )
{
	std::string error;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	if (initialVerify(error, 3, "PRIVMSG <recipient> :<message>\n"))
	{
		std::string recipient = _args[1];
		std::string message = getMessage();
		bool isChannel = validChannel(recipient, error);

		if (!validArg(recipient) || !validMessage(message))
			return ;
		else
		{
			if (!isChannel)
			{
				if (sendMessage(_clients.getFDByNick(recipient), message))
					return ;
				error = RED + "Error: User not found\n" + RESET;
			}
			else
			{
				if (sendMessage( _channels.get(recipient), message))
					return ;
				error = RED + "Error: channel not found\n" + RESET;
			}
		}
	}
	it->second.sendMessage(error);
	std::cout << error << std::endl;
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
