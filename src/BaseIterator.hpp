#pragma once

#include <memory>

template<typename T>
class Tree;



template<typename T>
class IterationPolicy{
    /**
     *
     * Base class for iteration policies
     * @brief: Defines behaviour of iterator using IterationPolicy::next(node)
     *
     * */
public:
    virtual typename Tree<T>::Node* next(typename Tree<T>::Node* node) const noexcept = 0;
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
    typename Tree<T>::Node* next(typename Tree<T>::Node* node) const noexcept override;
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
    typename Tree<T>::Node* next(typename Tree<T>::Node* node) const noexcept override;
};




template<typename T>
class BaseIterator {
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

    BaseIterator(typename Tree<T>::Node* root, std::shared_ptr<IterationPolicy<T>> policy);

    virtual const T& operator*() const noexcept;

    virtual bool operator!=(const BaseIterator &other) noexcept;

    virtual bool operator==(const BaseIterator &other) noexcept;

    BaseIterator& operator++() noexcept;

    BaseIterator operator+(int n) const noexcept;

protected:
    typename Tree<T>::Node* curr_node;
    std::shared_ptr<IterationPolicy<T>> policy;
};


#include "BaseIterator.tpp"
