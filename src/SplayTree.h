#pragma once


#include "Tree.h"
#include "SplayIterator.hpp"


#include <utility>


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

            std::shared_ptr<typename Tree<T>::Node> next() noexcept override;
            std::shared_ptr<typename Tree<T>::Node> previous() noexcept override;

            [[nodiscard]] bool isLeftSon() const noexcept;
            [[nodiscard]] bool isRightSon() const noexcept;

        public:
            T data;
            std::shared_ptr<SplayNode> parent;
            std::shared_ptr<SplayNode> left;
            std::shared_ptr<SplayNode> right;
        };

private:
    static void zig(std::shared_ptr<SplayNode> node) noexcept;
    static void zigzig(std::shared_ptr<SplayNode> node) noexcept;
    static void zigzag(std::shared_ptr<SplayNode> node) noexcept;


    static std::shared_ptr<SplayNode> splay(std::shared_ptr<SplayNode> node) noexcept;
    static std::pair<std::shared_ptr<SplayNode>, std::shared_ptr<SplayNode>> split(std::shared_ptr<SplayNode> node, const T& key) noexcept;
    static std::shared_ptr<SplayNode> merge(std::shared_ptr<SplayNode> lhs, std::shared_ptr<SplayNode> rhs) noexcept;

    static void swap_value(std::shared_ptr<SplayNode>& var, std::shared_ptr<SplayNode>& value, std::shared_ptr<SplayNode>& new_parent = nullptr);

};


#include "SplayTree.tpp"
