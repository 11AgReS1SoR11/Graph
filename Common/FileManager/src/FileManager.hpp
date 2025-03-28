#pragma once

#include <string>
#include <optional>

class FileManager
{
public:

    static bool writeToFile(const std::string& filePath, const std::string& data);
    static std::optional<std::string> readFromFile(const std::string& filePath);
};
