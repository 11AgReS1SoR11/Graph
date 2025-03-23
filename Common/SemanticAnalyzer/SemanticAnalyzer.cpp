#include "SemanticAnalyzer.h"


void SEMANTICANALYZER::SemanticAnalyzer::semanticAnalysis(const std::vector<std::pair<std::string, std::any>> &programTree, int rowNumber)
{
    declaredObjects.clear();

    for (const auto& [type, statement] : programTree)
    {
        if (type == OBJECT_DECL)
        {
            checkObjectDecl(std::any_cast<ObjectDecl>(statement), rowNumber);
        }
        else if (type == RELATION)
        {
            checkRelation(std::any_cast<Relation>(statement), rowNumber);
        }
        else if (type == NOTE)
        {
            checkNote(std::any_cast<Note>(statement), rowNumber);
        }
        else if (type == GRAPH)
        {
            checkGraph(std::any_cast<Graph>(statement), rowNumber);
        }
        else if (type == DOT_CLOUD)
        {
            checkDotCloud(std::any_cast<DotCloud>(statement), rowNumber);
        }

        rowNumber++;
    }
}


void SEMANTICANALYZER::SemanticAnalyzer::checkPropertyValue(const Property &property, const ConstraintInfo &constraints, int rowNumber) const
{
    if (constraints.type == TYPE_NUMBER)
    {
        if (!isNumber(property.value))
        {
            throw SemanticError("Значение свойства " + property.key + " должно быть числом.", rowNumber);
        }

        int value = std::stoi(property.value);

        if (constraints.min.has_value() && value < constraints.min.value())
        {
            throw SemanticError("Значение свойства " + property.key + " должно быть не меньше " +
                                std::to_string(constraints.min.value()) + ".", rowNumber);
        }

        if (constraints.max.has_value() && value > constraints.max.value())
        {
            throw SemanticError("Значение свойства " + property.key + " должно быть не больше " +
                                std::to_string(constraints.max.value()) + ".", rowNumber);
        }
    }
}


void SEMANTICANALYZER::SemanticAnalyzer::checkObjectDecl(const ObjectDecl &obj, int rowNumber)
{
    if (declaredObjects.count(obj.id))
    {
        throw SemanticError("Объект " + obj.id + " уже объявлен.", rowNumber);
    }

    declaredObjects.insert(obj.id);

    std::vector<std::string> allowedProperties = COMMON_PROPERTIES;
    auto specificProps = SHAPE_SPECIFIC_PROPERTIES.at(obj.shape);
    allowedProperties.insert(allowedProperties.end(), specificProps.begin(), specificProps.end());

    for (const Property& prop : obj.properties)
    {
        if (std::find(allowedProperties.begin(), allowedProperties.end(), prop.key) == allowedProperties.end())
        {
            throw SemanticError("Недопустимое свойство " + prop.key + " для фигуры " + obj.shape, rowNumber);
        }

        if (PROPERTY_CONSTRAINTS.count(prop.key))
        {
            checkPropertyValue(prop, PROPERTY_CONSTRAINTS.at(prop.key), rowNumber);
        }
    }
}


void SEMANTICANALYZER::SemanticAnalyzer::checkRelation(const Relation &rel, int rowNumber)
{
    if (!declaredObjects.count(rel.id1))
    {
        throw SemanticError("Объект " + rel.id1 + " не объявлен.", rowNumber);
    }

    if (!declaredObjects.count(rel.id2))
    {
        throw SemanticError("Объект " + rel.id2 + " не объявлен.", rowNumber);
    }

    for (const Property& prop : rel.properties)
    {
        if (std::find(COMMON_PROPERTIES.begin(), COMMON_PROPERTIES.end(), prop.key) == COMMON_PROPERTIES.end())
        {
            throw SemanticError("Недопустимое свойство " + prop.key + " для отношения.", rowNumber);
        }
    }
}


void SEMANTICANALYZER::SemanticAnalyzer::checkNote(const Note &note, int rowNumber)
{
    for (const Property& prop : note.properties)
    {
        if (std::find(COMMON_PROPERTIES.begin(), COMMON_PROPERTIES.end(), prop.key) == COMMON_PROPERTIES.end())
        {
            throw SemanticError("Недопустимое свойство " + prop.key + " для заметки.", rowNumber);
        }
    }
}


void SEMANTICANALYZER::SemanticAnalyzer::checkGraph(const Graph &graph, int rowNumber)
{

}


void SEMANTICANALYZER::SemanticAnalyzer::checkDotCloud(const DotCloud &dotCloud, int rowNumber)
{

}


bool SEMANTICANALYZER::SemanticAnalyzer::isNumber(const std::string &str) const
{
    try {
        std::size_t pos;
        std::stoi(str, &pos);
        return pos == str.length();
    } catch (...) {
        return false;
    }
}
