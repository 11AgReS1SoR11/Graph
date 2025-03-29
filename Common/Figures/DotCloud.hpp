#pragma once

#include "Circle.hpp"

#include <vector>

struct DotCloud : Shape
{
    std::string toJson() const override;

    std::vector<Circle*> dots;
    bool grid = false;
};
