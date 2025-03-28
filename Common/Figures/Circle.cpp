#include "Circle.hpp"

std::string Circle::toJson() const
{
    return "{"
           "\"type\": \"Circle\","
           + Shape::toJson() + ","
           "\"property\": {"
               "\"radius\": " + std::to_string(radius) +
           "}"
           "}";
}
