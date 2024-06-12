/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:01:59 by lucperei          #+#    #+#             */
/*   Updated: 2024/05/25 11:35:58 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

// Constructor & Destructor ===================================================
Client::Client(void) : _fd(-1), _authenticated(false) {}

Client::Client(int fd) : _fd(fd), _authenticated(false) {}

// Getters ====================================================================
int Client::getFd(void) const
{
	return (_fd);
}

std::string Client::getNickname(void) const
{
	return (_nickname);
}

std::string Client::getUsername(void) const
{
	return (_username);
}

// Setters ====================================================================
void Client::setNickname(const std::string &nickname)
{
	this->_nickname = nickname;
}

void Client::setUsername(const std::string &username)
{
	this->_username = username;
}

bool Client::isAuthenticated(void) const
{
	return (_authenticated);
}

// Methods ====================================================================
void Client::authenticate(void)
{
	_authenticated = true;
}
