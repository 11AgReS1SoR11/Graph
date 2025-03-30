#ifndef SEMANTICANALYZER_H
#define SEMANTICANALYZER_H

#ifdef _WIN32
#ifdef SEMANTICANALYZER_EXPORTS
#define SEMANTICANALYZER_API __declspec(dllexport)
#else
#define SEMANTICANALYZER_API __declspec(dllimport)
#endif
#else
#define SEMANTICANALYZER_API
#endif


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

#define PROGRAM                 "Program"
#define START_GRAPH             "@startgraph"
#define END_GRAPH               "@endgraph"
#define STATEMENT               "statement"
#define OBJECT_DECL             "object_decl"
#define RELATION                "relation"
#define NOTE                    "note"
#define GRAPH                   "graph"
#define DOT_CLOUD               "dot_cloud"
#define SHAPE                   "SHAPE"
#define ID                      "ID"
#define PROPERTY                "property"
#define DOT                     "dot"
#define START_INTERNAL_BLOCK    "{"
#define END_INTERNAL_BLOCK      "}"
#define PROPERTY_KEY            "PROPERTY_KEY"
#define TEXT                    "TEXT"
#define NUMBER                  "NUMBER"
#define ARROW                   "ARROW"
#define START_DOT_BLOCK         "{"
#define END_DOT_BLOCK           "}"

#define PROP_COLOR      "color"
#define PROP_TEXT       "text"
#define PROP_BORDER     "border"
#define PROP_X          "x"
#define PROP_Y          "y"
#define PROP_SIZE_TEXT  "size_text"
#define PROP_RADIUS     "radius"
#define PROP_SIZE_A     "size_A"
#define PROP_SIZE_B     "size_B"
#define PROP_ANGLE      "angle"
#define PROP_GRID       "grid"

#define TYPE_NUMBER     "number"
#define TYPE_STRING     "string"
#define TYPE_BOOLEAN    "bool"

#define SHAPE_CIRCLE    "circle"
#define SHAPE_RECTANGLE "rectangle"
#define SHAPE_DIAMOND   "diamond"

#define RED             "red"
#define BLUE            "blue"
#define GREEN           "green"
#define BLUE            "blue"
#define BLACK           "black"
#define WHITE           "white"
#define YELLOW          "yellow"
#define PURPLE          "purple"


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
    PROP_COLOR,
    PROP_TEXT,
    PROP_BORDER,
    PROP_X,
    PROP_Y,
    PROP_SIZE_TEXT
};

inline static const std::map<std::string, std::vector<std::string>> SHAPE_SPECIFIC_PROPERTIES =
{
    {SHAPE_CIRCLE,    {PROP_RADIUS}},
    {SHAPE_RECTANGLE, {PROP_SIZE_A, PROP_SIZE_B}},
    {SHAPE_DIAMOND,   {PROP_SIZE_A, PROP_SIZE_B, PROP_ANGLE}},
    {DOT_CLOUD,       {PROP_GRID}}
};

inline static const std::map<std::string, ConstraintInfo> PROPERTY_CONSTRAINTS =
{
    {PROP_RADIUS,    {TYPE_NUMBER, 0.0, std::nullopt}},
    {PROP_SIZE_A,    {TYPE_NUMBER, 0.0, std::nullopt}},
    {PROP_SIZE_B,    {TYPE_NUMBER, 0.0, std::nullopt}},
    {PROP_ANGLE,     {TYPE_NUMBER, 0.0, 360.0}},
    {PROP_COLOR,     {TYPE_STRING, std::nullopt, std::nullopt}},
    {PROP_TEXT,      {TYPE_STRING, std::nullopt, std::nullopt}},
    {PROP_BORDER,    {TYPE_NUMBER, 0.0, std::nullopt}},
    {PROP_X,         {TYPE_NUMBER, std::nullopt, std::nullopt}},
    {PROP_Y,         {TYPE_NUMBER, std::nullopt, std::nullopt}},
    {PROP_SIZE_TEXT, {TYPE_NUMBER, 0.0, std::nullopt}},
    {PROP_GRID,      {TYPE_BOOLEAN, std::nullopt, std::nullopt}}
};

inline static const std::vector<std::string> ALLOWED_COLORS =
{
    RED, GREEN, BLUE, BLACK, WHITE, YELLOW, PURPLE
};


class SemanticError: public std::runtime_error
{
public:
    SemanticError(const std::string& message, int statementNumber)
        : std::runtime_error("Ошибка: " + message + " Statement " + std::to_string(statementNumber)){}
};


class SEMANTICANALYZER_API SemanticAnalyzer
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
