#pragma once

#include "Circle.hpp"

#include <vector>

struct DotCloud : Shape
{
    std::string toJson() const override;

    bool grid = false;
    std::vector<Circle*> dots;
};
