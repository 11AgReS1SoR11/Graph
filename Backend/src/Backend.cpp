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
    size_t numOfSkobka = 0;
    std::string prefix = ""; // for tabulate for graph's elements

    std::string result;
    for (auto it = ast.begin(); it != ast.end(); ++it)
    {
        if (it->getValue() == "TEXT")
        {
            result += "\"" + (++it)->getValue() + "\"";
            continue;
        }

        if (it->getValue() == "relation" && prefix == "\t") // is relation in graph
        {
            result += prefix;
        }

        if (it->childNodes.empty())
        {
            if (it->getValue() == ";")
            {
                result += ";\n\t" + prefix;
            }
            else if (it->getValue() == "{")
            {
                result += " {\n\t" + prefix;
                ++numOfSkobka;
            }
            else if (it->getValue() == "}")
            {
                result.pop_back();
                result += "}\n\n";
                if (prefix == "\t" && --numOfSkobka == 0) { prefix = ""; } // end of graph
            }
            else if (it->getValue() == "(")
            {
                result += " (\n\t";
            }
            else if (it->getValue() == ")")
            {
                result.pop_back();
                result.pop_back();
                result += ")\n{\n";
                ++it; // skip '{'
                ++numOfSkobka;
                prefix = "\t";
            }
            else if (it->getValue() == "@startgraph")
            {
                result += "@startgraph\n\n";
            }
            else if (it->getValue() == "circle" || it->getValue() == "rectangle" || it->getValue() == "diamond" || it->getValue() == "graph" || it->getValue() == "dot_cloud")
            {
                result += prefix + it->getValue() + " ";
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

void Backend::translate(std::string const& filePath) noexcept
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

        if (!FileManager::writeToFile("build_release/figures.json", figuresJson)) // TODO: make path variable
        {
            LOG_ERROR(BACKEND_LOG, "Failed to write json with figures");
        }
    }
    catch (std::exception const& e)
    {
        LOG_ERROR(BACKEND_LOG, "Translate failed: " + std::string(e.what()));
    }
}

std::string Backend::retranslate(std::string const& filePath) noexcept
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

        FileManager::writeToFile("build_release/code.txt", codeStr);

        return codeStr;
    }
    catch (std::exception const& e)
    {
        LOG_ERROR(BACKEND_LOG, "Retranslate failed: " + std::string(e.what()));
    }

    return "";
}

} // namespace backend
