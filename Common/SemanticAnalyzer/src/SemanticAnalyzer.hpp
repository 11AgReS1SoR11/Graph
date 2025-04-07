#ifndef SEMANTICANALYZER_H
#define SEMANTICANALYZER_H


#include <string>
#include <set>
#include <vector>
#include <map>
#include <stdexcept>
#include <limits.h>
#include <algorithm>
#include <any>
#include <charconv>
#include <optional>
#include <string_view>
#include <numeric>

#include "Logger.hpp"


namespace GRAMMERCONSTANTS
{
constexpr const char* PROGRAM = "Program";
constexpr const char* START_GRAPH = "@startgraph";
constexpr const char* END_GRAPH = "@endgraph";
constexpr const char* STATEMENTS = "statements";
constexpr const char* STATEMENT = "statement";
constexpr const char* OBJECT_DECL = "object_decl";
constexpr const char* RELATION = "relation";
constexpr const char* NOTE = "note";
constexpr const char* GRAPH = "graph";
constexpr const char* DOT_CLOUD = "dot_cloud";
constexpr const char* GRAPH_CONTENTS = "graph_contents";
constexpr const char* SHAPE = "SHAPE";
constexpr const char* ID = "ID";
constexpr const char* PROPERTIES = "properties";
constexpr const char* PROPERTY = "property";
constexpr const char* START_INTERNAL_BLOCK = "{";
constexpr const char* END_INTERNAL_BLOCK = "}";
constexpr const char* PROPERTY_KEY = "PROPERTY_KEY";
constexpr const char* TEXT = "TEXT";
constexpr const char* NUMBER = "NUMBER";
constexpr const char* ARROW = "ARROW";
constexpr const char* START_DOT_BLOCK = "{";
constexpr const char* END_DOT_BLOCK = "}";

constexpr const char* PROP_COLOR = "color";
constexpr const char* PROP_TEXT = "text";
constexpr const char* PROP_BORDER = "border";
constexpr const char* PROP_X = "x";
constexpr const char* PROP_Y = "y";
constexpr const char* PROP_SIZE_TEXT = "size_text";
constexpr const char* PROP_RADIUS = "radius";
constexpr const char* PROP_SIZE_A = "size_A";
constexpr const char* PROP_SIZE_B = "size_B";
constexpr const char* PROP_ANGLE = "angle";
constexpr const char* PROP_GRID = "grid";

constexpr const char* TYPE_NUMBER = "number";
constexpr const char* TYPE_STRING = "string";
constexpr const char* TYPE_BOOLEAN = "bool";

constexpr const char* SHAPE_CIRCLE = "circle";
constexpr const char* SHAPE_RECTANGLE = "rectangle";
constexpr const char* SHAPE_DIAMOND = "diamond";

constexpr const char* RED = "red";
constexpr const char* BLUE = "blue";
constexpr const char* GREEN = "green";
constexpr const char* BLACK = "black";
constexpr const char* WHITE = "white";
constexpr const char* YELLOW = "yellow";
constexpr const char* PURPLE = "purple";
}


