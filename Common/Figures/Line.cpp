#include "Line.hpp"

namespace detail
{

std::string lineTypeToString(line_type_e type)
{
    switch (type)
    {
        case line_type_e::Dotted: return "Dotted";
        case line_type_e::Solid: return "Solid";
    }

    return {};
}

std::string lineOrientationToString(line_orientation_e orientation)
{
    switch (orientation)
    {
        case line_orientation_e::Undirected: return "Undirected";
        case line_orientation_e::Directed: return "Directed";
        case line_orientation_e::DoubleDirected: return "DoubleDirected";
    }

    return {};
}

} // namespace detail

std::string Line::toJson() const
{
    return "{\n"
           "\t\"type\": \"Line\",\n"
           "\t\"text\": \"" + text + "\","
           + style.toJson() + ",\n"
           "\t\"property\": {\n"
               "\t\t\"idFrom\": \"" + idFrom + "\",\n"
               "\t\t\"idTo\": \"" + idTo + "\",\n"
               "\t\t\"type\": \"" + detail::lineTypeToString(type) + "\",\n"
               "\t\t\"orientation\": \"" + detail::lineOrientationToString(orientation) + "\"\n"
           "\n\t}\n"
           "}";
}

line_type_e line_helper::stringToLineType(const std::string& str)
{
    if (str == "Dotted")
        return line_type_e::Dotted;

    return line_type_e::Solid;
}

line_orientation_e line_helper::stringToLineOrientation(const std::string& str)
{
    if (str == "Undirected")
        return line_orientation_e::Undirected;

    else if (str == "Directed")
        return line_orientation_e::Directed;

    return line_orientation_e::DoubleDirected;
}
