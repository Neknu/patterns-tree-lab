#pragma once

#include "Tree.h"

/**
* @brief Class for implementing BTree
*/
template<typename T>
class BTree : public Tree<T> {
public:
    BTree();
    ~BTree() override;

    void insert(const T& key) override;
    void remove(const T& key) override;
    bool find(const T& key) const override;

    void print() override;

private:
class BNode : public Tree<T>::Node {
    public:
        BNode(const T& key) : Tree<T>::Node{key} {}
        ~BNode() {}
    };
};

#include "BTree.tpp"

