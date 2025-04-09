#pragma once

#include <string>

namespace backend
{

class Backend
{
public:
    void translate(std::string const& inputFilePath, std::string const& outputFilePath) noexcept;
    std::string retranslate(std::string const& filePath, std::string const& outputFilePath) noexcept;
};

} // namespace backend
