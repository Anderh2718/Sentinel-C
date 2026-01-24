#include "cli.h"
#include "banner.h"
#include "scanner.h"
#include "security.h"
#include <iostream>
#include <string>

namespace cli {

void parse(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Use --help or -h to see available commands.\n";
        return;
    }

    std::string cmd = argv[1];
    std::string target = (argc > 2) ? argv[2] : ".";

    if (cmd == "--help" || cmd == "-h") {
        std::cout << "\nSentinel-C v2.5 Help\n"
                  << "Usage:\n"
                  << "  --help, -h          Show this help menu\n"
                  << "  --version, -v       Show version\n"
                  << "  --banner            Show banner\n"
                  << "  --about             About this tool\n"
                  << "  --init, -i <path>   Initialize baseline\n"
                  << "  --scan, -s <path>   Scan directory and compare\n"
                  << "  --monitor, -m <path> [interval_sec]   Continuous monitoring\n"
                  << "  --verify, -f <file> Verify a single file\n"
                  << "  --doctor, -d        Check baseline integrity\n\n"
                  << "Examples:\n"
                  << "  sentinel-c --init ./myfolder\n"
                  << "  sentinel-c --scan ./myfolder\n"
                  << "  sentinel-c --monitor ./myfolder 10\n"
                  << "  sentinel-c --verify ./myfolder/file.txt\n";
    }
    else if (cmd == "--version" || cmd == "-v") {
        std::cout << "Sentinel-C version v2.5\n";
    }
    else if (cmd == "--banner") {
        show_banner();
    }
    else if (cmd == "--about") {
        std::cout << "Sentinel-C v2.5 — Advanced Host Defense Multi-Tool\n"
                  << "Developed by Voltsparx\n"
                  << "Contact: voltsparx@gmail.com\n"
                  << "Purpose: File integrity monitoring, logging, and reporting.\n";
    }
    else if (cmd == "--init" || cmd == "-i") {
        initialize_baseline(target);
    }
    else if (cmd == "--scan" || cmd == "-s") {
        scan_and_compare(target);
    }
    else if (cmd == "--monitor" || cmd == "-m") {
        unsigned int interval = (argc > 3) ? std::stoi(argv[3]) : 5;
        monitor_directory(target, interval);
    }
    else if (cmd == "--verify" || cmd == "-f") {
        verify_file(target);
    }
    else if (cmd == "--doctor" || cmd == "-d") {
        if (security::baseline_integrity_ok())
            std::cout << "Baseline is valid.\n";
        else
            std::cout << "Baseline is missing or corrupted.\n";
    }
    else {
        std::cout << "Unknown command. Use --help or -h for usage.\n";
    }
}

}
