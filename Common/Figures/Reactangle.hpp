#pragma once

#include "Shape.hpp"

struct Reactangle : Shape
{
    void draw() const override;

    double sizeA = 1;
    double sizeB = 1;
};
