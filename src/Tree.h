#pragma once

/**
* @brief Class (interface) for all trees
*/
template<typename T>
class Tree {
protected:
    class Node;
    Node* root;

public:
    virtual void insert(const T& key) = 0;
    virtual void remove(const T& key) = 0;
    virtual bool find(const T& key) const = 0;
    
    virtual void print() = 0;
};

#include "Tree.tpp"

