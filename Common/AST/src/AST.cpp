#include "AST.hpp"

namespace AST
{

ASTTree::ASTTree(Node* root_)
{
    root = root_;
}

ASTTree::~ASTTree()
{
    std::vector<Node*> elements;
    for (auto it = begin(); it != end(); ++it)
    {
        elements.push_back(it.get());
    }

    for (auto* elem : elements)
    {
        elem->destroy();
    }
}

ASTTree::DSFIterator ASTTree::begin()
{
    return ASTTree::DSFIterator(root);
}

ASTTree::DSFIterator ASTTree::end()
{
    return ASTTree::DSFIterator();
}

ASTTree::DSFIterator ASTTree::insert(Node* newNode, DSFIterator it)
{
    if (newNode == nullptr) { throw std::runtime_error("Insert nullptr, bug!?"); }

    if (!root)
    {
        if (it != begin()) { throw std::runtime_error("Insert in empty tree, but not to begin, bug!?"); }
        root = newNode;
        return begin();
    }

    it->addChild(newNode);
    return DSFIterator{newNode};
}

ASTTree::DSFIterator::DSFIterator(Node* root)
{
    if (root) { toVisit.push(root); }
}

ASTTree::DSFIterator& ASTTree::DSFIterator::operator++()
{
    if (!toVisit.empty())
    {
        Node* current = toVisit.top();
        toVisit.pop();

        for (auto it = current->childNodes.rbegin(); it != current->childNodes.rend(); ++it)
        {
            toVisit.push(*it);
        }
    }

    return *this;
}

Node* ASTTree::DSFIterator::get() const noexcept
{
    return toVisit.empty() ? nullptr : toVisit.top();
}

Node& ASTTree::DSFIterator::operator*() const
{
    if (toVisit.empty()) { throw std::runtime_error("Dereference empty iter, bug!?"); }
    return *toVisit.top();
}

Node* ASTTree::DSFIterator::operator->() const
{
    if (toVisit.empty()) { throw std::runtime_error("Dereference empty iter, bug!?"); }
    return toVisit.top();
}

bool ASTTree::DSFIterator::operator!=(DSFIterator const& other) const noexcept
{
    if (toVisit.empty() && other.toVisit.empty()) { return false; }
    if (toVisit.empty() != other.toVisit.empty()) { return true; }
    return toVisit.top() != other.toVisit.top();
}

bool ASTTree::DSFIterator::operator==(DSFIterator const& other) const noexcept
{
    return !(*this != other);
}

} // namespace AST
