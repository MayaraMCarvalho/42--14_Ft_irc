/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MockIRCServer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:54:43 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/14 20:00:40 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOCK_IRCSERVER_HPP
#define MOCK_IRCSERVER_HPP

#include <string>
#include <iostream>

class MockIRCServer {
public:
    static void sendMessage(int fd, const std::string &msg) {
        std::cerr << "Mock sendMessage called with fd: " << fd << " and msg: " << msg << std::endl;
    }
};

#endif

