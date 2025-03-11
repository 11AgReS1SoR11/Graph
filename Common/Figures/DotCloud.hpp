#pragma once

#include "Circle.hpp"

#include <vector>

struct DotCloud : Shape
{
    void draw() const override;

    std::vector<Circle*> dots;
};
