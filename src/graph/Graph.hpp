#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Graph {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> adjList;

public:
    // Basic User Management
    bool addUser(const std::string& username);
    bool removeUser(const std::string& username);

    // Friendship Management
    bool addFriendship(const std::string& u1, const std::string& u2);
    bool removeFriendship(const std::string& u1, const std::string& u2);

    // Querying
    std::vector<std::string> getFriends(const std::string& username) const;
    std::vector<std::string> getMutualFriends(const std::string& u1, const std::string& u2) const;
    bool areConnected(const std::string& u1, const std::string& u2) const;

    // Display
    void displayAllUsers() const;

    // Utility
    void clear();
};

#endif // GRAPH_HPP
