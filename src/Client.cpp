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
int Client::get_fd(void) const
{
	return (_fd);
}

std::string Client::get_nickname(void) const
{
	return (_nickname);
}

std::string Client::get_username(void) const
{
	return (_username);
}

// Setters ====================================================================
void Client::set_nickname(const std::string &nickname)
{
	this->_nickname = nickname;
}

void Client::set_username(const std::string &username)
{
	this->_username = username;
}

bool Client::is_authenticated(void) const
{
	return (_authenticated);
}

// Methods ====================================================================
void Client::authenticate(void)
{
	_authenticated = true;
}
