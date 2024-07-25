/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:42:47 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 06:56:44 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Logger.hpp>

Logger::Logger(void) { }

Logger::Logger(Logger &src) { (void)src; }

Logger::~Logger(void) { }

Logger &Logger::operator=(Logger &src) {
	(void)src;
	return *this;
}
