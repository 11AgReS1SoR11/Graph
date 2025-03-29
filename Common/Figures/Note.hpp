#pragma once
#include "Shape.hpp"

struct Note : Shape
{
    std::string toJson() const override;

    
};