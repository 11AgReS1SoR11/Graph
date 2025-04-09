#include "Note.hpp"
std::string Note::toJson() const
{
    return "{\n"
            "\t\"type\": \"Note\","
            + Shape::toJson() + ",\n"
            "\t\"property\": {\n"
                "\t\t\"size_A\": " + std::to_string(sizeA) + ",\n"
                "\t\t\"size_B\": " + std::to_string(sizeB) + ",\n"
                "\t\t\"idTo\": \"" + idTo + "\""
            "\n\t}\n"
            "}";
}