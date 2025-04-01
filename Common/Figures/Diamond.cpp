#include "Diamond.hpp"

std::string Diamond::toJson() const
{
    return "{"
           "\"type\": \"Diamond\","
           + Shape::toJson() + ","
           "\"property\": {"
               "\"size_A\": " + std::to_string(sizeA) + ","
               "\"size_B\": " + std::to_string(sizeB) + ","
               "\"angle\": " + std::to_string(angle) +
           "}"
           "}";
}
