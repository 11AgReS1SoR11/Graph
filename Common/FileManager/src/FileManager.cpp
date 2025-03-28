#include "FileManager.hpp"
#include "Logger.hpp"

bool FileManager::writeToFile(const std::string& filePath, const std::string& data)
{
    std::ofstream outFile(filePath);
    if (!outFile)
    {
        std::string const errorMsg = "Filed to open file for write: " + filePath;
        LOG_ERROR(FILE_MANAGER_LOG, errorMsg);
        return false;
    }

    outFile << data;
    outFile.close();
    return true;
}

std::optional<std::string> FileManager::readFromFile(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile)
    {
        std::string const errorMsg = "Filed to open file for read: " + filePath;
        LOG_ERROR(FILE_MANAGER_LOG, errorMsg);
        return {};
    }

    std::string const data((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();
    return data;
}
