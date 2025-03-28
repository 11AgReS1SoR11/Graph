#include "Reactangle.hpp"

std::string Reactangle::toJson() const
{
    return "{"
           "\"type\": \"Reactangle\","
           + Shape::toJson() + ","
           "\"property\": {"
               "\"sizeA\": " + std::to_string(sizeA) + ","
               "\"sizeB\": " + std::to_string(sizeB) +
           "}"
           "}";
}
