#pragma once
#include "scanner.h"
#include <vector>
#include <string>
#include <unordered_map>

namespace database {

// Initialize storage folders (logs & reports)
void init_storage();

// Save baseline to disk
void save_baseline(const std::vector<FileEntry>& files);

// Load baseline from disk
std::unordered_map<std::string, FileEntry> load_baseline();

// Log a single action (NEW / MODIFIED / DELETED)
void log_action(const std::string& action, const std::string& filepath);

// Generate HTML report from changes
void generate_html_report(const std::vector<FileEntry>& new_files,
                          const std::vector<FileEntry>& modified_files,
                          const std::vector<FileEntry>& deleted_files);

}