namespace SEMANTICANALYZER
{

struct Property
{
    std::string key;
    std::string value;
};

struct ObjectDecl
{
    std::string shape;
    std::string id;
    std::vector<Property> properties;
};

struct Relation
{
    std::string id1;
    std::string arrow;
    std::string id2;
    std::vector<Property> properties;
};

struct Note
{
    std::string id;
    std::vector<Property> properties;
};

struct Graph
{
    std::string id;
    std::vector<Property> properties;
    std::vector<ObjectDecl> objects;
    std::vector<Relation> relations;
};

struct Dot
{
    std::vector<Property> internalProperties;
};

struct DotCloud
{
    std::string id;
    std::vector<Property> externalProperties;
    std::vector<Dot> dots;
};

struct ConstraintInfo
{
    std::string type;
    std::optional<double> min;
    std::optional<double> max;
};


inline static const std::vector<std::string> COMMON_PROPERTIES =
{
    GRAMMERCONSTANTS::PROP_COLOR,
    GRAMMERCONSTANTS::PROP_TEXT,
    GRAMMERCONSTANTS::PROP_BORDER,
    GRAMMERCONSTANTS::PROP_X,
    GRAMMERCONSTANTS::PROP_Y,
    GRAMMERCONSTANTS::PROP_SIZE_TEXT
};

inline static const std::map<std::string, std::vector<std::string>> SHAPE_SPECIFIC_PROPERTIES =
{
    {GRAMMERCONSTANTS::SHAPE_CIRCLE,    {GRAMMERCONSTANTS::PROP_RADIUS}},
    {GRAMMERCONSTANTS::SHAPE_RECTANGLE, {GRAMMERCONSTANTS::PROP_SIZE_A, GRAMMERCONSTANTS::PROP_SIZE_B}},
    {GRAMMERCONSTANTS::SHAPE_DIAMOND,   {GRAMMERCONSTANTS::PROP_SIZE_A, GRAMMERCONSTANTS::PROP_SIZE_B, GRAMMERCONSTANTS::PROP_ANGLE}},
    {GRAMMERCONSTANTS::DOT_CLOUD,       {GRAMMERCONSTANTS::PROP_GRID}}
};

inline static const std::map<std::string, ConstraintInfo> PROPERTY_CONSTRAINTS =
{
    {GRAMMERCONSTANTS::PROP_RADIUS,    {GRAMMERCONSTANTS::TYPE_NUMBER, 0.0, std::nullopt}},
    {GRAMMERCONSTANTS::PROP_SIZE_A,    {GRAMMERCONSTANTS::TYPE_NUMBER, 0.0, std::nullopt}},
    {GRAMMERCONSTANTS::PROP_SIZE_B,    {GRAMMERCONSTANTS::TYPE_NUMBER, 0.0, std::nullopt}},
    {GRAMMERCONSTANTS::PROP_ANGLE,     {GRAMMERCONSTANTS::TYPE_NUMBER, 0.0, 360.0}},
    {GRAMMERCONSTANTS::PROP_COLOR,     {GRAMMERCONSTANTS::TYPE_STRING, std::nullopt, std::nullopt}},
    {GRAMMERCONSTANTS::PROP_TEXT,      {GRAMMERCONSTANTS::TYPE_STRING, std::nullopt, std::nullopt}},
    {GRAMMERCONSTANTS::PROP_BORDER,    {GRAMMERCONSTANTS::TYPE_NUMBER, 0.0, std::nullopt}},
    {GRAMMERCONSTANTS::PROP_X,         {GRAMMERCONSTANTS::TYPE_NUMBER, std::nullopt, std::nullopt}},
    {GRAMMERCONSTANTS::PROP_Y,         {GRAMMERCONSTANTS::TYPE_NUMBER, std::nullopt, std::nullopt}},
    {GRAMMERCONSTANTS::PROP_SIZE_TEXT, {GRAMMERCONSTANTS::TYPE_NUMBER, 0.0, std::nullopt}},
    {GRAMMERCONSTANTS::PROP_GRID,      {GRAMMERCONSTANTS::TYPE_BOOLEAN, std::nullopt, std::nullopt}}
};

inline static const std::vector<std::string> ALLOWED_COLORS =
{
    GRAMMERCONSTANTS::RED, GRAMMERCONSTANTS::GREEN, GRAMMERCONSTANTS::BLUE, GRAMMERCONSTANTS::BLACK, GRAMMERCONSTANTS::WHITE, GRAMMERCONSTANTS::YELLOW, GRAMMERCONSTANTS::PURPLE
};


class SemanticError: public std::runtime_error
{
public:
    SemanticError(const std::string& message, int statementNumber)
        : std::runtime_error("Ошибка: " + message + " Statement " + std::to_string(statementNumber)){}
};


class SemanticAnalyzer
{
public:

    static SemanticAnalyzer& getInstance()
    {
        static SemanticAnalyzer instance;
        return instance;
    }

    /*!
     * \brief Точка входа в семантический анализатор.
     * \param programTree - набор Statement
     * \param statementNumber - номер Statement для логирования(временное решение)
     */
    void semanticAnalysis(const std::vector<std::pair<std::string, std::any>>& programTree, int statementNumber = 1);

    /*!
     * \brief Сброс состояния анализатора.
     */
    void reset() { scopeStack.clear(); }

    /*!
     * \brief  Функция возвращает все объявленные глобально объекты.
     */
    const std::set<std::string>& getDeclaredObjects() const { return scopeStack.empty() ? emptySet : scopeStack.back(); }

private:

    SemanticAnalyzer() = default;

    SemanticAnalyzer(const SemanticAnalyzer&) = delete;
    SemanticAnalyzer& operator=(const SemanticAnalyzer&) = delete;

    void enterScope() { scopeStack.push_back(emptySet); }
    void exitScope() { if (!scopeStack.empty()) scopeStack.pop_back(); }

    bool isObjectDeclared(const std::string& id) const;
    void declareObject(const std::string& id, int statementNumber);

    /*!
     * \brief Функция проверяется соответсвие заданным атрибутам в структуре ConstraintInfo.
     */
    void checkPropertyValue(const Property& property, const ConstraintInfo& constraints, int statementNumber) const;

    /*!
     * \brief Функция проверяет корректность Statement "Объявление объекта".
     */
    void checkObjectDecl(const ObjectDecl& obj, int statementNumber);

    /*!
     * \brief Функция проверяет корректность Statement "Отношение между объектами".
     */
    void checkRelation(const Relation& rel, int statementNumber);

    /*!
     * \brief Функция проверяет корректность Statement "Заметка".
     */
    void checkNote(const Note& note, int statementNumber);

    /*!
     * \brief Функция проверяет корректность Statement "Граф".
     */
    void checkGraph(const Graph& graph, int statementNumber);

    /*!
     * \brief Функция проверяет корректность Statement "Облако точек".
     */
    void checkDotCloud(const DotCloud& dotCloud, int statementNumber);

private:
    std::vector<std::set<std::string>> scopeStack;
    static inline const std::set<std::string> emptySet {};
};

}

#endif // SEMANTICANALYZER_H
