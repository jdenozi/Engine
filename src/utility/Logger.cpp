#include <regex>
#include "Logger.h"
#include <filesystem>

Logger::Logger(){
    std::filesystem::path exePath = std::filesystem::current_path() / "logs" / (getCurrentTimestamp() + "_application.log");
    logFile_.open(exePath, std::ios::app);
    if (!logFile_.is_open()) {
        std::cerr << "Failed to open log file at " << exePath << std::endl;
    }
}

Logger::~Logger() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

void Logger::log(LogLevel level, const std::string &message, const char *file, int line) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::string levelStr;
    switch (level) {
        case LogLevel::INFO:
            levelStr = "INFO";
            break;
        case LogLevel::DEBUG:
            levelStr = "DEBUG";
            break;
        case LogLevel::WARNING:
            levelStr = "WARNING";
            break;
        case LogLevel::ERROR:
            levelStr = "ERROR";
            break;
    }

    std::string timestamp = getCurrentTimestamp();
    std::string fullMessage;
    if(level != LogLevel::INFO){
        fullMessage = timestamp + " [" + levelStr + "] " + extractFilename(file) + ":" + std::to_string(line) + " " + message;
    }else{
        fullMessage = timestamp + " [" + levelStr + "] " + extractFilename(file) + ":" + message;

    }

    logFile_ << fullMessage << std::endl;
    logFile_.flush();

    std::cout << fullMessage << std::endl;
}

std::string Logger::extractFilename(const std::string &filepath) {
    static const std::regex filenameRegex(R"(([^/\\]+)$)");
    std::smatch match;
    if (std::regex_search(filepath, match, filenameRegex) && match.size() > 1) {
        return match.str(1);
    }
    return filepath;
}

std::string Logger::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}