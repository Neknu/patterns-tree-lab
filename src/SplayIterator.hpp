#pragma once

#include <memory>

template<typename T>
class Tree;

template <typename T>
class SplayTree;



template<typename T>
class IterationPolicy{
    /**
     *
     * Base class for iteration policies
     * @brief: Defines behaviour of iterator using IterationPolicy::next(node)
     *
     * */
public:
    virtual std::shared_ptr<typename Tree<T>::Node> next(std::shared_ptr<typename Tree<T>::Node> node) const noexcept = 0;
};



template<typename T>
class ForwardIteration : public IterationPolicy<T>{
    /**
     *
     * Extends IterationPolicy
     * @brief: Allows us to iterate on tree in forward order
     *
     * */
public:
    std::shared_ptr<typename Tree<T>::Node> next(std::shared_ptr<typename Tree<T>::Node> node) const noexcept override;
};



template<typename T>
class ReverseIteration : public IterationPolicy<T>{
    /**
     *
     * Extends IterationPolicy
     * @brief: Allows us to iterate on tree in reverse order
     *
     * */
public:
    std::shared_ptr<typename Tree<T>::Node> next(std::shared_ptr<typename Tree<T>::Node> node) const noexcept override;
};




template<typename T>
class SplayIterator {
/**
 *
 * Base class-interface for iterators
 *
 * @brief: Allows us to write specific iterators for trees,
 * and define iterating behaviour with IterationPolicy
 * (Mix of Bridge and Strategy Patterns)
 *
 * */

public:
    friend class Tree<T>;

    SplayIterator(std::shared_ptr<typename SplayTree<T>::SplayNode> root, std::shared_ptr<IterationPolicy<T>> policy);

    virtual const T& operator*() const noexcept;

    virtual bool operator!=(const SplayIterator &other) noexcept;

    virtual bool operator==(const SplayIterator &other) noexcept;

    SplayIterator& operator++() noexcept;

    SplayIterator operator+(int n) const noexcept;

protected:
    std::shared_ptr<typename SplayTree<T>::SplayNode> curr_node;
    std::shared_ptr<IterationPolicy<T>> policy;
};


#include "SplayIterator.tpp"
