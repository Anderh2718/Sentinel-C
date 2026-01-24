#include "security.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace security {

// Check if baseline exists and is not empty
bool baseline_integrity_ok() {
    const std::string baseline_file = "sentinel-c-logs/data/.sentinel-baseline";
    if (!fs::exists(baseline_file)) return false;

    std::ifstream in(baseline_file);
    return in.peek() != std::ifstream::traits_type::eof();
}

}
