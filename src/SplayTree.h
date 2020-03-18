#pragma once


#include "Tree.h"
#include "SplayTreeIterator.hpp"

/**
* @brief Class for implementing Splay Tree
*/
template<typename T>
class SplayTree : public Tree<T> {
private:
    class SplayNode;
public:
    SplayTree();

    void insert(const T& key) override;
    void remove(const T& key) noexcept override;
    BaseIterator<T> find(const T& key) const noexcept override;

    void print() const noexcept override;

private:
    class SplayNode : public Tree<T>::Node {
        public:

            explicit SplayNode(const T& key);
            ~SplayNode();

            typename Tree<T>::Node* next() const noexcept override;
            typename Tree<T>::Node* previous() const noexcept override;


            SplayNode* parent;
            SplayNode* left;
            SplayNode* right;

            [[nodiscard]] bool isLeftSon() const noexcept;
            [[nodiscard]] bool isRightSon() const noexcept;
        };
};

#include "SplayTree.tpp"

