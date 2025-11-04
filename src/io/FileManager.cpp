#include "FileManager.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

using namespace std;

FileManager::FileManager(const string& path) {
    filesystem::path base = filesystem::current_path();
    if (base.filename() == "build" || base.filename() == "Build")
        base = base.parent_path();

    filesystem::path p(path);
    filePath = p.is_relative() ? (base / p).lexically_normal().string() : p.lexically_normal().string();
    filesystem::create_directories(filesystem::path(filePath).parent_path());
}

vector<string> FileManager::split(const string& s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delimiter)) {
        if (!item.empty()) tokens.push_back(item);
    }
    return tokens;
}

string FileManager::join(const vector<string>& items, char delimiter) {
    string result;
    for (size_t i = 0; i < items.size(); ++i) {
        result += items[i];
        if (i + 1 < items.size()) result.push_back(delimiter);
    }
    return result;
}

// ============ LOAD ============

void FileManager::loadWithHashes(unordered_map<string, unordered_set<string>>& adjList,
                                 unordered_map<string, string>& idToUser,
                                 unordered_map<string, string>& userToId) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "users.csv not found at " << filePath << ", starting fresh.\n";
        return;
    }

    // Two-pass load: first read all entries to build id<->username maps, then
    // resolve friend IDs to usernames. This ensures friend IDs referencing
    // later lines are handled correctly.
    struct Entry { string id; string username; string friendsField; };
    vector<Entry> entries;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, username, friendsField;
        getline(ss, id, ',');
        getline(ss, username, ',');
        // read the rest as friendsField (may be empty)
        getline(ss, friendsField);

        // Trim possible Windows CR
        if (!id.empty() && id.back() == '\r') id.pop_back();
        if (!username.empty() && username.back() == '\r') username.pop_back();
        if (!friendsField.empty() && friendsField.back() == '\r') friendsField.pop_back();

        entries.push_back({id, username, friendsField});
    }

    // First pass: populate id<->username maps and ensure an entry exists in adjList
    for (const auto &e : entries) {
        if (e.id.empty() || e.username.empty()) continue;
        idToUser[e.id] = e.username;
        userToId[e.username] = e.id;
        // create empty friend set (will be filled in second pass)
        adjList[e.username];
    }

    // Second pass: resolve friend ID lists into usernames
    for (const auto &e : entries) {
        if (e.username.empty()) continue;
        unordered_set<string> friendNames;
        if (!e.friendsField.empty()) {
            for (auto fid : split(e.friendsField, '|')) {
                if (fid.empty()) continue;
                if (!fid.empty() && fid.back() == '\r') fid.pop_back();
                if (idToUser.count(fid))
                    friendNames.insert(idToUser[fid]);
            }
        }
        adjList[e.username] = friendNames;
    }

    file.close();
    cout << "Loaded users (with hash IDs) from " << filePath << "\n";
}

// ============ SAVE ============

void FileManager::saveWithHashes(const unordered_map<string, unordered_set<string>>& adjList,
                                 const unordered_map<string, string>& idToUser,
                                 const unordered_map<string, string>& userToId) {
    ofstream file(filePath, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error opening " << filePath << " for writing.\n";
        return;
    }

    for (auto& [id, username] : idToUser) {
        const auto& friends = adjList.at(username);
        vector<string> friendIds;
        for (auto& f : friends)
            if (userToId.count(f)) friendIds.push_back(userToId.at(f));

        file << id << "," << username << "," << join(friendIds, '|') << "\n";
    }

    file.close();
    cout << "Saved users with hash IDs to " << filePath << "\n";
}

// ============ ADD/REMOVE USERS ============

void FileManager::addUser(const string& id, const string& username) {
    ofstream file(filePath, ios::app);
    if (!file.is_open()) return;
    file << id << "," << username << ",\n";
    file.close();
}

void FileManager::removeUser(const string& id) {
    ifstream in(filePath);
    if (!in.is_open()) return;

    stringstream buffer;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string currentId;
        getline(ss, currentId, ',');
        if (currentId == id) continue;
        buffer << line << "\n";
    }

    in.close();
    ofstream out(filePath, ios::trunc);
    out << buffer.str();
    out.close();
}

// ============ UPDATE FRIENDSHIPS ============

void FileManager::updateFriendships(const unordered_map<string, unordered_set<string>>& adjList,
                                    const unordered_map<string, string>& userToId) {
    unordered_map<string, string> idToUser;
    for (auto& [u, id] : userToId)
        idToUser[id] = u;

    saveWithHashes(adjList, idToUser, userToId);
}
