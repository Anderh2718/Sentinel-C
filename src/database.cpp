#include "database.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <iostream>

namespace fs = std::filesystem;
const std::string BASE_PATH = "sentinel-c-logs/";
const std::string DATA_PATH = BASE_PATH + "data/";
const std::string REPORT_PATH = BASE_PATH + "reports/";
const std::string BASELINE_FILE = DATA_PATH + ".sentinel-baseline";
const std::string LOG_FILE = DATA_PATH + ".sentinel.log";

namespace database {

// Create storage directories if missing
void init_storage() {
    fs::create_directories(DATA_PATH);
    fs::create_directories(REPORT_PATH);
}

// Save baseline to file
void save_baseline(const std::vector<FileEntry>& files) {
    std::ofstream out(BASELINE_FILE);
    for (const auto& f : files) {
        out << f.hash << "|" << f.size << "|" << f.path << "\n";
    }
}

// Load baseline from file
std::unordered_map<std::string, FileEntry> load_baseline() {
    std::unordered_map<std::string, FileEntry> baseline;
    std::ifstream in(BASELINE_FILE);
    if (!in) return baseline;

    std::string line;
    while (std::getline(in, line)) {
        auto p1 = line.find('|');
        auto p2 = line.find('|', p1 + 1);
        FileEntry f;
        f.hash = line.substr(0, p1);
        f.size = std::stoull(line.substr(p1 + 1, p2 - p1 - 1));
        f.path = line.substr(p2 + 1);
        baseline[f.path] = f;
    }
    return baseline;
}

// Log action to file
void log_action(const std::string& action, const std::string& filepath) {
    std::ofstream log(LOG_FILE, std::ios::app);
    if (!log) return;

    auto now = std::chrono::system_clock::now();
    auto t_c = std::chrono::system_clock::to_time_t(now);
    log << "[" << std::put_time(std::localtime(&t_c), "%F %T") << "] "
        << action << ": " << filepath << "\n";
}

// Generate HTML report
void generate_html_report(const std::vector<FileEntry>& new_files,
                          const std::vector<FileEntry>& modified_files,
                          const std::vector<FileEntry>& deleted_files) {
    auto now = std::chrono::system_clock::now();
    auto t_c = std::chrono::system_clock::to_time_t(now);

    std::ostringstream filename;
    filename << REPORT_PATH << "sentinel_report_"
             << std::put_time(std::localtime(&t_c), "%Y%m%d_%H%M%S")
             << ".html";

    std::ofstream html(filename.str());
    if (!html) return;

    html << "<!DOCTYPE html><html><head><meta charset='utf-8'><title>Sentinel-C Report</title>";
    html << "<style>body{font-family:Arial;}table{border-collapse:collapse;width:100%;}"
         << "th,td{border:1px solid #ccc;padding:8px;text-align:left;}"
         << ".NEW{background-color:#d4edda;}"
         << ".MODIFIED{background-color:#fff3cd;}"
         << ".DELETED{background-color:#f8d7da;}"
         << "</style></head><body>";
    html << "<h2>Sentinel-C Scan Report</h2>";
    html << "<p>Generated: " << std::put_time(std::localtime(&t_c), "%F %T") << "</p>";
    html << "<table><tr><th>File</th><th>Status</th><th>Size (bytes)</th><th>SHA-256</th></tr>";

    for (const auto& f : new_files)
        html << "<tr class='NEW'><td>" << f.path << "</td><td>NEW</td><td>"
             << f.size << "</td><td>" << f.hash << "</td></tr>";

    for (const auto& f : modified_files)
        html << "<tr class='MODIFIED'><td>" << f.path << "</td><td>MODIFIED</td><td>"
             << f.size << "</td><td>" << f.hash << "</td></tr>";

    for (const auto& f : deleted_files)
        html << "<tr class='DELETED'><td>" << f.path << "</td><td>DELETED</td><td>"
             << f.size << "</td><td>" << f.hash << "</td></tr>";

    html << "</table></body></html>";
    std::cout << "[+] HTML report generated: " << filename.str() << "\n";
}

} // namespace database
