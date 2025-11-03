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

std::vector<std::string> Graph::getMutualFriends(const std::string& u1, const std::string& u2) const {
    std::vector<std::string> mutual;
    auto it1 = adjList.find(u1);
    auto it2 = adjList.find(u2);
    if (it1 == adjList.end() || it2 == adjList.end()) return mutual;

    // iterate over smaller set for efficiency
    const auto &set1 = it1->second;
    const auto &set2 = it2->second;
    if (set1.size() <= set2.size()) {
        for (const auto &f : set1) {
            if (set2.find(f) != set2.end()) mutual.push_back(f);
        }
    } else {
        for (const auto &f : set2) {
            if (set1.find(f) != set1.end()) mutual.push_back(f);
        }
    }
    return mutual;
}

bool Graph::areConnected(const std::string& u1, const std::string& u2) const {
    if (u1 == u2) return true;
    auto it1 = adjList.find(u1);
    auto it2 = adjList.find(u2);
    if (it1 == adjList.end() || it2 == adjList.end()) return false;

    std::unordered_set<std::string> visited;
    std::queue<std::string> q;
    q.push(u1);
    visited.insert(u1);

    while (!q.empty()) {
        auto curr = q.front(); q.pop();
        auto itCurr = adjList.find(curr);
        if (itCurr == adjList.end()) continue;
        for (const auto &nei : itCurr->second) {
            if (nei == u2) return true;
            if (visited.insert(nei).second) q.push(nei);
        }
    }
    return false;
}

void Graph::displayAllUsers() const {
    std::cout << "\nUsers and their friends:\n";
    if (adjList.empty()) {
        std::cout << "(Graph is empty)\n";
        return;
    }
    for (const auto &entry : adjList) {
        std::cout << "- " << entry.first << ": ";
        for (const auto &f : entry.second) std::cout << f << " ";
        std::cout << "\n";
    }
}

void Graph::clear() {
    adjList.clear();
}

