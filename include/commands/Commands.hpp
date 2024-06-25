/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:17:29 by macarval          #+#    #+#             */
/*   Updated: 2024/06/25 04:58:16 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <map>

# include "../include/Colors.hpp"

class Commands
{
	private:

	public:
	// Constructor & Destructor ===============================================
		Commands( void );
		~Commands( void );
	// Exceptions =============================================================

	// Getters ================================================================

	// Setters ================================================================

	// Methods ================================================================
		bool		isCommand(const std::string &message);
		void		commandNick(void);
		void		commandJoin(void);
		void		commandPart(void);
		void		commandPrivMsg(void);
};

#endif
