#pragma once

#include "Style.hpp"

struct Shape
{
    virtual std::string toJson() const;

    std::string id{};
    std::string text{};
    Style style{};
    int x{};
    int y{};
};
