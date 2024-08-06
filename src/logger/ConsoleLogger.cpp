/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleLogger.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:58:55 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 08:21:30 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ConsoleLogger.hpp>
#include <Colors.hpp>

ConsoleLogger::ConsoleLogger(void) { }

ConsoleLogger::ConsoleLogger(t_logLevel level) : Logger(level) { }

ConsoleLogger::ConsoleLogger(ConsoleLogger &src) : Logger(src) {
}

ConsoleLogger::~ConsoleLogger(void) { }

ConsoleLogger &ConsoleLogger::operator=(ConsoleLogger &src) {
	_logLevel = src._logLevel;
	return *this;
}

void ConsoleLogger::debug(const std::string msg) {
	if (_logLevel <= DEBUG)
		std::cerr << BBLUE << "[DEBUG]:" << RESET << ' ' << msg << std::endl;
}

void ConsoleLogger::info(const std::string msg) {
	if (_logLevel <= INFO)
		std::cerr << BGREEN  << "[INFO]:" << RESET << ' ' << msg << std::endl;
}

void ConsoleLogger::warn(const std::string msg) {
	if (_logLevel <= WARN)
		std::cerr << BYELLOW << "[WARN]:" << RESET << ' ' << msg << std::endl;
}

void ConsoleLogger::error(const std::string msg) {
	if (_logLevel <= ERROR)
		std::cerr << BRED << "[ERROR]:" << RESET << ' ' << msg << std::endl;
}

void ConsoleLogger::fatal(const std::string msg) {
	std::cerr << BPURPLE << "[FATAL]:" << RESET << ' ' << msg << std::endl;
}
