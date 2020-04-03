#pragma once

#include "IterationPolicy.h"

#include <memory>

template<typename T>
class Tree;

template <typename T>
class BTree;

/**
 *
 * class for B Iterators
 *
 * @brief: Allows us to write specific iterators for BTree,
 * and define iterating behaviour with IterationPolicy
 * (Mix of Bridge and Strategy Patterns)
 *
 * */
template<typename T>
class BIterator {

public:
    friend class Tree<T>;

    BIterator(std::shared_ptr<typename BTree<T>::BNode> root, std::shared_ptr<IterationPolicy<T>> policy);


    /**
     * @brief: returns value of current_node
     */
    virtual const T& operator*() const noexcept;

    virtual bool operator!=(const BIterator &other) noexcept;

    virtual bool operator==(const BIterator &other) noexcept;

    BIterator& operator++() noexcept;

    BIterator operator+(int n) const noexcept;

public:
    std::shared_ptr<typename BTree<T>::BNode> curr_node;
    std::shared_ptr<IterationPolicy<T>> policy;
};


#include "BIterator.tpp"