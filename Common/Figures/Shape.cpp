#include "Shape.hpp"

std::string Shape::toJson() const
{
    return  "\n\t\"id\": \"" + id + "\",\n"
            "\t\"text\": \"" + text + "\",\n"
            "\t\"position\": {\n"
                "\t\t\"x\": " + std::to_string(x) + ",\n"
                "\t\t\"y\": " + std::to_string(y) +
            "\n\t},"
            + style.toJson();
}
