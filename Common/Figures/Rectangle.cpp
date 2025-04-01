#include "Rectangle.hpp"

std::string Rectangle::toJson() const
{
    return "{"
           "\"type\": \"Rectangle\","
           + Shape::toJson() + ","
           "\"property\": {"
               "\"size_A\": " + std::to_string(sizeA) + ","
               "\"size_B\": " + std::to_string(sizeB) +
           "}"
           "}";
}
