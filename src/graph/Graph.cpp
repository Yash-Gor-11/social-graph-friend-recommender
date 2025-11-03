#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#include <iomanip>

// =================== BASIC USER MANAGEMENT ===================

bool Graph::addUser(const std::string& username) {
    if (adjList.count(username)) return false;
    adjList[username]; // create empty friend list
    return true;
}

bool Graph::removeUser(const std::string& username) {
    if (!adjList.count(username)) return false;
    for (auto &entry : adjList) entry.second.erase(username);
    adjList.erase(username);
    return true;
}

// =================== FRIENDSHIP MANAGEMENT ===================

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

// =================== FRIEND QUERYING ===================

std::vector<std::string> Graph::getFriends(const std::string& username) const {
    std::vector<std::string> result;
    auto it = adjList.find(username);
    if (it == adjList.end()) return result;
    for (const auto &f : it->second) result.push_back(f);
    return result;
}

std::vector<std::string> Graph::getMutualFriends(const std::string& u1, const std::string& u2) const {
    std::vector<std::string> mutual;
    auto it1 = adjList.find(u1);
    auto it2 = adjList.find(u2);
    if (it1 == adjList.end() || it2 == adjList.end()) return mutual;

    const auto &set1 = it1->second;
    const auto &set2 = it2->second;

    if (set1.size() <= set2.size()) {
        for (const auto &f : set1)
            if (set2.find(f) != set2.end()) mutual.push_back(f);
    } else {
        for (const auto &f : set2)
            if (set1.find(f) != set1.end()) mutual.push_back(f);
    }
    return mutual;
}

bool Graph::areConnected(const std::string& u1, const std::string& u2) const {
    if (u1 == u2) return true;
    if (!adjList.count(u1) || !adjList.count(u2)) return false;

    std::unordered_set<std::string> visited;
    std::queue<std::string> q;
    q.push(u1);
    visited.insert(u1);

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        for (const auto &nei : adjList.at(curr)) {
            if (nei == u2) return true;
            if (visited.insert(nei).second)
                q.push(nei);
        }
    }
    return false;
}

// =================== PAGE RANK ===================

void Graph::computePageRank() {
    int N = adjList.size();
    if (N == 0) {
        std::cout << "⚠️  Graph is empty.\n";
        return;
    }

    double initRank = 1.0 / N;
    for (auto &p : adjList)
        pageRank[p.first] = initRank;

    for (int i = 0; i < iterations; i++) {
        std::unordered_map<std::string, double> newRank;
        for (auto &p : adjList)
            newRank[p.first] = (1.0 - damping) / N;

        for (auto &p : adjList) {
            const auto &u = p.first;
            const auto &friends = p.second;
            if (friends.empty()) continue;

            double share = damping * pageRank[u] / friends.size();
            for (const auto &v : friends)
                newRank[v] += share;
        }
        pageRank = newRank;
    }

    std::cout << "\n✅ PageRank computed successfully!\n";
}

void Graph::displayPageRank() const {
    if (pageRank.empty()) {
        std::cout << "⚠️  PageRank not computed yet.\n";
        return;
    }
    std::cout << "\n--- 📊 PageRank Scores ---\n";
    for (auto &p : pageRank)
        std::cout << p.first << ": " << std::fixed << std::setprecision(4) << p.second << "\n";
}

// =================== FRIEND RECOMMENDATION ===================

std::vector<std::pair<std::string, double>> Graph::recommendFriends(const std::string& user, int topK) const {
    if (!adjList.count(user)) {
        std::cout << "⚠️  User not found.\n";
        return {};
    }

    std::unordered_set<std::string> friends = adjList.at(user);
    friends.insert(user); // exclude self

    std::unordered_map<std::string, double> score;

    for (const auto &p : adjList) {
        const std::string &candidate = p.first;
        if (friends.count(candidate)) continue;

        auto mutual = getMutualFriends(user, candidate);
        double mutualCount = mutual.size();
        double influence = pageRank.count(candidate) ? pageRank.at(candidate) : 1.0;

        score[candidate] = mutualCount * influence;
    }

    std::vector<std::pair<std::string, double>> sorted(score.begin(), score.end());
    std::sort(sorted.begin(), sorted.end(),
              [](auto &a, auto &b) { return a.second > b.second; });

    std::cout << "\n--- 🤖 Friend Recommendations for " << user << " ---\n";
    int count = 0;
    for (auto &p : sorted) {
        if (p.second <= 0) continue;
        std::cout << "👉 " << p.first
                  << " | Score: " << std::fixed << std::setprecision(4) << p.second << "\n";
        if (++count >= topK) break;
    }

    if (count == 0)
        std::cout << "⚠️  No friend recommendations available.\n";

    return sorted;
}

// =================== DISPLAY AND UTILITY ===================

void Graph::displayAllUsers() const {
    std::cout << "\n--- 👥 Users and their Friends ---\n";
    if (adjList.empty()) {
        std::cout << "(Graph is empty)\n";
        return;
    }
    for (const auto &entry : adjList) {
        std::cout << "- " << entry.first << ": ";
        for (const auto &f : entry.second)
            std::cout << f << " ";
        std::cout << "\n";
    }
}

void Graph::clear() {
    adjList.clear();
    pageRank.clear();
    std::cout << "🧹 Graph cleared.\n";
}
