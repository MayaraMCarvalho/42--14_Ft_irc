/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NullLogger.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:58:55 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 08:10:29 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <NullLogger.hpp>

NullLogger::NullLogger(void) { }

NullLogger::NullLogger(t_logLevel level) : Logger(level) { }

NullLogger::NullLogger(NullLogger &src) : Logger(src) { }

NullLogger::~NullLogger(void) { }

NullLogger &NullLogger::operator=(NullLogger &src) {
	(void)src;
	return *this;
}

void NullLogger::debug(const std::string msg) { (void)msg; }

void NullLogger::info(const std::string msg) { (void)msg; }

void NullLogger::warn(const std::string msg) { (void)msg; }

void NullLogger::error(const std::string msg) { (void)msg; }

void NullLogger::fatal(const std::string msg) { (void)msg; }
