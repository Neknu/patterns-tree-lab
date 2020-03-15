#pragma once

#include "Tree.h"

template<typename T>
class IterationPolicy;



template<typename T>
class BaseIterator {
/**
 *
 * Base class-interface for iterators
 *
 * Allows us to write specific iterators for trees,
 * and define iterating behaviour with IterationPolicy
 * (Mix of Bridge and Strategy Patterns)
 *
 * */

public:
    BaseIterator(typename Tree<T>::BaseNode* root, const IterationPolicy<T>& policy);

    virtual const T& operator*() noexcept = 0;

    virtual bool operator!=(const BaseIterator &other) noexcept = 0;

    virtual bool operator==(const BaseIterator &other) noexcept = 0;

    BaseIterator &operator++() noexcept;

    BaseIterator &operator+(int n) noexcept;

private:
    typename Tree<T>::BaseNode* curr_node;
    const IterationPolicy<T>& policy;
};



template<typename T>
class IterationPolicy{
    /**
     *
     * Base class for iteration policies
     * Defines behaviour of iterator using IterationPolicy::next(node)
     *
     * */
public:
    virtual BaseIterator<T>& next(typename Tree<T>::BaseNode* node) noexcept = 0;
};



template<typename T>
class ForwardIteration : public IterationPolicy<T>{
    /**
     *
     * Extends IterationPolicy
     * Allows us to iterate on tree in forward order
     *
     * */
public:
    BaseIterator<T>& next(typename Tree<T>::BaseNode* node) override;
};



template<typename T>
class ReverseIteration : public IterationPolicy<T>{
    /**
     *
     * Extends IterationPolicy
     * Allows us to iterate on tree in reverse order
     *
     * */
public:
    BaseIterator<T>& next(typename Tree<T>::BaseNode* node) override;
};


#include "BaseIterator.tpp"
