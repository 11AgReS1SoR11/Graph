#pragma once

#include "Shape.hpp"

struct Reactangle : Shape
{
    std::string toJson() const override;

    double sizeA = 1;
    double sizeB = 1;
};
