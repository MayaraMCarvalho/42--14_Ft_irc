/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileLogger.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:58:55 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 07:01:28 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <FileLogger.hpp>

FileLogger::FileLogger(void) : _logfile("/dev/null", std::ios::app) { }

FileLogger::FileLogger(const std::string filename)
	: _logfile(filename.c_str(), std::ios::app) { }

FileLogger::FileLogger(std::ofstream logfile) { (void)logfile; }

FileLogger::FileLogger(FileLogger &src) : Logger(src) { (void)src; }

FileLogger::~FileLogger(void) { _logfile.close(); }

FileLogger &FileLogger::operator=(FileLogger &src) {
	(void)src;
	return *this;
}

void FileLogger::debug(const std::string msg) {
	_logfile << std::string("[DEBUG]: ") << msg << std::endl;
}

void FileLogger::info(const std::string msg) {
	_logfile << "[INFO]: " << msg << std::endl;
}

void FileLogger::warn(const std::string msg) {
	_logfile << "[WARN]: " << msg << std::endl;
}

void FileLogger::error(const std::string msg) {
	_logfile << "[ERROR]: " << msg << std::endl;
}

void FileLogger::fatal(const std::string msg) {
	_logfile << "[FATAL]: " << msg << std::endl;
}
