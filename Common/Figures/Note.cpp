#include "Note.hpp"

static size_t nextId = 1;

Note::Note()
{
    id = "note_" + std::to_string(nextId++);
}

std::string Note::toJson() const
{
    return  "{\n"
            "\t\"type\": \"Note\","
            + Shape::toJson() + ",\n"
            "\t\"property\": {\n"
                "\t\t\"size_A\": " + std::to_string(sizeA) + ",\n"
                "\t\t\"size_B\": " + std::to_string(sizeB) + ",\n"
                "\t\t\"idTo\": \"" + idTo + "\""
            "\n\t}\n"
            "}";
}
