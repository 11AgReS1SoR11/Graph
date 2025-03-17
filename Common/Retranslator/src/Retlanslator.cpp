#include <Retranslator.hpp>

Retranslator& Retranslator::getInstance(){
    if (!instance)
        instance = std::unique_ptr<Retranslator>(new Retranslator());
    return *instance;
}


ASTTree Retranslator::parseTree(std::unordered_map<std::string, Shape*> map){
    
}