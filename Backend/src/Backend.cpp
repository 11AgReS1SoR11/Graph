#include "Backend.hpp"

#include "Logger.hpp"
#include "FileManager.hpp"
#include "FiguresStorage.hpp"
#include "Retranslator.hpp"
#include "Translator.hpp"

#include "AstStatementParser.hpp"
#include "SemanticAnalyzer.hpp"
#include "Parser.hpp"

#include <stdexcept>

namespace backend
{

namespace details
{

std::string getCode(AST::ASTTree& ast)
{
    std::string result;
    for (auto it = ast.begin(); it != ast.end(); ++it)
    {
        if (it->childNodes.empty())
        {
            if (it->getValue() == ";")
            {
                result += it->getValue() + "\n\t";
            }
            else if (it->getValue() == "{")
            {
                result += " " + it->getValue() + "\n\t";
            }
            else if (it->getValue() == "}")
            {
                result += it->getValue() + "\n";
            }
            else if (it->getValue() == "@endgraph")
            {
                result += "\n" + it->getValue();
            }
            else if (it->getValue() == "circle" || it->getValue() == "rectangle" || it->getValue() == "diamond" || it->getValue() == "graph" || it->getValue() == "dot_cloud")
            {
                result += "\n" + it->getValue() + " ";
            }
            else
            {
                result += it->getValue();
            }
        }
    }

    return result;
}

std::string getFigures(FiguresStorage const& figures)
{
    std::string json = "[";
    for (auto const& figure : figures)
    {
        json += figure->toJson() + ",";
    }
    json += "]";

    return json;
}

} // details

void Backend::translate(std::string const& filePath, std::string const& outputFilePath)
{
    try
    {
        Parser parser(filePath);
        std::unique_ptr<AST::ASTTree> ast = parser.parse();

        if (!ast)
        {
            LOG_ERROR(BACKEND_LOG, "Failed to parse code");
            return;
        }

        SEMANTICANALYZER::AstStatementParser parserAST(*ast);
        auto programTree = parserAST.parse();

        SEMANTICANALYZER::SemanticAnalyzer& semanticAnalyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
        semanticAnalyzer.semanticAnalysis(programTree, 1);

        Translator trans;
        FiguresStorage figures = trans.translate(programTree);

        std::string const figuresJson = FiguresStorage::toJson(figures);

        if (!FileManager::writeToFile(outputFilePath, figuresJson))
        {
            LOG_ERROR(BACKEND_LOG, "Failed to write json with figures");
        }

        LOG_INFO(BACKEND_LOG, "Translated success:\n" + figuresJson);
    }
    catch (std::exception const& e)
    {
        LOG_ERROR(BACKEND_LOG, "Translate failed: " + std::string(e.what()));
    }
}

std::string Backend::retranslate(std::string const& filePath, std::string const& outputFilePath)
{
    auto json = FileManager::readFromFile(filePath);

    if (!json)
    {
        LOG_ERROR(BACKEND_LOG, "Failed to get json with figures");
        return "";
    }

    try
    {
        FiguresStorage figures = FiguresStorage::createFigures(*json);
        Retranslator& retranslator = Retranslator::getInstance();
        AST::ASTTree ast = retranslator.parseTree(static_cast<std::vector<Shape*>&>(figures));


        SEMANTICANALYZER::AstStatementParser parser(ast);
        auto programTree = parser.parse();

        SEMANTICANALYZER::SemanticAnalyzer& semanticAnalyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
        semanticAnalyzer.semanticAnalysis(programTree, 1);

        std::string const codeStr = details::getCode(ast);

        if (!FileManager::writeToFile(outputFilePath, codeStr))
        {
            LOG_ERROR(BACKEND_LOG, "Failed to write code");
        }

        LOG_INFO(BACKEND_LOG, "Retranslate success:\n" + codeStr);
        return codeStr;
    }
    catch (std::exception const& e)
    {
        LOG_ERROR(BACKEND_LOG, "Retranslate failed: " + std::string(e.what()));
    }

    return "";
}

} // namespace backend
