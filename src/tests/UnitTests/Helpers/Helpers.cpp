/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Helpers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:20:11 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/25 22:48:57 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Helpers.hpp"

bool    runTest(bool (*testFunc)(void)) {
    if (testFunc()) {
        return (true);
    } else {
        return (false);
    }
}

double calculatePassPercentage(int totalTests, int tests) {
    return (totalTests > 0) ? (static_cast<double>(tests) / totalTests) * 100 : 0;
}
