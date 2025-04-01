#pragma once

#include <string>

namespace backend
{

class Backend
{
public:
    void translate(std::string const& code);
    std::string retranslate(std::string const& filePath);
};

} // namespace backend
