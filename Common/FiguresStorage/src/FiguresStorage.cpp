#include "FiguresStorage.hpp"

#include "Figures.hpp"
#include "Logger.hpp"
#include "json.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <typeinfo>

using json = nlohmann::json;

FiguresStorage::~FiguresStorage()
{
    for (auto* shape : *this)
    {
        delete shape;
    }
}

void checkParam(const json& data, const std::string& param)
{
    if (!data.contains(param))
    {
        std::string errMsg = "missing param in json data: " + param;
        LOG_ERROR(FIGURES_STORAGE_LOG, errMsg);
        throw std::invalid_argument(errMsg);
    }
}

void checkSubParam(const json& data, const std::string& param, const std::string& subparam)
{
    if (!data.contains(param))
    {
        std::string errMsg = "missing param in json data: " + param;
        LOG_ERROR(FIGURES_STORAGE_LOG, errMsg);
        throw std::invalid_argument(errMsg);
    }

    if (!((data[param]).contains(subparam)))
    {
        std::string errMsg = "missing subparam in json data: " + subparam;
        LOG_ERROR(FIGURES_STORAGE_LOG, errMsg);
        throw std::invalid_argument(errMsg);
    }
}

void addShapeParams(Shape& shape, const json& data)
{
    checkParam(data, "id");
    checkParam(data, "text");
    checkSubParam(data, "position", "x");
    checkSubParam(data, "position", "y");
    checkSubParam(data, "style", "color");
    checkSubParam(data, "style", "border");
    checkSubParam(data, "style", "textSize");

    shape.id = data["id"];
    shape.text = data["text"];
    shape.x = data["position"]["x"];
    shape.y = data["position"]["y"];
    shape.style.color = style_helper::stringToColor(data["style"]["color"]);
    shape.style.border = data["style"]["border"];
    shape.style.textSize = data["style"]["textSize"];
}

Shape* createFigure(const json& data)
{
    const std::string type = data["type"];

    try 
    {
        if (type == "Circle")
        {
            std::unique_ptr<Circle> circle = std::make_unique<Circle>();
            addShapeParams(*circle, data);
            checkSubParam(data, "property", "radius");
            circle->radius = data["property"]["radius"];
            return circle.release();
        }

        if (type == "Diamond")
        {
            std::unique_ptr<Diamond> diamond = std::make_unique<Diamond>();
            addShapeParams(*diamond, data);
            checkSubParam(data, "property", "size_A");
            checkSubParam(data, "property", "size_B");
            checkSubParam(data, "property", "angle");
            diamond->sizeA = data["property"]["size_A"];
            diamond->sizeB = data["property"]["size_B"];
            diamond->angle = data["property"]["angle"];
            return diamond.release();
        }

        if (type == "Rectangle")
        {
            std::unique_ptr<Rectangle> rectangle = std::make_unique<Rectangle>();
            addShapeParams(*rectangle, data);
            checkSubParam(data, "property", "size_A");
            checkSubParam(data, "property", "size_B");
            rectangle->sizeA = data["property"]["size_A"];
            rectangle->sizeB = data["property"]["size_B"];
            return rectangle.release();
        }

        if (type == "Line")
        {
            std::unique_ptr<Line> line = std::make_unique<Line>();

            checkParam(data, "text");
            checkSubParam(data, "style", "color");
            checkSubParam(data, "style", "border");
            checkSubParam(data, "style", "textSize");
            checkSubParam(data, "property", "idFrom");
            checkSubParam(data, "property", "idTo");
            checkSubParam(data, "property", "type");
            checkSubParam(data, "property", "orientation");

            line->text = data["text"];
            line->style.color = style_helper::stringToColor(data["style"]["color"]);
            line->style.border = data["style"]["border"];
            line->style.textSize = data["style"]["textSize"];
            line->idFrom = data["property"]["idFrom"];
            line->idTo = data["property"]["idTo"];
            line->type = line_helper::stringToLineType(data["property"]["type"]);
            line->orientation = line_helper::stringToLineOrientation(data["property"]["orientation"]);
            
            return line.release();
        }

        if (type == "Note")
        {
            std::unique_ptr<Note> note = std::make_unique<Note>();
            addShapeParams(*note, data);
            note->sizeA = data["property"]["size_A"];
            note->sizeB = data["property"]["size_B"];
            note->idTo = data["property"]["idTo"];
            return note.release();
        }

        if (type == "Graph")
        {
            std::unique_ptr<Graph> graph = std::make_unique<Graph>();
            addShapeParams(*graph, data);
            checkSubParam(data, "property", "nodes");
            const json& nodes = data["property"]["nodes"];
            for (const auto& node : nodes)
            {
                checkParam(data, "type");
                if (node["type"] == "Note" || node["type"] == "DotCloud" || node["type"] == "Graph")
                {
                    std::string const errMsg = "Unsupported graph's node type: " + node["type"].get<std::string>();
                    LOG_ERROR(FIGURES_STORAGE_LOG, errMsg);
                    throw std::invalid_argument(errMsg);
                }

                graph->nodes.push_back(createFigure(node));
            }   

            return graph.release();
        }

        if (type == "DotCloud")
        {
            std::unique_ptr<DotCloud> dotCloud = std::make_unique<DotCloud>();
            addShapeParams(*dotCloud, data);
            checkSubParam(data, "property", "grid");
            dotCloud->grid = (data["property"]["grid"] == "true") ? true : false;
            checkSubParam(data, "property", "dots");
            const json& nodes = data["property"]["dots"];
            for (const auto& node : nodes)
            {
                if (node["type"] != "Circle")
                {
                    std::string errMsg = "wrong figure type in Dotcloud in createFigure function";
                    LOG_ERROR(FIGURES_STORAGE_LOG, errMsg);
                    throw std::invalid_argument(errMsg);
                }

                dotCloud->dots.push_back(dynamic_cast<Circle*>(createFigure(node)));
            }   

            return dotCloud.release();
        }

        else
        {
            std::string const errMsg = "Unsupported figures type: " + type;
            LOG_ERROR(FIGURES_STORAGE_LOG, errMsg);
            throw std::invalid_argument(errMsg);
        }
    }

    catch(std::exception& e)
    {
        std::string const errMsg = "Wrong json: " + std::string(e.what());
        LOG_ERROR(FIGURES_STORAGE_LOG, errMsg);
        throw std::invalid_argument(errMsg);
    }

    return nullptr;

}

FiguresStorage FiguresStorage::createFigures(std::string const& figuresJson)
{
    FiguresStorage figures;
    json data = json::parse(figuresJson);
    checkParam(data, "figures");
    for (const auto& figureData : data["figures"])
    {
        figures.push_back(createFigure(figureData));
    }

    return figures;
}

std::string FiguresStorage::toJson(std::vector<Shape*> const& figures)
{
    std::string json = "{\n";
    json += "\"figures\":[\n";

    for (Shape* figure : figures)
    {
        json += figure->toJson() + ",\n";
    }
    if (!figures.empty()) { json.pop_back(); }
    json.pop_back();
    json += "]\n}";
    return json;
}
