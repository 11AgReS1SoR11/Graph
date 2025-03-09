#pragma once

#include <stack>

#include "Node.hpp"

namespace AST
{

class ASTTree
{
public:
    ASTTree(Node* root = nullptr);
    ~ASTTree();

    class DSFIterator
    {
    public:
        DSFIterator() = default;
        explicit DSFIterator(Node* root);

        bool operator!=(DSFIterator const&) const noexcept;
        bool operator==(DSFIterator const&) const noexcept;

        Node* get() const noexcept;
        DSFIterator& operator++();
        Node& operator*() const;
        Node* operator->() const;

    private:
        std::stack<Node*> toVisit;
    };

    DSFIterator begin();
    DSFIterator end();
    DSFIterator insert(Node* newNode, DSFIterator it);

private:
    Node* root;
};

} // namespace AST
