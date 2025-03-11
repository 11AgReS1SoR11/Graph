#pragma once

#include "Shape.hpp"

struct Diamond : Shape
{
    void draw() const override;

    double sizeA = 1;
    double sizeB = 1;
    double angle = 90;
};
