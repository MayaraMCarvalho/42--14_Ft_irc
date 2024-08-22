/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileLogger.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:32:14 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 07:59:54 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_LOGGER_HPP
# define FILE_LOGGER_HPP

# include <fstream>
# include <Logger.hpp>

class FileLogger : public Logger {
	private:
		std::ofstream _logfile;
		FileLogger(void);

		FileLogger(FileLogger &src);

		FileLogger &operator=(FileLogger &src);

	public:
		FileLogger(const std::string filename);
		FileLogger(const std::string filename, t_logLevel level);
		virtual ~FileLogger(void);

		virtual void debug(const std::string msg);
		virtual void info(const std::string msg);
		virtual void warn(const std::string msg);
		virtual void error(const std::string msg);
		virtual void fatal(const std::string msg);
};

#endif
