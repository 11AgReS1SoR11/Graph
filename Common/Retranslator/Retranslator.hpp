#include <memory>
#include "AST.hpp"
#include <unordered_map>
#include "Shape.hpp"
#include "Node.hpp"

class Retranslator{
public:
    static Retranslator& getInstance();

    ASTTree parseTree(std::unordered_map<std::string, Shape*> map);

private:
    Retranslator(){};
    Retranslator(const Retranslator&) = delete;
    Retranslator& operator=(const Retranslator&) = delete;
    
    static std::unique_ptr<Retranslator> instance;

    Node* makeObject(Shape* shape) const;
    Node* makeNote(Shape* shape) const;
    Node* makeLink(Shape* shape) const;
}