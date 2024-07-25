/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileLogger.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:58:55 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 08:20:12 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <FileLogger.hpp>

FileLogger::FileLogger(void) : _logfile("/dev/null", std::ios::app) { }

FileLogger::FileLogger(const std::string filename)
	: _logfile(filename.c_str(), std::ios::app) { }

FileLogger::FileLogger(const std::string filename, t_logLevel level)
	: Logger(level), _logfile(filename.c_str(), std::ios::app) { }

FileLogger::FileLogger(FileLogger &src) : Logger(src) { }

FileLogger::~FileLogger(void) { _logfile.close(); }

FileLogger &FileLogger::operator=(FileLogger &src) {
	_logLevel = src._logLevel;
	return *this;
}

void FileLogger::debug(const std::string msg) {
	if (_logLevel <= DEBUG)
		_logfile << std::string("[DEBUG]: ") << msg << std::endl;
}

void FileLogger::info(const std::string msg) {
	if (_logLevel <= INFO)
		_logfile << "[INFO]: " << msg << std::endl;
}

void FileLogger::warn(const std::string msg) {
	if (_logLevel <= WARN)
		_logfile << "[WARN]: " << msg << std::endl;
}

void FileLogger::error(const std::string msg) {
	if (_logLevel <= ERROR)
		_logfile << "[ERROR]: " << msg << std::endl;
}

void FileLogger::fatal(const std::string msg) {
	_logfile << "[FATAL]: " << msg << std::endl;
}
