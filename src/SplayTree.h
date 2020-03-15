#pragma once


#include "Tree.h"

/**
* @brief Class for implementing Splay Tree
*/
template<typename T>
class SplayTree : public Tree<T> {
public:
    SplayTree();
    ~SplayTree();

    void insert(const T& key) override;
    void remove(const T& key) override;
    bool find(const T& key) const override;

    void print() override;

private:
    class SplayNode :public Node {
    public:
        SplayNode(const T& key);
        ~SplayNode();
    private:
        T data;
        SplayNode* parent;
        SplayNode* left;
        SplayNode* right;
    };
};

#include "SplayTree.tpp"

