#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../io/FileManager.hpp"  

class Graph {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> adjList;
    std::unordered_map<std::string, double> pageRank;
    double damping = 0.85;
    int iterations = 20;
    
    FileManager fileManager;

public:
    Graph();
    // ===== User Management =====
    bool addUser(const std::string& username);
    bool removeUser(const std::string& username);

    // ===== Friendship Management =====
    bool addFriendship(const std::string& u1, const std::string& u2);
    bool removeFriendship(const std::string& u1, const std::string& u2);

    // ===== Queries =====
    std::vector<std::string> getFriends(const std::string& username) const;
    std::vector<std::string> getMutualFriends(const std::string& u1, const std::string& u2) const;
    bool areConnected(const std::string& u1, const std::string& u2) const;

    // ===== PageRank =====
    void computePageRank();
    void displayPageRank() const;

    // ===== Friend Recommendation =====
    std::vector<std::pair<std::string, double>> recommendFriends(const std::string& user, int topK = 3) const;

    // ===== Display =====
    void displayAllUsers() const;

    // ===== Utility =====
    void clear();

    // Persist current in-memory graph to CSV without clearing
    void save();
};

#endif // GRAPH_HPP