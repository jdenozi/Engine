#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <mutex>

class Logger {
public:
    enum class LogLevel {
        INFO, DEBUG, WARNING, ERROR
    };

    static Logger &getInstance() {
        static Logger instance;
        return instance;
    }

    void log(LogLevel level, const std::string &message, const char *file, int line);

    Logger(const Logger &) = delete;

    Logger &operator=(const Logger &) = delete;

private:

    Logger();

    ~Logger();

    static std::string getCurrentTimestamp();

    static std::string extractFilename(const std::string &filepath);

    std::ofstream logFile_;
    std::mutex mutex_;
};

static Logger &AppLogger = Logger::getInstance();

#define LOG_INFO(message) AppLogger.log(Logger::LogLevel::DEBUG, message, __FILE__,  __LINE__)
#define LOG_DEBUG(message) AppLogger.log(Logger::LogLevel::DEBUG, message, __FILE__, __LINE__)
#define LOG_WARNING(message) AppLogger.log(Logger::LogLevel::WARNING, message, __FILE__, __LINE__)
#define LOG_ERROR(message) AppLogger.log(Logger::LogLevel::ERROR, message, __FILE__, __LINE__)