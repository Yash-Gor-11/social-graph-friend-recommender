// File handling header
#pragma once
#include <string>
#include <vector>

class FileManager {
public:
    static std::vector<std::vector<std::string>> readCSV(const std::string& path);
    static void writeCSV(const std::string& path, const std::vector<std::vector<std::string>>& data);
};
