#include "FiguresStorage.hpp"

#include "Figures.hpp"
#include "Logger.hpp"

#include <stdexcept>
#include <algorithm>
#include <iostream>

using json = nlohmann::json;

FiguresStorage::~FiguresStorage()
{
    for (auto* shape : *this)
    {
        // TODO: figure out during GRAP-49
        // delete shape;
    }
}

void addShapeParams(Shape* shape, const json& data)
{
    shape->id = data["id"];
    shape->text = data["text"];
    shape->x = data["position"]["x"];
    shape->y = data["position"]["y"];
    
    shape->style.color = style_helper::stringToColor(data["style"]["color"]);
    shape->style.border = data["style"]["border"];
    shape->style.textSize = data["style"]["textSize"];
    
}

Shape* createFigure(const json& data)
{
    const std::string type = data["type"];

    if (type == "Circle")
    {
        Circle* circle = new Circle();
        addShapeParams(circle, data);
        circle->radius = data["property"]["radius"];
        return circle;
    }

    if (type == "Diamond")
    {
        Diamond* diamond = new Diamond();
        addShapeParams(diamond, data);
        diamond->sizeA = data["property"]["size_A"];
        diamond->sizeB = data["property"]["size_B"];
        diamond->angle = data["property"]["angle"];
        return diamond;
    }

    if (type == "Rectangle")
    {
        Rectangle* rectangle = new Rectangle();
        addShapeParams(rectangle, data);
        rectangle->sizeA = data["property"]["size_A"];
        rectangle->sizeB = data["property"]["size_B"];
        return rectangle;
    }

    if (type == "Line")
    {
        
        Line* line = new Line();

        line->id = data["id"];
        line->text = data["text"];
        line->style.color = style_helper::stringToColor(data["style"]["color"]);
        line->style.border = data["style"]["border"];
        line->style.textSize = data["style"]["textSize"];
        line->idFrom = data["property"]["idFrom"];
        line->idTo = data["property"]["idTo"];
        line->type = line_helper::stringToLineType(data["property"]["type"]);
        line->orientation = line_helper::stringToLineOrientation(data["property"]["orientation"]);
        
        return line;
    }

    if (type == "Note")
    {
        Note* note = new Note();
        addShapeParams(note, data);
        note->sizeA = data["property"]["size_A"];
        note->sizeB = data["property"]["size_B"];
        note->idTo = data["property"]["idTo"];
        return note;
    }

    else
    {
        std::string errMsg("wrong type in createFigure function");
        LOG_ERROR(FIGURES_STORAGE_LOG, errMsg);
        throw std::invalid_argument(errMsg);
    }

}

FiguresStorage FiguresStorage::createFigures(std::string const& figuresJson)
{
    FiguresStorage figures;
    std::cout << figuresJson << std::endl;
    json data = json::parse(figuresJson);
    for (const auto& figureData : data["figures"]) {
        figures.push_back(createFigure(figureData));
    }
    
    return figures;
}
