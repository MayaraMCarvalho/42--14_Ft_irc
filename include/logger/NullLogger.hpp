/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NullLogger.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:32:14 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 07:02:36 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NULL_LOGGER_HPP
# define NULL_LOGGER_HPP

# include <Logger.hpp>

class NullLogger : public Logger {
	public:
		NullLogger(void);
		NullLogger(NullLogger &src);
		virtual ~NullLogger(void);

		NullLogger &operator=(NullLogger &src);

		virtual void debug(const std::string msg);
		virtual void info(const std::string msg);
		virtual void warn(const std::string msg);
		virtual void error(const std::string msg);
		virtual void fatal(const std::string msg);
};

#endif
