// Graph class header
#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class Graph {
public:
    void addUser(const std::string& username);
    void addFriendship(const std::string& user1, const std::string& user2);
    std::vector<std::string> recommendFriends(const std::string& username);
};
