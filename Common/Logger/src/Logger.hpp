#pragma once

#include <fstream>
#include <string>
#include <mutex>

#define LOG_INFO(entity, message) Logger::getInstance().log(Logger::Level::INFO, entity, message);
#define LOG_WARN(entity, message) Logger::getInstance().log(Logger::Level::WARN, entity, message);
#define LOG_ERROR(entity, message) Logger::getInstance().log(Logger::Level::ERROR, entity, message);

inline constexpr auto BACKEND_LOG = "BACKEND";
inline constexpr auto TRANSLATOR_LOG = "TRANSLATOR";
inline constexpr auto RETRANSLATOR_LOG = "RETRANSLATOR";
inline constexpr auto PARSER_LOG = "PARSER";
inline constexpr auto SEMANTIC_ANALYZER_LOG = "SEMANTIC_ANALYZER";
inline constexpr auto FILE_MANAGER_LOG = "FILE_MANAGER";
inline constexpr auto FIGURES_STORAGE_LOG = "FIGURES_STORAGE";

class Logger
{
public:
    enum class Level { INFO, WARN, ERROR };

    static Logger& getInstance();

    void log(Level level, std::string const& entity, std::string const& message);

    void updLogOutput(std::string const& filePath);

private:
    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string m_logFilePath;
    std::ofstream m_logFile;
    std::mutex m_mutex;
};
