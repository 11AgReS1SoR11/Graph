#pragma once

#include "Style.hpp"

#include <string>

struct Shape
{
    virtual void draw() const = 0;

    std::string text{};
    Style style{};
    int x{};
    int y{};
};
