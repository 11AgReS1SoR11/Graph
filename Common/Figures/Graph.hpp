#pragma once

#include "Shape.hpp"

#include <vector>

struct Graph : Shape
{
    std::string toJson() const override;

    std::vector<std::pair<std::string const,Shape*>> nodes;
};
