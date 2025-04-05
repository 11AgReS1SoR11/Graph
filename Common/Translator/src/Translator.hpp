#include <string>
#include <vector>

#include "Figures.hpp"

#include "AstStatementParser.hpp"

#include "FiguresStorage.hpp"

class Translator{
public:
    FiguresStorage translate(std::vector<std::pair<std::string, std::any>>& parsed_ast_tree);
};
