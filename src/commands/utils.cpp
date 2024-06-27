/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:29:02 by macarval          #+#    #+#             */
/*   Updated: 2024/06/27 11:59:21 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
void Commands::parsingArgs(const std::string &message)
{
	std::string token;
	std::istringstream tokenStream(message);

	while (std::getline(tokenStream, token, ' '))
		_args.push_back(token);
}

void Commands::save(std::string &nick)
{
	t_numCode errorCode = NO_CODE;
	std::string message;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	_clients.setNick(_fd, nick);
	errorCode = _clients.updateNick(_fd, nick);

	message = GREEN + "Nickname update successfully: " +
		BYELLOW + it->second.getNick() + "\n" + RESET;
	if (errorCode != NO_CODE)
		message = RED + "Error " + codeToString(errorCode) + "\n" + RESET;

	it->second.sendMessage(message);
	std::cout << message << std::endl;
}

void Commands::save(std::string &user, std::string &host)
{
	t_numCode errorCode = NO_CODE;
	std::string message;
	std::map<int, Client>::iterator it = _clients.getClient(_fd);

	_clients.setUser(_fd, user);
	errorCode = _clients.updateUser(_fd, user);
	it->second.setHost(host);//VERIFICAR

	message = GREEN + "User update successfully!\n" + RESET;
	if (errorCode != NO_CODE)
		message = RED + "Error " + codeToString(errorCode) + "\n" + RESET;

	it->second.sendMessage(message);
	std::cout << message << std::endl;
}

std::string Commands::codeToString(t_numCode code)
{
	std::ostringstream oss;

	oss << static_cast<int>(code);

	return oss.str();
}

std::string Commands::intToString(int num)
{
	std::ostringstream oss;

	oss << static_cast<int>(num);

	return oss.str();
}
