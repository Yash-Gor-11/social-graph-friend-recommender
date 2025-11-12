#pragma once
#include <unordered_map>
#include <string>
#include <vector>

class Trie {
    struct Node {
        bool isEnd = false;
        std::unordered_map<char, Node*> next;
    };
    Node* root;

    void dfs(Node* node, std::string& cur, std::vector<std::string>& out) const;

public:
    Trie();
    ~Trie();
    void insert(const std::string& word);
    std::vector<std::string> prefixSearch(const std::string& prefix, int limit = 10) const;
};

