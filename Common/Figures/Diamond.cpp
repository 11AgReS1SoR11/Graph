#include "Diamond.hpp"

std::string Diamond::toJson() const
{
    return "{\n"
           "\t\"type\": \"Diamond\","
           + Shape::toJson() + ",\n"
           "\t\"property\": {\n"
               "\t\t\"size_A\": " + std::to_string(sizeA) + ",\n"
               "\t\t\"size_B\": " + std::to_string(sizeB) + ",\n"
               "\t\t\"angle\": " + std::to_string(angle) +
           "\n\t}\n"
           "}";
}
