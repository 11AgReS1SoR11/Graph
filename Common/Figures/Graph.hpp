#pragma once

#include "Shape.hpp"

#include <vector>

struct Graph : Shape
{
    void draw() const override;

    std::vector<Shape*> nodes;
};
