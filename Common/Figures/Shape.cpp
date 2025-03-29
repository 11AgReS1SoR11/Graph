#include "Shape.hpp"

std::string Shape::toJson() const
{
    return  "\"id\": \"" + id + "\","
            "\"text\": \"" + text + "\","
            "\"position\": {"
                "\"x\": " + std::to_string(x) + ","
                "\"y\": " + std::to_string(y) +
            "},"
            + style.toJson();
}
