#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class FileManager {
private:
    std::string filePath;

public:
    // Use dataset/users.csv as default
    FileManager(const std::string& path = "dataset/users.csv");

    void load(std::unordered_map<std::string, std::unordered_set<std::string>>& adjList);
    void save(const std::unordered_map<std::string, std::unordered_set<std::string>>& adjList);

    void addUser(const std::string& username);
    void removeUser(const std::string& username);
    void updateFriendships(const std::unordered_map<std::string, std::unordered_set<std::string>>& adjList);

private:
    std::vector<std::string> split(const std::string& s, char delimiter);
    std::string join(const std::unordered_set<std::string>& items, char delimiter);
};

#endif
