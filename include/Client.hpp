/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:02:15 by lucperei          #+#    #+#             */
/*   Updated: 2024/05/24 01:44:04 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
	private:
		int			_fd;
		std::string	_nickname;
		std::string	_username;
		bool		_authenticated;

	public:
	// Constructor ============================================================
		Client(void);
		Client(int fd);

	// Getters ================================================================
		int			get_fd(void) const;
		std::string	get_nickname(void) const;
		std::string	get_username(void) const;

	// Setters ================================================================
		void		set_nickname(const std::string &nickname);
		void		set_username(const std::string &username);

	// Methods ================================================================
		bool		is_authenticated(void) const;
		void		authenticate(void);
};

#endif
