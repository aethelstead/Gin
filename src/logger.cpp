#include <iostream>
#include "logger.h"

using namespace Gin;

Logger::LogLevel Logger::logLevel = Logger::LogLevel::Info;

void Logger::log_error(const char* message)
{
    if (Logger::logLevel >= Logger::LogLevel::Error)
    {
        std::cout << "[ERROR] - " << message << "\n";
    }
}
void Logger::log_warn(const char* message)
{
    if (Logger::logLevel >= Logger::LogLevel::Warn)
    {
        std::cout << "[WARN] - " << message << "\n";
    }
}
void Logger::log_info(const char* message)
{
    if (Logger::logLevel >= Logger::LogLevel::Info)
    {
        std::cout << "[INFO] - " << message << "\n";
    }
}
