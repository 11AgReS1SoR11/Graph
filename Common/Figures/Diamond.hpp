#pragma once

#include "Shape.hpp"

struct Diamond : Shape
{
    std::string toJson() const override;

    double sizeA = 1;
    double sizeB = 1;
    double angle = 90;
};
