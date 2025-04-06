#include "Note.hpp"
std::string Note::toJson() const
{
    return "{"
    "\"type\": \"Note\","
    + Shape::toJson() + ","
    "\"property\": {"
        "\"size_A\": " + std::to_string(sizeA) + ","
        "\"size_B\": " + std::to_string(sizeB) + ","
        "\"idTo\": \"" + idTo + "\""
    "}"
    "}";
}