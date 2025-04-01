#include "Backend.hpp"

#include "Logger.hpp"
#include "FileManager.hpp"
#include "FiguresStorage.hpp"
#include "Retranslator.hpp"

#include "AstStatementParser.h"
#include "SemanticAnalyzer.h"

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
                result += it->getValue() + " ";
            }
            else if (it->getValue() == "{")
            {
                result += " " + it->getValue();
            }
            else if (it->getValue() == "}")
            {
                result += it->getValue() + " ";
            }
            else if (it->getValue() == "@endgraph")
            {
                result += "\n" + it->getValue();
            }
            else if (it->getValue() == "circle" || it->getValue() == "rectangle" || it->getValue() == "diamond")
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

} // details

void Backend::translate(std::string const& code)
{
    // TODO: implement
}

std::string Backend::retranslate(std::string const& filePath)
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

        FileManager::writeToFile("build/code.txt", codeStr);

        return codeStr;
    }
    catch (std::exception const& e)
    {
        LOG_ERROR(BACKEND_LOG, "Failed to process: " + std::string(e.what()));
    }

    return "";
}

} // namespace backend
