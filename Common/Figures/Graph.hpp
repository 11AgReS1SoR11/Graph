#pragma once

#include "Shape.hpp"

#include <vector>

struct Graph : Shape
{
    std::string toJson() const override;

    std::vector<Shape*> nodes;
};
