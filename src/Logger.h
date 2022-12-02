#ifndef LOGGER_H
#define LOGGER_H

typedef enum
{
    None = 0,
    Error,
    Warn,
    Info
} LogLevel;

struct Logger
{
    static LogLevel logLevel;

    static void log_error(const char* message);
    static void log_warn(const char* message);
    static void log_info(const char* message);
};

#endif