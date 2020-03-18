#pragma once

#include "SplayIterator.hpp"


#include <memory>


/**
* @brief Class (interface) for all trees
*/
template<typename T>
class Tree {
public:
    virtual void insert(const T& key) = 0;
    virtual void remove(const T& key) noexcept = 0;
    virtual void print() const noexcept = 0;

    class Node{
    public:
        virtual std::shared_ptr<Node> next() const noexcept = 0;
        virtual std::shared_ptr<Node> previous() const noexcept = 0;
    };

    std::shared_ptr<Node> root;
};


template<typename T>
class BalancedTreeContext{
public:
    explicit BalancedTreeContext(const Tree<T>& tree);

    /*
     * Тут потім будуть методи для взаємодії з деревом, але зараз це не важливо
     * */
};

