// Trie class header
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Trie {
public:
    void insert(const std::string& word);
    std::vector<std::string> getSuggestions(const std::string& prefix);
};
