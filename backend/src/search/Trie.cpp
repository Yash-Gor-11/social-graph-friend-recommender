#include "Trie.hpp"
#include <algorithm>

Trie::Trie() : root(new Node()) {}
Trie::~Trie() { /* optional: free nodes */ }

void Trie::insert(const std::string& word) {
    Node* cur = root;
    for(char c : word) {
        if(!cur->next[c]) cur->next[c] = new Node();
        cur = cur->next[c];
    }
    cur->isEnd = true;
}

void Trie::dfs(Node* node, std::string& cur, std::vector<std::string>& out) const {
    if(out.size() >= 10) return;
    if(node->isEnd) out.push_back(cur);
    for(auto& [ch, nxt] : node->next) {
        cur.push_back(ch);
        dfs(nxt, cur, out);
        cur.pop_back();
    }
}

std::vector<std::string> Trie::prefixSearch(const std::string& prefix, int limit) const {
    Node* cur = root;
    for(char c : prefix) {
        if(!cur->next.count(c)) return {};
        cur = cur->next[c];
    }
    std::vector<std::string> res;
    std::string tmp = prefix;
    dfs(cur, tmp, res);
    if((int)res.size() > limit) res.resize(limit);
    return res;
}
