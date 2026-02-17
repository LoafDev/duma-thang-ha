#pragma once

#include <iostream>

#define LOG_INFO(module, msg) \
    std::cout << "[INFO][" << module << "]" << msg << "\n"

#define LOG_WARN(module, msg) \
    std::cout << "[WARN][" << module << "]" << msg << "\n"

#define LOG_ERROR(module, msg) \
    std::cerr << "[ERROR][" << module << "]" << msg << "\n"