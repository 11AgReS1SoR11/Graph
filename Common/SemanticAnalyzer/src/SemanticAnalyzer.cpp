#include "SemanticAnalyzer.hpp"


void SEMANTICANALYZER::SemanticAnalyzer::semanticAnalysis(const std::vector<std::pair<std::string, std::any>> &programTree, int statementNumber)
{
    enterScope();

    for (const auto& [type, statement] : programTree)
    {
        if (type == GRAMMERCONSTANTS::OBJECT_DECL)
        {
            checkObjectDecl(std::any_cast<const ObjectDecl&>(statement), statementNumber);
        }
        else if (type == GRAMMERCONSTANTS::RELATION)
        {
            checkRelation(std::any_cast<const Relation&>(statement), statementNumber);
        }
        else if (type == GRAMMERCONSTANTS::NOTE)
        {
            checkNote(std::any_cast<const Note&>(statement), statementNumber);
        }
        else if (type == GRAMMERCONSTANTS::GRAPH)
        {
            checkGraph(std::any_cast<const Graph&>(statement), statementNumber);
        }
        else if (type == GRAMMERCONSTANTS::DOT_CLOUD)
        {
            checkDotCloud(std::any_cast<const DotCloud&>(statement), statementNumber);
        }

        statementNumber++;
    }

    exitScope();
}


bool SEMANTICANALYZER::SemanticAnalyzer::isObjectDeclared(const std::string &id) const
{
    if(scopeStack.back().count(id))
        return true;

    return false;
}


void SEMANTICANALYZER::SemanticAnalyzer::declareObject(const std::string &id, int statementNumber)
{
    if(scopeStack.empty())
        enterScope();

    if(scopeStack.back().count(id))
    {
        throw SemanticError("Объект " + id + " уже объявлен в текущей области видимости.", statementNumber);
    }
    scopeStack.back().insert(id);
}


void SEMANTICANALYZER::SemanticAnalyzer::checkPropertyValue(const Property &property, const ConstraintInfo &constraints, int statementNumber) const
{
    if (constraints.type == GRAMMERCONSTANTS::TYPE_NUMBER)
    {
        double propValue = 0.0;

        try {
            propValue = std::stod(property.value);
        }
        catch (const std::exception&)
        {
            throw SemanticError("Значение свойства " + property.key + " должно быть числом.", statementNumber);
        }

        if (constraints.min.has_value() && propValue < constraints.min.value())
        {
            throw SemanticError("Значение свойства " + property.key + " должно быть не меньше " +
                                std::to_string(constraints.min.value()) + ".", statementNumber);
        }

        if (constraints.max.has_value() && propValue > constraints.max.value())
        {
            throw SemanticError("Значение свойства " + property.key + " должно быть не больше " +
                                std::to_string(constraints.max.value()) + ".", statementNumber);
        }
    }
    else if(constraints.type == GRAMMERCONSTANTS::TYPE_STRING)
    {
        if (property.key == GRAMMERCONSTANTS::PROP_COLOR &&
                std::find(ALLOWED_COLORS.begin(), ALLOWED_COLORS.end(), property.value) == ALLOWED_COLORS.end())
        {
            std::string allowed = std::accumulate(ALLOWED_COLORS.begin(), ALLOWED_COLORS.end(), std::string(),
                                                  [](const std::string& a, const std::string& b) { return a.empty() ? b : a + ", " + b; });

            throw SemanticError("Значение свойства color должно быть одним из: " + allowed + ".", statementNumber);
        }
    }
    else if(constraints.type == GRAMMERCONSTANTS::TYPE_BOOLEAN)
    {
        if (property.value != "true" && property.value != "false")
        {
            throw SemanticError("Значение свойства " + property.key + " должно быть логическим (true/false).", statementNumber);
        }
    }
}


void SEMANTICANALYZER::SemanticAnalyzer::checkObjectDecl(const ObjectDecl &obj, int statementNumber)
{
    if (isObjectDeclared(obj.id))
    {
        throw SemanticError("Объект " + obj.id + " уже объявлен.", statementNumber);
    }

    declareObject(obj.id, statementNumber);

    std::vector<std::string> allowedProperties = COMMON_PROPERTIES;

    if (SHAPE_SPECIFIC_PROPERTIES.count(obj.shape))
    {
        auto specificProps = SHAPE_SPECIFIC_PROPERTIES.at(obj.shape);
        allowedProperties.insert(allowedProperties.end(), specificProps.begin(), specificProps.end());
    }

    for (const Property& prop : obj.properties)
    {
        if (std::find(allowedProperties.begin(), allowedProperties.end(), prop.key) == allowedProperties.end())
        {
            throw SemanticError("Недопустимое свойство " + prop.key + " для фигуры " + obj.shape, statementNumber);
        }

        checkPropertyValue(prop, PROPERTY_CONSTRAINTS.at(prop.key), statementNumber);
    }
}


