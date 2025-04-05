#pragma once
#include "Shape.hpp"

struct Note : Shape
{
    std::string toJson() const override;

    double sizeA = 1;
    double sizeB = 1;
    std::string idTo{};
};