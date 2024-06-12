/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:59:49 by lucperei          #+#    #+#             */
/*   Updated: 2024/05/24 17:02:24 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <string>
#include <unistd.h>
#include <cstring>
#include <iostream>

class	Bot
{
	private:
		std::string	_name;

		void	sendMessage(int client_fd, const std::string &message);

	public:
	// Constructor ============================================================
		Bot(void);
		Bot(const std::string &name);

	// Methods ================================================================
		void	respondToMessage(int client_fd, const std::string &message);

};

#endif
