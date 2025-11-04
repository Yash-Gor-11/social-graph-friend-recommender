#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class FileManager {
private:
    string filePath;

public:
    FileManager(const string& path = "dataset/users.csv");

    // Load and save using hashed IDs
    void loadWithHashes(unordered_map<string, unordered_set<string>>& adjList,
                        unordered_map<string, string>& idToUser,
                        unordered_map<string, string>& userToId);

    void saveWithHashes(const unordered_map<string, unordered_set<string>>& adjList,
                        const unordered_map<string, string>& idToUser,
                        const unordered_map<string, string>& userToId);

    // Incremental updates
    void addUser(const string& id, const string& username);
    void removeUser(const string& id);
    void updateFriendships(const unordered_map<string, unordered_set<string>>& adjList,
                           const unordered_map<string, string>& userToId);

private:
    vector<string> split(const string& s, char delimiter);
    string join(const vector<string>& items, char delimiter);
};

#endif
