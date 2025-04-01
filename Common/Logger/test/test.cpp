#include <catch2/catch_test_macros.hpp>

#include "Logger.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <ctime>

static std::vector<std::string> const LOGS = {"Info log", "Warn log", "Error log"};
static std::string const LOG_FORMAT_STR = "[%s][%s] %s"; // C-style format string

std::string readLastLogLine()
{
    std::ifstream file(LOG_FILE_PATH);
    std::string lastLine;
    std::string currentLine;
    if (file.is_open())
    {
        while (std::getline(file, currentLine))
        {
            lastLine = currentLine;
        }
        file.close();
    }
    return lastLine;
}

TEST_CASE("Logging to file", "[Logger]")
{
    std::ofstream outfile(LOG_FILE_PATH, std::ofstream::trunc); // Clear the file
    outfile.close();

    LOG_INFO(FILE_MANAGER_LOG, LOGS[0]);
    std::string const lastLogInfo = readLastLogLine();
    std::string const expectedStringInfo = "[INFO][" + std::string(FILE_MANAGER_LOG) + "] " + LOGS[0];
    REQUIRE(lastLogInfo.find(expectedStringInfo) != std::string::npos);

    LOG_WARN(BACKEND_LOG, LOGS[1]);
    std::string const lastLogWarn = readLastLogLine();
    std::string const expectedStringWarn = "[WARN][" + std::string(BACKEND_LOG) + "] " + LOGS[1];
    REQUIRE(lastLogWarn.find(expectedStringWarn) != std::string::npos);

    LOG_ERROR(TRANSLATOR_LOG, LOGS[2]);
    std::string const lastLogError = readLastLogLine();
    std::string const expectedStringError = "[ERROR][" + std::string(TRANSLATOR_LOG) + "] " + LOGS[2];
    REQUIRE(lastLogError.find(expectedStringError) != std::string::npos);

    std::remove(LOG_FILE_PATH); // Cleanup
}