void SEMANTICANALYZER::SemanticAnalyzer::checkRelation(const Relation &rel, int statementNumber)
{
    if (!isObjectDeclared(rel.id1))
    {
        throw SemanticError("Объект " + rel.id1 + " не объявлен.", statementNumber);
    }

    if (!isObjectDeclared(rel.id2))
    {
        throw SemanticError("Объект " + rel.id2 + " не объявлен.", statementNumber);
    }

    if (rel.id1 == GRAMMERCONSTANTS::GRAPH || rel.id1 == GRAMMERCONSTANTS::DOT_CLOUD || rel.id2 == GRAMMERCONSTANTS::GRAPH || rel.id2 == GRAMMERCONSTANTS::DOT_CLOUD)
    {
        throw SemanticError("Связь не может быть создана с графом или облаком точек.", statementNumber);
    }

    for (const Property& prop : rel.properties)
    {
        if (std::find(COMMON_PROPERTIES.begin(), COMMON_PROPERTIES.end(), prop.key) == COMMON_PROPERTIES.end())
        {
            throw SemanticError("Недопустимое свойство " + prop.key + " для отношения.", statementNumber);
        }

        checkPropertyValue(prop, PROPERTY_CONSTRAINTS.at(prop.key), statementNumber);
    }
}


void SEMANTICANALYZER::SemanticAnalyzer::checkNote(const Note &note, int statementNumber)
{
    if (!isObjectDeclared(note.id))
    {
        throw SemanticError("Объект " + note.id + " не объявлен.", statementNumber);
    }

    declareObject(note.id, statementNumber);

    for (const Property& prop : note.properties)
    {
        if (std::find(COMMON_PROPERTIES.begin(), COMMON_PROPERTIES.end(), prop.key) == COMMON_PROPERTIES.end())
        {
            throw SemanticError("Недопустимое свойство " + prop.key + " для заметки.", statementNumber);
        }

        checkPropertyValue(prop, PROPERTY_CONSTRAINTS.at(prop.key), statementNumber);
    }
}


void SEMANTICANALYZER::SemanticAnalyzer::checkGraph(const Graph &graph, int statementNumber)
{
    if (isObjectDeclared(graph.id))
    {
        throw SemanticError("Граф " + graph.id + " уже объявлено.", statementNumber);
    }

    declareObject(graph.id, statementNumber);

    enterScope();

    for (const auto& prop : graph.properties)
    {
        if (std::find(COMMON_PROPERTIES.begin(), COMMON_PROPERTIES.end(), prop.key) == COMMON_PROPERTIES.end())
        {
            throw SemanticError("Недопустимое свойство " + prop.key + " для графа.", statementNumber);
        }

        checkPropertyValue(prop, PROPERTY_CONSTRAINTS.at(prop.key), statementNumber);
    }

    std::set<std::string> relationPairs;
    for (const Relation& rel : graph.relations)
    {
        std::string pair = rel.id1 + "->" + rel.id2;
        std::string reversePair = rel.id2 + "->" + rel.id1;

        if (relationPairs.count(pair) || relationPairs.count(reversePair))
        {
            throw SemanticError("Объекты " + rel.id1 + " и " + rel.id2 + " уже соединены в графе.", statementNumber);
        }

        relationPairs.insert(pair);
    }

    for (const ObjectDecl& obj : graph.objects)
    {
        checkObjectDecl(obj, statementNumber);
    }

    for (const Relation& rel : graph.relations)
    {
        checkRelation(rel, statementNumber);
    }

    exitScope();
}


void SEMANTICANALYZER::SemanticAnalyzer::checkDotCloud(const DotCloud &dotCloud, int statementNumber)
{
    if (isObjectDeclared(dotCloud.id))
    {
        throw SemanticError("Облако точек " + dotCloud.id + " уже объявлено.", statementNumber);
    }

    declareObject(dotCloud.id, statementNumber);

    enterScope();

    std::vector<std::string> allowedExternalProperties = COMMON_PROPERTIES;
    auto specificProps = SHAPE_SPECIFIC_PROPERTIES.at(GRAMMERCONSTANTS::DOT_CLOUD);
    allowedExternalProperties.insert(allowedExternalProperties.end(), specificProps.begin(), specificProps.end());

    for (const Property& prop : dotCloud.externalProperties)
    {
        if (std::find(allowedExternalProperties.begin(), allowedExternalProperties.end(), prop.key) == allowedExternalProperties.end())
        {
            throw SemanticError("Недопустимое свойство " + prop.key + " для облака точек.", statementNumber);
        }

        checkPropertyValue(prop, PROPERTY_CONSTRAINTS.at(prop.key), statementNumber);
    }

    for(const Dot& dot : dotCloud.dots)
    {
        bool hasX = false, hasY = false;

        for(const Property& prop : dot.internalProperties)
        {
            if (prop.key == GRAMMERCONSTANTS::PROP_X) hasX = true;
            if (prop.key == GRAMMERCONSTANTS::PROP_Y) hasY = true;

            checkPropertyValue(prop, PROPERTY_CONSTRAINTS.at(prop.key), statementNumber);
        }

        if (!hasX || !hasY) {
            throw SemanticError("Для точки в облаке точек обязательны свойства x и y.", statementNumber);
        }
    }

    exitScope();
}
