#include "Style.hpp"
#include <map>




color_e style_helper::stringToColor(const std::string str)
{

    std::map<const std::string, int> mapping;

    mapping["red"] = 1;
    mapping["green"] = 2;
    mapping["blue"] = 3;
    mapping["black"] = 4;
    mapping["white"] = 5;
    mapping["yellow"] = 6;
    mapping["purple"] = 7;
    mapping["none"] = 0;
    
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
        case color_e::RED: return "red";
        case color_e::GREEN: return "green";
        case color_e::BLUE: return "blud";
        case color_e::BLACK: return "black";
        case color_e::WHITE: return "white";
        case color_e::YELLOW: return "yellow";
        case color_e::PURPLE: return "purple";
        case color_e::NONE: return "none";
    }

    return {};
}


std::string Style::toJson() const
{
    return  "\n\t\"style\": {\n"
            "\t\t\"color\": \"" + style_helper::colorToString(color) + "\",\n"
            "\t\t\"border\": " + std::to_string(border) + ",\n"
            "\t\t\"textSize\": " + std::to_string(textSize) +
            "\n\t}";
}
