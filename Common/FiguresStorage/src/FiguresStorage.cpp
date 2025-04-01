#include "FiguresStorage.hpp"

#include "Figures.hpp"
#include "Logger.hpp"

#include <stdexcept>
#include <algorithm>

FiguresStorage::~FiguresStorage()
{
    for (auto* shape : *this)
    {
        // TODO: figure out during GRAP-49
        // delete shape;
    }
}

namespace details
{

// Helper function to trim whitespace from a string
std::string trim(std::string const& str)
{
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), [](unsigned char x){return std::isspace(x);}), result.end());

    if (result.empty())
    {
        static constexpr auto errorMsg = "Inccorect figure's json: only white space";
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    return result;
}

// Function to extract a string value from a JSON object
std::string extractString(std::string const& json, std::string const& key)
{
    size_t keyStart = json.find("\"" + key + "\"");
    if (keyStart == std::string::npos)
    {
        std::string const errorMsg = "Missing key: \"" + key + "\" here: " + json;
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    keyStart += 1 + key.size() + 1; // skip "key"

    if (keyStart > json.size())
    {
        std::string const errorMsg = "Invalid json format: expected \":\", but given nothing. key = " + key + " here: " + json;
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    if (json[keyStart] != ':')
    {
        std::string const errorMsg = "Invalid json format: expected \":\", for key = " + key + " here: " + json;
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    size_t valueStart = json.find("\"", keyStart); 
    if (valueStart == std::string::npos)
    {
        std::string const errorMsg = "Invalid json format: expected quote, but given nothing for key = " + key + " here: " + json;
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    valueStart++; // skip quote

    size_t const valueEnd = json.find("\"", valueStart);
    if (valueEnd == std::string::npos)
    {
        std::string const errorMsg = "Invalid json format: expected end quote, but given nothing for key = " + key + " here: " + json;
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    return json.substr(valueStart, valueEnd - valueStart);
}

// Function to extract a double value from a JSON object
double extractDouble(std::string const& json, std::string const& key)
{
    size_t keyStart = json.find("\"" + key + "\"");
    if (keyStart == std::string::npos)
    {
        std::string const errorMsg = "Missing key: \"" + key + "\" here: " + json;
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    keyStart += 1 + key.size() + 1; // skip "key"

    if (keyStart > json.size())
    {
        std::string const errorMsg = "Invalid json format: expected \":\", but given nothing. key = " + key + " here: " + json;
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    if (json[keyStart] != ':')
    {
        std::string const errorMsg = "Invalid json format: expected \":\", for key = " + key + " here: " + json;
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    size_t const valueStart = keyStart + 1;
    if (valueStart == std::string::npos)
    {
        std::string const errorMsg = "Invalid json format: expected value, but given nothing. key = " + key + " here: " + json;
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg);
        throw std::invalid_argument(errorMsg);
    }

    size_t valueEnd = json.find_first_of(",}", valueStart);
    if (valueEnd == std::string::npos) { valueEnd = json.length(); }

    std::string valueStr = json.substr(valueStart, valueEnd - valueStart);
    return std::stod(valueStr); // TODO: log exception during GRAP-49
}

// Function to create a Shape object from JSON
Shape* createShapeFromJson(const std::string& json)
{
    std::string const type = extractString(json, "type");

    if (type == "Circle")
    {
        Circle* circle = new Circle();
        circle->id = extractString(json, "id");
        circle->text = extractString(json, "text");
        circle->x = extractDouble(json, "x");
        circle->y = extractDouble(json, "y");
        // TODO: implement during GRAP-49
        // circle->style.color = extractString(json, "color");
        circle->style.border = extractDouble(json, "border");
        circle->style.textSize = extractDouble(json, "textSize");
        circle->radius = extractDouble(json, "radius");
        return circle;
    }
    else if (type == "Diamond")
    {
        Diamond* diamond = new Diamond();
        diamond->id = extractString(json, "id");
        diamond->text = extractString(json, "text");
        diamond->x = extractDouble(json, "x");
        diamond->y = extractDouble(json, "y");
        // TODO: implement during GRAP-49
        // diamond->style.color = extractString(json, "color");
        diamond->style.border = extractDouble(json, "border");
        diamond->style.textSize = extractDouble(json, "textSize");
        diamond->sizeA = extractDouble(json, "size_A");
        diamond->sizeB = extractDouble(json, "size_B");
        diamond->angle = extractDouble(json, "angle");
        return diamond;

    }
    else if (type == "Rectangle")
    {
        Rectangle* rectangle = new Rectangle();
        rectangle->id = extractString(json, "id");
        rectangle->text = extractString(json, "text");
        rectangle->x = extractDouble(json, "x");
        rectangle->y = extractDouble(json, "y");
        // TODO: implement during GRAP-49
        // rectangle->style.color = extractString(json, "color");
        rectangle->style.border = extractDouble(json, "border");
        rectangle->style.textSize = extractDouble(json, "textSize");
        rectangle->sizeA = extractDouble(json, "size_A");
        rectangle->sizeB = extractDouble(json, "size_B");
        return rectangle;
    }
    else if (type == "Line")
    {
        // Line does not inherit from Shape, so handle it differently
        Line* line = new Line();
        line->id = extractString(json, "id");
        line->text = extractString(json, "text");
        // TODO: implement during GRAP-49
        // line->style.color = extractString(json, "color");
        line->style.border = extractDouble(json, "border");
        line->style.textSize = extractDouble(json, "textSize");
        line->idFrom = extractString(json, "idFrom");
        line->idTo = extractString(json, "idTo");
        // TODO: implement during GRAP-49
        // line->type = extractInt(json, "type");
        // line->orientation = extractInt(json, "orientation");
        return line;
    }
    else
    {
        std::string const errorMsg = "Unsupported figure's type: " + type;
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg)
        throw std::invalid_argument(errorMsg);
    }

    return nullptr; // Unknown type
}

} // namespace details

FiguresStorage FiguresStorage::createFigures(std::string const& figuresJson)
{
    FiguresStorage figures;

    std::string const trimmedJson = details::trim(figuresJson);

    if (trimmedJson.empty() || trimmedJson[0] != '[' || trimmedJson.back() != ']')
    {
        static constexpr auto errorMsg = "Invalid JSON format: must be a JSON array.";
        LOG_ERROR(FIGURES_STORAGE_LOG, errorMsg)
        throw std::invalid_argument(errorMsg);
    }

    // Extract individual figure JSON strings (simplified parsing)
    size_t start = 1; // Skip '['
    size_t end;
    while ((end = trimmedJson.find("},{", start)) != std::string::npos)
    {
        std::string const figureJson = trimmedJson.substr(start, end - start + 1); // +1 to include the comma
        Shape* figure = details::createShapeFromJson(figureJson);
        figures.push_back(figure);

        start = end + 2; // Skip comma and space
    }

    // Handle the last element (no trailing comma)
    if (start < trimmedJson.length() - 1)
    {
        std::string const figureJson = trimmedJson.substr(start, trimmedJson.length() - 1 - start); // -1 to skip the ']'
        Shape* figure = details::createShapeFromJson(figureJson);
        figures.push_back(figure);
    }

    return figures;
}
