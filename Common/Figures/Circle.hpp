#pragma once

#include "Shape.hpp"

struct Circle : Shape
{
    void draw() const override;

    double radius = 1;
};
