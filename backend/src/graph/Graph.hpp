#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../io/FileManager.hpp"
#include "../utils/utils.hpp"
#include "../search/Trie.hpp"

using namespace std;

class Graph {
private:
    unordered_map<string, unordered_set<string>> adjList;
    unordered_map<string, double> pageRank;
    unordered_map<string, string> userToId;  // username -> id
    unordered_map<string, string> idToUser;  // id -> username

    double damping = 0.85;
    int iterations = 20;

    FileManager fileManager;
    Trie userTrie;
    bool silent;

public:
    Graph(bool silentMode = false);

    bool addUser(const string& username);
    bool removeUser(const string& username);

    bool addFriendship(const string& u1, const string& u2);
    bool removeFriendship(const string& u1, const string& u2);

    vector<string> getFriends(const string& username) const;
    vector<string> getMutualFriends(const string& u1, const string& u2) const;
    bool areConnected(const string& u1, const string& u2) const;

    void computePageRank();
    void displayPageRank() const;

    vector<pair<string, double>> recommendFriends(const string& user, int topK = 3) const;

    void displayAllUsers() const;
    void clear();
    void save();

    void buildTrie();    // builds from all usernames
    vector<string> searchPrefix(const string& prefix);
};

#endif
