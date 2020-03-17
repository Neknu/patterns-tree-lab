#pragma once

#include "Tree.h"

/**
* @brief Class for implementing Bplus Tree
*/
template<typename T>
class BplusTree : public Tree<T> {
public:
    BplusTree();
    ~BplusTree() override;

    void insert(const T& key) override;
    void remove(const T& key) override;
    bool find(const T& key) const override;

    void print() override;

private:
    class BplusNode : public Tree<T>::Node {
        public:
            BplusNode(const T& key):data(key) {}
            ~BplusNode() {}
        private:
            T data;
        };
};

