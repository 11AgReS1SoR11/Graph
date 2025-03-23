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

#include <iostream>
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


#define OBJECT_DECL     "object_decl"
#define RELATION        "relation"
#define NOTE            "note"
#define GRAPH           "graph"
#define DOT_CLOUD       "dot_cloud"

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

#define TYPE_NUMBER     "number"
#define TYPE_STRING     "string"

#define SHAPE_CIRCLE    "circle"
#define SHAPE_RECTANGLE "rectangle"
#define SHAPE_DIAMOND   "diamond"


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

struct DotCloud
{
    std::string id;
    std::vector<Property> properties;
    std::vector<ObjectDecl> objects;
};

struct ConstraintInfo
{
    std::string type;
    std::optional<int> min;
    std::optional<int> max;
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
    {SHAPE_DIAMOND,   {PROP_SIZE_A, PROP_SIZE_B, PROP_ANGLE}}
};

inline static const std::map<std::string, ConstraintInfo> PROPERTY_CONSTRAINTS =
{
    {PROP_RADIUS,    {TYPE_NUMBER, 0, std::nullopt}},
    {PROP_SIZE_A,    {TYPE_NUMBER, 0, std::nullopt}},
    {PROP_SIZE_B,    {TYPE_NUMBER, 0, std::nullopt}},
    {PROP_ANGLE,     {TYPE_NUMBER, 0, 360}},
    {PROP_COLOR,     {TYPE_STRING, std::nullopt, std::nullopt}},
    {PROP_TEXT,      {TYPE_STRING, std::nullopt, std::nullopt}},
    {PROP_BORDER,    {TYPE_STRING, std::nullopt, std::nullopt}},
    {PROP_X,         {TYPE_NUMBER, std::nullopt, std::nullopt}},
    {PROP_Y,         {TYPE_NUMBER, std::nullopt, std::nullopt}},
    {PROP_SIZE_TEXT, {TYPE_NUMBER, 0, std::nullopt}}
};

class SemanticError: public std::runtime_error
{
public:
    SemanticError(const std::string& message, int rowNumber)
        : std::runtime_error("Ошибка: " + message + " Строка " + std::to_string(rowNumber)){}
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
     * \param rowNumber - номер Statement для логирования(временное решение)
     */
    void semanticAnalysis(const std::vector<std::pair<std::string, std::any>>& programTree, int rowNumber = 1);

    /*!
     * \brief Сброс состояния анализатора.
     */
    void reset() { declaredObjects.clear(); }

    /*!
     * \brief  Функция возвращает все объявленные глобально объекты.
     */
    const std::set<std::string>& getDeclaredObjects() const { return declaredObjects; }

private:

    SemanticAnalyzer() = default;

    SemanticAnalyzer(const SemanticAnalyzer&) = delete;
    SemanticAnalyzer& operator=(const SemanticAnalyzer&) = delete;

    /*!
     * \brief Функция проверяется соответсвие заданным атрибутам в структуре ConstraintInfo.
     */
    void checkPropertyValue(const Property& property, const ConstraintInfo& constraints, int rowNumber) const;

    /*!
     * \brief Функция проверяет корректность Statement "Объявление объекта".
     */
    void checkObjectDecl(const ObjectDecl& obj, int rowNumber, bool isDotCloud = false);

    /*!
     * \brief Функция проверяет корректность Statement "Отношение между объектами".
     */
    void checkRelation(const Relation& rel, int rowNumber);

    /*!
     * \brief Функция проверяет корректность Statement "Заметка".
     */
    void checkNote(const Note& note, int rowNumber);

    /*!
     * \brief Функция проверяет корректность Statement "Граф".
     */
    void checkGraph(const Graph& graph, int rowNumber);

    /*!
     * \brief Функция проверяет корректность Statement "Облако точек".
     */
    void checkDotCloud(const DotCloud& dotCloud, int rowNumber);

    /*!
     * \brief Функция проверяет, является ли строка целым числом.
     */
    bool isNumber(const std::string& str) const;

private:
    std::set<std::string> declaredObjects;

};

}

#endif // SEMANTICANALYZER_H
