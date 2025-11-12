#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <functional>
#include <sstream>
#include <iomanip>

using namespace std;

// Generates a deterministic 6-character hexadecimal hash ID for a username.
string generateHashId(const string& username);

#endif
