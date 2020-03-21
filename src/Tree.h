#pragma once

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


template<template <typename T> typename TreeType, typename DataType>
class BalancedTreeContext{
public:
    explicit BalancedTreeContext(std::shared_ptr<TreeType<DataType>> tree);

    /*
     * Тут потім будуть методи для взаємодії з деревом, але зараз це не важливо
     * */

    void insert(const DataType& key);
    void remove(const DataType& key) noexcept;
    void print() const noexcept;

    auto find(const DataType& key);


private:
    std::shared_ptr<TreeType<DataType>> tree;
};



template<template <typename T> typename TreeType, typename DataType>
BalancedTreeContext<TreeType, DataType>::BalancedTreeContext(std::shared_ptr<TreeType<DataType>> tree) : tree(tree){

}



template<template<typename T> typename TreeType, typename DataType>
void BalancedTreeContext<TreeType, DataType>::insert(const DataType &key) {
    tree->insert(key);
}



template<template<typename T> typename TreeType, typename DataType>
void BalancedTreeContext<TreeType, DataType>::remove(const DataType &key) noexcept {
    tree->remove(key);
}

template<template<typename T> typename TreeType, typename DataType>
void BalancedTreeContext<TreeType, DataType>::print() const noexcept {
    tree->print();
}

template<template<typename T> typename TreeType, typename DataType>
auto BalancedTreeContext<TreeType, DataType>::find(const DataType &key) {

    return tree->find(key);
}

