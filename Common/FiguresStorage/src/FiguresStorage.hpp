#pragma once

#include "Shape.hpp"
#include <vector>

class FiguresStorage : public std::vector<Shape*>
{
public:
    FiguresStorage() = default;
    ~FiguresStorage();

    static FiguresStorage createFigures(std::string const& figuresJson);
    static std::string toJson(std::vector<Shape*> const& figures);
};

