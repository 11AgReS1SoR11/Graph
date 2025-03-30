#pragma once

#include <string>

enum class color_e : short
{
    NONE,
    RED,
    GREEN,
    BLUE,
    BLACK,
    WHITE,
    YELLOW,
    PURPLE
};

struct Style
{
    std::string toJson() const;

    color_e color = color_e::NONE;
    unsigned int border = 1;
    unsigned int textSize = 10;
};

std::string colorToString(color_e color);
