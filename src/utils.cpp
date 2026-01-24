#include "utils.h"
#include <iostream>

void print_error(const std::string& msg) {
    std::cout << "\033[31m[-] " << msg << "\033[0m\n";
}

void print_success(const std::string& msg) {
    std::cout << "\033[32m[+] " << msg << "\033[0m\n";
}

void print_warning(const std::string& msg) {
    std::cout << "\033[33m[!] " << msg << "\033[0m\n";
}
