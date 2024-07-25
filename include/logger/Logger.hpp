/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:32:14 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 08:07:09 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

#include <string>
#include "itoa.hpp"

class Logger {
	public:
		virtual void debug(const std::string msg) = 0;
		virtual void info(const std::string msg) = 0;
		virtual void warn(const std::string msg) = 0;
		virtual void error(const std::string msg) = 0;
		virtual void fatal(const std::string msg) = 0;

		typedef enum {
			DEBUG,
			INFO,
			WARN,
			ERROR,
			FATAL
		} t_logLevel;

	protected:
		Logger(void);
		Logger(t_logLevel level);
		Logger(Logger &src);
		virtual ~Logger(void);
		Logger &operator=(Logger &src);

		t_logLevel _logLevel;
		static const t_logLevel DEFAULT_LEVEL = INFO;
};

#endif
