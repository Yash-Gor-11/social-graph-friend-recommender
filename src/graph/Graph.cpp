#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <algorithm>

bool Graph::addUser(const std::string& username) {
    if (adjList.count(username)) return false;
    adjList[username]; // creates empty set
    return true;
}

bool Graph::removeUser(const std::string& username) {
    if (!adjList.count(username)) return false;
    // remove username from everyone else's friend set
    for (auto &entry : adjList) {
        entry.second.erase(username);
    }
    adjList.erase(username);
    return true;
}

bool Graph::addFriendship(const std::string& u1, const std::string& u2) {
    if (u1 == u2) return false; // no self-friendship
    if (!adjList.count(u1) || !adjList.count(u2)) return false;
    adjList[u1].insert(u2);
    adjList[u2].insert(u1);
    return true;
}

bool Graph::removeFriendship(const std::string& u1, const std::string& u2) {
    if (!adjList.count(u1) || !adjList.count(u2)) return false;
    adjList[u1].erase(u2);
    adjList[u2].erase(u1);
    return true;
}

std::vector<std::string> Graph::getFriends(const std::string& username) const {
    std::vector<std::string> result;
    auto it = adjList.find(username);
    if (it == adjList.end()) return result;
    result.reserve(it->second.size());
    for (const auto &f : it->second) result.push_back(f);
    return result;
}


