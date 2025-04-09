#include "Rectangle.hpp"

std::string Rectangle::toJson() const
{
    return "{\n"
           "\t\"type\": \"Rectangle\","
           + Shape::toJson() + ",\n"
           "\t\"property\": {\n"
               "\t\t\"size_A\": " + std::to_string(sizeA) + ",\n"
               "\t\t\"size_B\": " + std::to_string(sizeB) +
           "\n\t}\n"
           "}";
}
