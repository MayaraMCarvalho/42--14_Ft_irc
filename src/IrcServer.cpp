#include "IrcServer.hpp"
#include "Channel.hpp"
#include "Commands.hpp"

// Constructor & Destructor ===================================================
IRCServer::IRCServer(void) {}

IRCServer::~IRCServer(void) {}

IRCServer::IRCServer(const std::string &port, const std::string &password)
	: _port(port), _password(password), _serverFd(-1), _bot("ChatBot"),
	_clients(), _channels(&_clients) {}

// Getters ====================================================================
const std::string& IRCServer::getPort(void) {
    return _port;
}

const	std::string& IRCServer::getPassword(void) {
    return _password;
}

int		IRCServer::getServerFd(void) {
    return _serverFd;
}

const	std::vector<struct pollfd>& IRCServer::getPollFds(void) {
    return _pollFds;
}

const	FileTransfer& IRCServer::getFileTransfer(void) {
	return *this->_fileTransfer;
}

const	Bot& IRCServer::getBot(void) {
	return _bot;
}

const	ClientList& IRCServer::getClients(void) {
	return _clients;
}

const	ChannelList& IRCServer::getChannels(void) {
	return _channels;
}

// Setters ====================================================================
void	IRCServer::setPort(const std::string& port) {
	_port = port;
}

void	IRCServer::setPassword(const std::string& password) {
     _password = password;
}

void	IRCServer::setServerFd(int serverFd) {
    _serverFd = serverFd;
}

void	IRCServer::setPollFds(const std::vector<struct pollfd>& pollFds) {
    _pollFds = pollFds;
}

void	IRCServer::setFileTransfer(FileTransfer& fileTransfer) {
	this->_fileTransfer = &fileTransfer;
}

void	IRCServer::setBot(const Bot& bot) {
	_bot = bot;
}

void	IRCServer::setClients(ClientList& clients) {
	_clients = clients;
}

void	IRCServer::setChannels(ChannelList& channels) {
	_channels = channels;
}

// Methods ====================================================================
bool	IRCServer::isEmptyString(const std::string& str) {
    return str.empty();
}


