#pragma once


#include "Tree.h"

/**
* @brief Class for implementing Splay Tree
*/
template<typename T>
class SplayTree : public Tree<T> {
public:
    SplayTree() = default;
    ~SplayTree();

    void insert(const T& key) override;
    void remove(const T& key) noexcept override;
    bool find(const T& key) const noexcept override;

    void print() const noexcept override;

private:
    class SplayNode : public Tree<T>::Node {
        public:

            explicit SplayNode(const T& key);
            ~SplayNode();

            typename Tree<T>::Node* next() const noexcept override;
            typename Tree<T>::Node* previous() const noexcept override;

        private:
            T data;
            SplayNode* parent;
            SplayNode* left;
            SplayNode* right;

            [[nodiscard]] bool isLeftSon() const noexcept;
            [[nodiscard]] bool isRightSon() const noexcept;
        };
};

#include "SplayTree.tpp"

