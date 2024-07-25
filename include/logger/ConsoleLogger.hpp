/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleLogger.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:32:14 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 07:52:17 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_LOGGER_HPP
# define CONSOLE_LOGGER_HPP

# include <Logger.hpp>

class ConsoleLogger : public Logger {
	public:
		ConsoleLogger(void);
		ConsoleLogger(t_logLevel level);
		ConsoleLogger(ConsoleLogger &src);
		virtual ~ConsoleLogger(void);

		ConsoleLogger &operator=(ConsoleLogger &src);

		virtual void debug(const std::string msg);
		virtual void info(const std::string msg);
		virtual void warn(const std::string msg);
		virtual void error(const std::string msg);
		virtual void fatal(const std::string msg);
};

#endif
