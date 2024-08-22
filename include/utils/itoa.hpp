/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 05:59:20 by gmachado          #+#    #+#             */
/*   Updated: 2024/07/25 06:03:15 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITOA_HPP
# define ITOA_HPP

#include <sstream>

template<typename T>
std::string itoa(T num) {
	std::stringstream ss;

	ss << num;

	return ss.str();
}

#endif
