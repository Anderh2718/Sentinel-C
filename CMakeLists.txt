cmake_minimum_required(VERSION 3.10)
project(SentinelC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect OS
if(WIN32)
    message(STATUS "Building for Windows")
elseif(UNIX)
    message(STATUS "Building for Linux/Unix")
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/cli.cpp
    src/banner.cpp
    src/scanner.cpp
    src/database.cpp
    src/security.cpp
    src/hasher.cpp
)

# Create executable
add_executable(sentinel-c ${SOURCES})

# Windows specific: enable console subsystem for CLI tools
if(WIN32)
    set_target_properties(sentinel-c PROPERTIES WIN32_EXECUTABLE FALSE)
endif()
