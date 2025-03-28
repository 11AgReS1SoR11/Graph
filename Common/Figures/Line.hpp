#pragma once

#include "Shape.hpp"

enum class line_type_e : short
{
    Dotted,
    Solid
};

enum class line_orientation_e : short
{
    Undirected,
    Directed,
    DoubleDirected
};

struct Line : Shape
{
    std::string toJson() const override;

    std::string idFrom;
    std::string idTo;
    line_type_e type = line_type_e::Solid;
    line_orientation_e orientation = line_orientation_e::Undirected;
};