bool	IRCServer::containsOnlyDigits(const std::string& str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool	IRCServer::validateArguments(int argc, char *argv[], std::string &port, std::string &password)
{
	int portNum;
	std::string portStr;

	if (argc != 3)
	{
		std::cerr << RED;
		std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		std::cout << RESET;
		return (false);
	}

	port = argv[1];
    portStr = argv[1];
    if (!containsOnlyDigits(portStr))
	{
		std::cerr << RED;
		std::cerr << "Error: Invalid port number: " << argv[1] << std::endl;
		std::cout << RESET;
		return (false);
	} else {
		std::istringstream iss(portStr);
		iss >> portNum;
		if (portNum <= 1024 || portNum > 65535)
		{
			std::cerr << RED;
			std::cerr << "Error: Port number out of range" << std::endl;
			std::cout << RESET;
			return (false);
		}
	}

	password = argv[2];
	if (password.empty())
	{
		std::cerr << RED;
		std::cerr << "Invalid password! "<< YELLOW << "('" << argv[2] << "')." << std::endl;
		std::cout << RESET;
		return (false);
	}

	return (true);
}

void IRCServer::setupServer(void)
{
	struct sockaddr_in address;
	int	opt;

	std::memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(std::atoi(_port.c_str()));

	_serverFd = socket(AF_INET, SOCK_STREAM, 0);

	if (_serverFd < 0)
		throw std::runtime_error("Failed to create socket");

	opt = 1;
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("Failed to set socket options");

	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Unable to set non-blocking mode on client file descriptor (fcntl)");

	if (bind(_serverFd, (struct sockaddr *)&address, sizeof(address)) < 0)
		throw std::runtime_error("Failed to bind socket");

	if (listen(_serverFd, 10) < 0)
		throw std::runtime_error("Failed to listen on socket");
		
	struct pollfd pfd = {_serverFd, POLLIN, STDIN_FILENO};
	_pollFds.push_back(pfd);
}

void IRCServer::signalHandler(int signal)
{
	if (signal == SIGINT || signal == SIGTERM || signal == SIGTSTP)
	{
		std::cout << "\nExiting gracefully." << std::endl;
		exit(EXIT_SUCCESS); // <-memory leak
	}
}

void IRCServer::setupSignalHandlers(void)
{
	struct sigaction action;
	std::memset(&action, 0, sizeof(action));
	action.sa_handler = signalHandler;

	if (sigaction(SIGINT, &action, NULL) == -1 ||
		sigaction(SIGTERM, &action, NULL) == -1 ||
		sigaction(SIGTSTP, &action, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void IRCServer::run(void)
{
	int	pollCount;

	setupServer();
	setupSignalHandlers();
	std::cout << GREEN << "Server running on port ";
	std::cout << BYELLOW << _port << RESET << std::endl;

	while (true)
	{
		pollCount = poll(_pollFds.data(), _pollFds.size(), -1);
		if (pollCount < 0)
			throw std::runtime_error("Poll error");

		if (_pollFds[0].revents & POLLIN)
			acceptNewClient();

		for (size_t i = 1; i < _pollFds.size(); ++i)
		{
			if (_pollFds[i].revents & POLLIN)
				handleClientMessage(_pollFds[i].fd);
		}
	}
}

void IRCServer::acceptNewClient(void)
{
	int	clientFd;
	struct sockaddr_in clientAddress;
	socklen_t clientLen = sizeof(clientAddress);
	clientFd = accept(_serverFd, (struct sockaddr *)&clientAddress, &clientLen);

	if (clientFd < 0)
	{
		if (errno != EWOULDBLOCK)
			std::cerr << "Failed to accept new client" << std::endl;
		return;
	}

	if (fcntl(clientFd, F_SETFL, O_NONBLOCK)) {
		throw std::runtime_error("Unable to set non-blocking mode on client file descriptor (fcntl)");
	}

	_clients.add(clientFd, &clientAddress.sin_addr);

	_channels.join(clientFd, "default", "");
	struct pollfd pfd = {clientFd, POLLIN, 0};
	_pollFds.push_back(pfd);

	std::cout << BLUE << "New client connected: ";
	std::cout << BYELLOW << clientFd << RESET << std::endl;

	std::map<int, Client>::iterator it = _clients.getClient(clientFd);
	std::string message = BPURPLE + "-------------------------------\n" +
		"------ Welcome to ft_IRC ------\n" +
		"-------------------------------\n" + RESET;
	it->second.sendMessage(message);
}

t_numCode IRCServer::authenticate(int userFD, std::string password) {
	std::map<int, Client>::iterator userIt = _clients.getClient(userFD);

	if (userIt == _clients.end()){
		// throw std::invalid_argument("Unknown user"); retorna Aborted (core dumped)
		return ERR_UNKNOWNERROR;
	}

	Client::t_status status = userIt->second.getStatus();

	if (status == Client::DISCONNECTED || status == Client::UNKNOWN)
		throw std::invalid_argument("Invalid user status");

	if (status != Client::CONNECTED)
		throw std::invalid_argument("Already authenticated");

	if (password != _password)
		return ERR_PASSWDMISMATCH;

	userIt->second.setStatus(Client::AUTHENTICATED);
	return NO_CODE;
}

void IRCServer::handleClientMessage(int clientFd)
{
	char	buffer[512];
	ssize_t	nbytes;

	std::memset(buffer, 0, sizeof(buffer));
	nbytes = recv(clientFd, buffer, sizeof(buffer) - 1, 0); // read client data

	if (nbytes <= 0)
	{
		std::cout << RED;
		if (nbytes < 0 && errno != EWOULDBLOCK)
			std::cerr << "Read error on client " << clientFd << std::endl;
		else if (nbytes == 0)
			std::cout << "Client disconnected: " << BYELLOW << clientFd << std::endl;
		std::cout << RESET;
		removeClient(clientFd);
		return;
	}

	buffer[nbytes] = '\0';
	std::string message(buffer);

	//
	if (!message.empty() && message[message.length() - 1] == '\n')
		message.erase(message.length() - 1);
	//

	std::cout << CYAN;
	std::cout << "Received message from client " << clientFd;
	std::cout << ": " << BYELLOW << message << RESET << std::endl;

	//
	//
	//
	Commands commands(this->_clients, this->_channels, clientFd);
	bool isCommand = false;
	if (!message.empty() && commands.isCommand(message))
	{
		isCommand = true;
	}
	//
	else if (message.substr(0, 5) == "/file")
		handleFileTransfer(clientFd, message);
	else
		_bot.respondToMessage(clientFd, message); // call for the bot to respond

	std::map<std::string, Channel>::iterator it = _channels.get("default");

	if (!isCommand)
	{
		if (it != _channels.end())
			it->second.sendToAll(message);
		else
			std::cerr << "Failed to send message to channel default" << std::endl;
	}
}

void IRCServer::removeClient(int clientFd)
{
	close(clientFd);

	_channels.partDisconnectedClient(clientFd);

	for (std::vector<struct pollfd>::iterator it = _pollFds.begin(); it != _pollFds.end(); ++it)
	{
		if (it->fd == clientFd)
		{
			_pollFds.erase(it);
			break;
		}
	}

	_clients.remove(clientFd);
}

void IRCServer::sendMessage(int clientFd, const std::string &message)
{
	ssize_t	nbytes;

	std::string fullMessage = message + "\n";
	nbytes = send(clientFd, fullMessage.c_str(), fullMessage.length(), 0);
	if (nbytes < 0)
	{
		std::cerr << RED << "Write error on client " << clientFd << std::endl;
		std::cout << RESET;
	}
}

void IRCServer::handleFileTransfer(int clientFd, const std::string &command)
{
	std::istringstream	iss(command);
	std::string			cmd, fileName;
	int					receiverFd;

	iss >> cmd >> receiverFd >> fileName;
	_fileTransfer->requestTransfer(clientFd, receiverFd, fileName); // starts file transfer
}

// Exceptions =================================================================