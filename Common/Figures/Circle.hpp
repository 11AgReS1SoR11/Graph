#pragma once

#include "Shape.hpp"

struct Circle : Shape
{
    std::string toJson() const override;

    int radius = 1;
};
