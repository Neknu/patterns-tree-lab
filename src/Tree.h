#pragma once

#include <vector>

/**
* @brief Class (interface) for all trees
*/

template<typename T>
class BaseIterator;


template<typename T>
class IterationPolicy;


template<typename T>
class Tree {
public:

    class BaseNode{
    public:
        virtual BaseNode* next() const noexcept = 0;
        virtual BaseNode* previous() const noexcept = 0;

    protected:
        T data;
    };

protected:
    BaseNode* root;
};


template<typename T>
class BalancedTreeContext{
public:
    explicit BalancedTreeContext(const Tree<T>& tree);

    /*
     * Тут потім будуть методи для взаємодії з деревом, але зараз це не важливо
     * */
};

