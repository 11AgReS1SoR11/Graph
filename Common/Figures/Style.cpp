#include "Style.hpp"


std::string colorToString(color_e color)
{
    switch (color)
    {
        case color_e::RED: return "RED";
        case color_e::GREEN: return "GREEN";
        case color_e::BLUE: return "BLUE";
        case color_e::BLACK: return "BLACK";
        case color_e::WHITE: return "WHITE";
        case color_e::YELLOW: return "YELLOW";
        case color_e::PURPLE: return "PURPLE";
        case color_e::NONE: return "NONE";
    }

    return {};
}


std::string Style::toJson() const
{
    return  "\"style\": {"
            "\"color\": \"" + colorToString(color) + "\","
            "\"border\": " + std::to_string(border) + ","
            "\"textSize\": " + std::to_string(textSize) +
            "}";
}
