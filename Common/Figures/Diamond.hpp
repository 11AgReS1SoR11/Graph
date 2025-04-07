#pragma once

#include "Shape.hpp"

struct Diamond : Shape
{
    std::string toJson() const override;

    int sizeA = 1;
    int sizeB = 1;
    int angle = 90;
};
