/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestFramework.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:06:08 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/23 23:37:57 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FRAMEWORK_HPP
#define TEST_FRAMEWORK_HPP

#include "../include/IrcServer.hpp"
#include "../include/client/Client.hpp"
#include "../include/client/ClientList.hpp"
#include "../include/commands/Commands.hpp"
#include "../include/channel/ChannelList.hpp"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdexcept>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <string>
#include <map>

#define ASSERT_EQ(actual, expected) \
    ((actual) != (expected) ? \
        (std::cerr << "\033[0;31m" << "❌ failed: \033[0m (" << #actual << " == " << #expected << "), actual: " << actual << ", expected: " << expected << std::endl, false) : \
        (std::cerr << "\033[0;32m" << "✅ passed: \033[0m (" << #actual << " == " << #expected << "), actual: " << actual << ", expected: " << expected << std::endl, true))

#define ASSERT_ITER_EQ(actual, expected) \
    ((actual) == (expected) ? \
        (std::cerr << "\033[0;32m" << "✅ passed: \033[0m (" << #actual << " == " << #expected << "), iterators are equal." << std::endl, true) : \
        (std::cerr << "\033[0;31m" << "❌ failed: \033[0m (" << #actual << " == " << #expected << "), iterators are not equal." << std::endl, false))

#define ASSERT_ITER_NOT_END(it, end) \
    ((it) != (end) ? \
        (std::cerr << "\033[0;32m" << "✅ passed: iterator is not end." << "\033[0m" << std::endl, true) : \
        (std::cerr << "\033[0;31m" << "❌ failed: iterator should not be end (" << #it << ") != (" << #end << ") \033[0m" << std::endl, false))

#define ASSERT_ITER_END(it, end) \
    ((it) == (end) ? \
        (std::cerr << "\033[0;32m" << "✅ passed: iterator is end." << "\033[0m" << std::endl, true) : \
        (std::cerr << "\033[0;31m" << "❌ failed: iterator should be end." << "\033[0m" << std::endl, false))

#define ASSERT_TRUE(condition) \
    ((condition) ? \
        (std::cerr << "\033[0;32m" << "✅ passed: \033[0m (" << #condition << ")" << std::endl, true) : \
        (std::cerr << "\033[0;31m" << "❌ failed: \033[0m (" << #condition << ")" << std::endl, false))

#define ASSERT_FALSE(condition) \
    (!(condition) ? \
        (std::cerr << "\033[0;32m" << "✅ passed: \033[0m (" << #condition << " is false)" << std::endl, true) : \
        (std::cerr << "\033[0;31m" << "❌ failed: \033[0m (" << #condition << " is true)" << std::endl, false))

#endif
