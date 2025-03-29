#include "Diamond.hpp"

std::string Diamond::toJson() const
{
    return "{"
           "\"type\": \"Diamond\","
           + Shape::toJson() + ","
           "\"property\": {"
               "\"sizeA\": " + std::to_string(sizeA) + ","
               "\"sizeB\": " + std::to_string(sizeB) + ","
               "\"angle\": " + std::to_string(angle) +
           "}"
           "}";
}
