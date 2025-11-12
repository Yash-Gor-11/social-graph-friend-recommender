#include "utils.hpp"

string generateHashId(const string& username) {
    hash<string> hasher;
    size_t hashValue = hasher(username);

    stringstream ss;
    ss << hex << setw(6) << setfill('0') << (hashValue & 0xFFFFFF); // 24-bit short hash
    return ss.str();
}
