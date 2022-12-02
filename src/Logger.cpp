#include <iostream>
#include "Logger.h"

// Set the Logger to the highest LogLevel by default.
LogLevel Logger::logLevel = LogLevel::Info;

void Logger::log_error(const char* message)
{
    if (logLevel >= LogLevel::Error)
    {
        std::cout << "[ERROR] - " << message << "\n";
    }
}

void Logger::log_warn(const char* message)
{
    if (logLevel >= LogLevel::Error)
    {
        std::cout << "[WARN] - " << message << "\n";
    }
}

void Logger::log_info(const char* message)
{
    if (logLevel >= LogLevel::Error)
    {
        std::cout << "[INFO] - " << message << "\n";
    }
}
