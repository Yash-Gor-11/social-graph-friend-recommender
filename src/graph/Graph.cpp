#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

// Constructor: load CSV data at start
Graph::Graph() : fileManager("dataset/users.csv") {
    fileManager.loadWithHashes(adjList, idToUser, userToId);
}

// =================== USER MANAGEMENT ===================

bool Graph::addUser(const string& username) {
    if (adjList.count(username)) return false;
    string id = generateHashId(username);
    userToId[username] = id;
    idToUser[id] = username;
    adjList[username];
    fileManager.addUser(id, username);
    return true;
}

bool Graph::removeUser(const string& username) {
    if (!adjList.count(username)) return false;
    for (auto& entry : adjList) entry.second.erase(username);
    adjList.erase(username);
    if (userToId.count(username)) {
        string id = userToId[username];
        userToId.erase(username);
        idToUser.erase(id);
        fileManager.removeUser(id);
    }
    return true;
}

// =================== FRIENDSHIP MANAGEMENT ===================

bool Graph::addFriendship(const string& u1, const string& u2) {
    if (u1 == u2) return false;
    if (!adjList.count(u1) || !adjList.count(u2)) return false;
    adjList[u1].insert(u2);
    adjList[u2].insert(u1);
    fileManager.updateFriendships(adjList, userToId);
    return true;
}

bool Graph::removeFriendship(const string& u1, const string& u2) {
    if (!adjList.count(u1) || !adjList.count(u2)) return false;
    adjList[u1].erase(u2);
    adjList[u2].erase(u1);
    fileManager.updateFriendships(adjList, userToId);
    return true;
}

// =================== FRIEND QUERYING ===================

vector<string> Graph::getFriends(const string& username) const {
    vector<string> result;
    auto it = adjList.find(username);
    if (it == adjList.end()) return result;
    result.insert(result.end(), it->second.begin(), it->second.end());
    return result;
}

vector<string> Graph::getMutualFriends(const string& u1, const string& u2) const {
    vector<string> mutual;
    auto it1 = adjList.find(u1);
    auto it2 = adjList.find(u2);
    if (it1 == adjList.end() || it2 == adjList.end()) return mutual;

    const auto& set1 = it1->second;
    const auto& set2 = it2->second;
    for (const auto& f : set1)
        if (set2.find(f) != set2.end()) mutual.push_back(f);
    return mutual;
}

bool Graph::areConnected(const string& u1, const string& u2) const {
    if (u1 == u2) return true;
    if (!adjList.count(u1) || !adjList.count(u2)) return false;

    unordered_set<string> visited;
    queue<string> q;
    q.push(u1);
    visited.insert(u1);

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        for (const auto& nei : adjList.at(curr)) {
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
        cout << "Graph is empty.\n";
        return;
    }

    double initRank = 1.0 / N;
    for (auto& p : adjList)
        pageRank[p.first] = initRank;

    for (int i = 0; i < iterations; i++) {
        unordered_map<string, double> newRank;
        for (auto& p : adjList)
            newRank[p.first] = (1.0 - damping) / N;

        for (auto& p : adjList) {
            const auto& u = p.first;
            const auto& friends = p.second;
            if (friends.empty()) continue;

            double share = damping * pageRank[u] / friends.size();
            for (const auto& v : friends)
                newRank[v] += share;
        }
        pageRank = newRank;
    }

    cout << "\nPageRank computed successfully!\n";
}

void Graph::displayPageRank() const {
    if (pageRank.empty()) {
        cout << "PageRank not computed yet.\n";
        return;
    }
    cout << "\n--- PageRank Scores ---\n";
    for (auto& p : pageRank)
        cout << p.first << ": " << fixed << setprecision(4) << p.second << "\n";
}

// =================== FRIEND RECOMMENDATION ===================

vector<pair<string, double>> Graph::recommendFriends(const string& user, int topK) const {
    if (!adjList.count(user)) {
        cout << "User not found.\n";
        return {};
    }

    unordered_set<string> friends = adjList.at(user);
    friends.insert(user);

    unordered_map<string, double> score;

    for (const auto& p : adjList) {
        const string& candidate = p.first;
        if (friends.count(candidate)) continue;

        auto mutual = getMutualFriends(user, candidate);
        double mutualCount = mutual.size();
        double influence = pageRank.count(candidate) ? pageRank.at(candidate) : 1.0;

        score[candidate] = mutualCount * influence;
    }

    vector<pair<string, double>> sorted(score.begin(), score.end());
    sort(sorted.begin(), sorted.end(),
         [](auto& a, auto& b) { return a.second > b.second; });

    cout << "\n--- Friend Recommendations for " << user << " ---\n";
    int count = 0;
    for (auto& p : sorted) {
        if (p.second <= 0) continue;
        cout << p.first << " | Score: " << fixed << setprecision(4) << p.second << "\n";
        if (++count >= topK) break;
    }

    if (count == 0)
        cout << "No friend recommendations available.\n";

    return sorted;
}

// =================== DISPLAY AND UTILITY ===================

void Graph::displayAllUsers() const {
    cout << "\n--- Users and their Friends ---\n";
    if (adjList.empty()) {
        cout << "(Graph is empty)\n";
        return;
    }
    for (const auto& entry : adjList) {
        cout << "- " << entry.first << ": ";
        for (const auto& f : entry.second)
            cout << f << " ";
        cout << "\n";
    }
}

void Graph::clear() {
    adjList.clear();
    pageRank.clear();
    userToId.clear();
    idToUser.clear();
    fileManager.saveWithHashes(adjList, idToUser, userToId);
    cout << "Graph cleared.\n";
}

void Graph::save() {
    fileManager.saveWithHashes(adjList, idToUser, userToId);
}
