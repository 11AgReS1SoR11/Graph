#include "Circle.hpp"

std::string Circle::toJson() const
{
    return "{\n"
           "\t\"type\": \"Circle\","
           + Shape::toJson() + ",\n"
           "\t\"property\": {\n"
               "\t\t\"radius\": " + std::to_string(radius) +
           "\n\t}\n"
           "}";
}
