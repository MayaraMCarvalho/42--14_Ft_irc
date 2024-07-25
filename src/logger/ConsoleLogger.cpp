/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleLogger.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:58:55 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 07:02:26 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ConsoleLogger.hpp>
#include <Colors.hpp>

ConsoleLogger::ConsoleLogger(void) { }

ConsoleLogger::ConsoleLogger(ConsoleLogger &src) : Logger(src) {
	(void)src;
}

ConsoleLogger::~ConsoleLogger(void) { }

ConsoleLogger &ConsoleLogger::operator=(ConsoleLogger &src) {
	(void)src;
	return *this;
}

void ConsoleLogger::debug(const std::string msg) {
	std::cerr << BBLUE << "[DEBUG]: " << RESET << msg << std::endl;
}

void ConsoleLogger::info(const std::string msg) {
	std::cerr << BGREEN  << "[INFO]: " << RESET << msg << std::endl;
}

void ConsoleLogger::warn(const std::string msg) {
	std::cerr << BYELLOW << "[WARN]: " << RESET << msg << std::endl;
}

void ConsoleLogger::error(const std::string msg) {
	std::cerr << BRED << "[ERROR]: " << RESET << msg << std::endl;
}

void ConsoleLogger::fatal(const std::string msg) {
	std::cerr << BPURPLE << "[FATAL]: " << RESET << msg << std::endl;
}
