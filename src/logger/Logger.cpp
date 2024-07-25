/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:42:47 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 08:06:54 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Logger.hpp>

Logger::Logger(void) : _logLevel(DEFAULT_LEVEL) { }

Logger::Logger(t_logLevel level) : _logLevel(level) { }

Logger::Logger(Logger &src) : _logLevel(src._logLevel) { }

Logger::~Logger(void) { }

Logger &Logger::operator=(Logger &src) {
	_logLevel = src._logLevel;
	return *this;
}
