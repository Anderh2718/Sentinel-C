#include "scanner.h"
#include "hasher.h"
#include "database.h"
#include "security.h"
#include <filesystem>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>
#include <unordered_map>

namespace fs = std::filesystem;

// Default excluded folders
const std::vector<std::string> EXCLUDE = {".git", "build"};

// ANSI colors
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

// Helper: check if path is excluded
static bool is_excluded(const fs::path& p) {
    for (const auto& ex : EXCLUDE)
        if (p.string().find(ex) != std::string::npos) return true;
    if (fs::is_symlink(p)) return true;
    return false;
}

// Scan directory and return file entries
static std::vector<FileEntry> scan_directory(const std::string& root) {
    std::vector<FileEntry> files;
    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file() || is_excluded(entry.path())) continue;
        FileEntry fe;
        fe.path = entry.path().string();
        fe.size = entry.file_size();
        fe.hash = sha256_file(fe.path);
        files.push_back(fe);
    }
    return files;
}

// Initialize baseline
void initialize_baseline(const std::string& root) {
    auto files = scan_directory(root);
    database::init_storage();
    database::save_baseline(files);
    std::cout << GREEN << "[+] Baseline created with " << files.size() << " files\n" << RESET;
}

// Scan and compare directory
void scan_and_compare(const std::string& root) {
    if (!security::baseline_integrity_ok()) {
        std::cerr << RED << "[-] No valid baseline found. Run --init first.\n" << RESET;
        return;
    }

    auto baseline = database::load_baseline();
    auto current = scan_directory(root);

    std::unordered_map<std::string, FileEntry> now;
    for (const auto& f : current) now[f.path] = f;

    std::vector<FileEntry> new_files, modified_files, deleted_files;

    // Check for new or modified
    for (const auto& [path,f] : now) {
        if (!baseline.count(path)) {
            std::cout << GREEN << "[+] NEW: " << path << RESET << "\n";
            new_files.push_back(f);
            database::log_action("NEW", path);
        } else if (baseline[path].hash != f.hash) {
            std::cout << YELLOW << "[!] MODIFIED: " << path << RESET << "\n";
            modified_files.push_back(f);
            database::log_action("MODIFIED", path);
        }
    }

    // Check for deleted
    for (const auto& [path,f] : baseline) {
        if (!now.count(path)) {
            std::cout << RED << "[-] DELETED: " << path << RESET << "\n";
            deleted_files.push_back(f);
            database::log_action("DELETED", path);
        }
    }

    // Generate HTML report if changes exist
    if (!new_files.empty() || !modified_files.empty() || !deleted_files.empty()) {
        database::generate_html_report(new_files, modified_files, deleted_files);
    }
}

// Monitor directory continuously
void monitor_directory(const std::string& root, unsigned int interval_seconds) {
    std::cout << "[+] Monitoring " << root << " every " << interval_seconds << " seconds. Ctrl+C to stop.\n";
    while (true) {
        scan_and_compare(root);
        std::this_thread::sleep_for(std::chrono::seconds(interval_seconds));
    }
}

// Verify a single file against baseline
void verify_file(const std::string& filepath) {
    if (!security::baseline_integrity_ok()) {
        std::cerr << RED << "[-] No valid baseline found. Run --init first.\n" << RESET;
        return;
    }

    auto baseline = database::load_baseline();
    if (!baseline.count(filepath)) {
        std::cout << YELLOW << "[!] File not in baseline: " << filepath << RESET << "\n";
        return;
    }

    std::string hash = sha256_file(filepath);
    if (hash == baseline[filepath].hash) {
        std::cout << GREEN << "[+] File verified: " << filepath << RESET << "\n";
    } else {
        std::cout << RED << "[!] File modified: " << filepath << RESET << "\n";
    }
}
