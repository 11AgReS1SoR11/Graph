#pragma once

#include "Shape.hpp"

struct Rectangle : Shape
{
    std::string toJson() const override;

    int sizeA = 1;
    int sizeB = 1;
};
