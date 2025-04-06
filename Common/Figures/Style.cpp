#include "Style.hpp"
#include <map>




color_e style_helper::stringToColor(const std::string str)
{

    std::map<const std::string, int> mapping;

    mapping["RED"] = 1;
    mapping["GREEN"] = 2;
    mapping["BLUE"] = 3;
    mapping["BLACK"] = 4;
    mapping["WHITE"] = 5;
    mapping["YELLOW"] = 6;
    mapping["PURPLE"] = 7;
    mapping["NONE"] = 0;
    
    switch (mapping[str])
    {
        case 1: return color_e::RED; break;
        case 2: return color_e::GREEN; break; 
        case 3: return color_e::BLUE; break;
        case 4: return color_e::BLACK; break;
        case 5: return color_e::WHITE; break;
        case 6: return color_e::YELLOW; break;
        case 7: return color_e::PURPLE; break;
    }
    return color_e::NONE;
}

std::string style_helper::colorToString(color_e color)
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
            "\"color\": \"" + style_helper::colorToString(color) + "\","
            "\"border\": " + std::to_string(border) + ","
            "\"textSize\": " + std::to_string(textSize) +
            "}";
}
