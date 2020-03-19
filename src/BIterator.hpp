#pragma once

#include "IterationPolicy.h"

#include <memory>

template<typename T>
class Tree;

template <typename T>
class BTree;

template<typename T>
class BIterator {
/**
 *
 * class for B Iterators
 *
 * @brief: Allows us to write specific iterators for trees,
 * and define iterating behaviour with IterationPolicy
 * (Mix of Bridge and Strategy Patterns)
 *
 * */

public:
    friend class Tree<T>;

    BIterator(std::shared_ptr<typename IterationBNode<T>::IterationBNode> root, std::shared_ptr<IterationPolicy<T>> policy);

    virtual const T& operator*() const noexcept;

    virtual bool operator!=(const BIterator &other) noexcept;

    virtual bool operator==(const BIterator &other) noexcept;

    BIterator& operator++() noexcept;

    BIterator operator+(int n) const noexcept;

protected:
    std::shared_ptr<typename BTree<T>::IterationBNode> curr_node;
    std::shared_ptr<IterationPolicy<T>> policy;
};


#include "BIterator.tpp"
