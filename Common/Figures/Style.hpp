#pragma once

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
    color_e color = color_e::NONE;
    unsigned int border = 1;
    unsigned int textSize = 10;
};
