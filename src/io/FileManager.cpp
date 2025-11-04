#include "FileManager.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

FileManager::FileManager(const std::string& path) {
    // Determine a sensible base (project root). If running from build/, go one level up.
    std::filesystem::path base = std::filesystem::current_path();
    if (base.filename() == "build" || base.filename() == "Build")
        base = base.parent_path();

    // If a relative path was provided, make it relative to base. Otherwise use the absolute path.
    std::filesystem::path p(path);
    if (p.is_relative())
        filePath = (base / p).lexically_normal().string();
    else
        filePath = p.lexically_normal().string();

    std::filesystem::create_directories(std::filesystem::path(filePath).parent_path());
}

std::vector<std::string> FileManager::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        if (!item.empty()) tokens.push_back(item);
    }
    return tokens;
}

std::string FileManager::join(const std::unordered_set<std::string>& items, char delimiter) {
    // Produce deterministic order: copy to vector and sort.
    std::vector<std::string> vec(items.begin(), items.end());
    std::sort(vec.begin(), vec.end());
    std::string result;
    bool first = true;
    for (const auto &item : vec) {
        if (!first) result.push_back(delimiter);
        result += item;
        first = false;
    }
    return result;
}

void FileManager::load(std::unordered_map<std::string, std::unordered_set<std::string>>& adjList) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "users.csv not found at " << filePath << ", starting fresh.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string username, friendsField;
        std::getline(ss, username, ',');
        std::getline(ss, friendsField, ',');

        // Trim possible Windows CR at end of fields
        if (!friendsField.empty() && friendsField.back() == '\r') friendsField.pop_back();
        if (!username.empty() && username.back() == '\r') username.pop_back();

        std::unordered_set<std::string> friends;
        for (auto& f : split(friendsField, '|')) {
            if (!f.empty()) friends.insert(f);
        }
        if (!username.empty())
            adjList[username] = friends;
    }

    file.close();
    std::cout << "Loaded users from " << filePath << "\n";
}

void FileManager::save(const std::unordered_map<std::string, std::unordered_set<std::string>>& adjList) {
    // Write deterministic rows: sort user keys first
    std::vector<std::string> users;
    users.reserve(adjList.size());
    for (const auto &p : adjList) users.push_back(p.first);
    std::sort(users.begin(), users.end());

    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filePath << " for writing.\n";
        return;
    }

    for (const auto &user : users) {
        const auto &friends = adjList.at(user);
        file << user << ",";
        file << join(friends, '|') << "\n";
    }

    file.close();
    std::cout << "Data saved to " << filePath << "\n";
}

void FileManager::addUser(const std::string& username) {
    std::ofstream file(filePath, std::ios::app);
    if (!file.is_open()) return;
    file << username << ",\n";
    file.close();
}

void FileManager::removeUser(const std::string& username) {
    std::ifstream in(filePath);
    if (!in.is_open()) return;

    std::stringstream buffer;
    std::string line;

    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string user, friendsField;
        std::getline(ss, user, ',');
        std::getline(ss, friendsField, ',');

        // Trim CR
        if (!friendsField.empty() && friendsField.back() == '\r') friendsField.pop_back();
        if (!user.empty() && user.back() == '\r') user.pop_back();

        if (user == username) continue;

        auto friends = split(friendsField, '|');
        std::string newFriends;
        for (auto& f : friends)
            if (f != username) newFriends += f + "|";
        if (!newFriends.empty()) newFriends.pop_back();

        buffer << user << "," << newFriends << "\n";
    }

    in.close();

    std::ofstream out(filePath, std::ios::trunc);
    out << buffer.str();
    out.close();
}

void FileManager::updateFriendships(const std::unordered_map<std::string, std::unordered_set<std::string>>& adjList) {
    save(adjList);
}