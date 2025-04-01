#include "Logger.hpp"

#include <iostream>
#include <memory>
#include <ctime>

#include <cassert>

namespace details
{

std::string levelToString(Logger::Level level)
{
    switch (level)
    {
        case Logger::Level::INFO: return "INFO";
        case Logger::Level::WARN: return "WARN";
        case Logger::Level::ERROR: return "ERROR";
    }

    return {};
}

std::string getCurrentTime()
{
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf;
}

} // namespace details

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log(Level level, std::string const& entity, std::string const& message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    
    auto const levelStr = details::levelToString(level);
    auto const timeStr = details::getCurrentTime();
    auto const logMessage = "[" + timeStr + "][" + levelStr + "][" + entity + "] " + message;

    std::cout << logMessage << std::endl;

    if (m_logFile.is_open())
    {
        m_logFile << logMessage << std::endl;
    }
}

void Logger::log(Level level, const char* entity, const char* message)
{
    log(level, std::string(entity), std::string(message));
}

void Logger::log(Level level, QString const& entity, QString const& message)
{
    log(level, entity.toStdString(), message.toStdString());
}

Logger::Logger()
{
    m_logFile.open(LOG_FILE_PATH, std::ios::app);
    if (!m_logFile)
    {
        std::cerr << "Failed to open log file" << std::endl;
    }
}

Logger::~Logger()
{
    if (m_logFile.is_open())
    {
        m_logFile.close();
    }
}
