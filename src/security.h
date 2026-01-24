// security.h
#pragma once
namespace security {
    bool baseline_integrity_ok();
}

// security.cpp
#include "security.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace security {
bool baseline_integrity_ok() {
    return fs::exists("sentinel-c-logs/data/baseline.db") &&
           fs::file_size("sentinel-c-logs/data/baseline.db") > 0;
}
}
