/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MockTest.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucperei <lucperei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:28:53 by lucperei          #+#    #+#             */
/*   Updated: 2024/07/14 20:24:15 by lucperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <map>
#include <set>

class MockChannelList : public ChannelList {
public:
    void join(int fd, const std::string &channel, const std::string & /*key*/) {
        channels[channel].insert(fd);
        lastAction = "join";
        lastChannel = channel;
        lastFd = fd;
    }

    void part(int fd, const std::string &channel) {
        lastAction = "part";
        lastChannel = channel;
        lastFd = fd;
    }

    std::set<int> getUsersInChannel(const std::string &channel) const {
        std::map<std::string, std::set<int> >::const_iterator it = channels.find(channel);
        if (it != channels.end()) {
            return it->second;
        }
        return std::set<int>();
    }

    std::string getLastAction() const {
        return lastAction;
    }

    std::string getLastChannel() const {
        return lastChannel;
    }

    int getLastFd() const {
        return lastFd;
    }

private:
    std::map<std::string, std::set<int> > channels;
    std::string lastAction;
    std::string lastChannel;
    int lastFd;
};

class MockClient {
public:
    void sendMessage(const std::string &message) {
        lastMessage = message;
    }
    std::string lastMessage;
};

#include <map>

class MockClientList : public ClientList {
public:
    void add(MockClient &client, int fd) {
        clients[fd] = client;
    }

    std::map<int, MockClient>::iterator getClient(int fd) {
        return clients.find(fd);
    }

    std::map<int, MockClient>::iterator end() {
        return clients.end();
    }

private:
    std::map<int, MockClient> clients;
};