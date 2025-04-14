#pragma once
#include "Shape.hpp"

struct Note : Shape
{
    Note();
    std::string toJson() const override;

    int sizeA = 1;
    int sizeB = 1;
    std::string idTo = "";
};