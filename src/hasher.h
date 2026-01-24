#pragma once
#include <string>

// Returns SHA-256 hash of the given file path
std::string sha256_file(const std::string& filepath);
