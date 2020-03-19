#pragma once


#include "Tree.h"
#include "SplayIterator.hpp"

/**
* @brief Class for implementing Splay Tree
*/
template<typename T>
class SplayTree : public Tree<T> {
public:
    class SplayNode;
public:
    SplayTree();

    void insert(const T& key) override;
    void remove(const T& key) noexcept override;
    void print() const noexcept override;

    SplayIterator<T> find(const T& key) const noexcept;
    SplayIterator<T> begin() const noexcept;
    SplayIterator<T> end() const noexcept;
    SplayIterator<T> rbegin() const noexcept;
    SplayIterator<T> rend() const noexcept;


public:

class SplayNode : public Tree<T>::Node {
        public:
            explicit SplayNode(const T& key);

            std::shared_ptr<typename Tree<T>::Node> next() const noexcept override;
            std::shared_ptr<typename Tree<T>::Node> previous() const noexcept override;

            [[nodiscard]] bool isLeftSon() const noexcept;
            [[nodiscard]] bool isRightSon() const noexcept;

        public:
            T data;
            std::shared_ptr<SplayNode> parent;
            std::shared_ptr<SplayNode> left;
            std::shared_ptr<SplayNode> right;
        };
};

#include "SplayTree.tpp"
