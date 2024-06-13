/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientMap.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 01:30:27 by gmachado          #+#    #+#             */
/*   Updated: 2024/06/13 01:52:54 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "Client.hpp"

class ClientMap
{
	private:
		std::map<std::string, Client> _clientsByNick;
		std::map<int, Client *> _clientsByFD;

	public:
		ClientMap(void);
		ClientMap(ClientMap &src);

		~ClientMap(void);

		ClientMap &operator=(ClientMap &src);
};
