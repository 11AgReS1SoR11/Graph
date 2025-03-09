#pragma once

#include <vector>
#include <string>
#include <stdexcept>

namespace AST
{

struct Node
{
    Node(std::string const& value_) : value{value_} {}
    void destroy() { delete this; } // instead of the destructor

    std::string getValue() const noexcept { return value; }
    void addChild(Node* child)
    {
        if (child == nullptr) { throw std::runtime_error("Add child, but nullptr, bug!?"); }
        childNodes.push_back(child);
    }

    std::string value;
    std::vector<Node*> childNodes;

private:
    ~Node() = default; // Making it impossible to create on the stack
};

} // namespace AST
