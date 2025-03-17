#include <Retranslator.hpp>
#include <typeinfo>

Retranslator& Retranslator::getInstance(){
    if (!instance)
        instance = std::unique_ptr<Retranslator>(new Retranslator());
    return *instance;
}


ASTTree* Retranslator::parseTree(std::unordered_map<std::string, Shape*> map){
    Node* root = new Node("root");
    ASTTree* tree = new ASTTree(root);
    
    for (const auto& [name, shape] : map)
    {
        const std::type_info type = typeid(*shape);
        if (type == typeid())
    }
}