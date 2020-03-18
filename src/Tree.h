#pragma once

#include "BaseIterator.hpp"


#include <memory>


/**
* @brief Class (interface) for all trees
*/
template<typename T>
class Tree {
public:
    class Node{
    public:
        explicit Node(const T& key);
        virtual std::shared_ptr<Node> next() const noexcept = 0;
        virtual std::shared_ptr<Node> previous() const noexcept = 0;

        T data;
    };

protected:
    std::shared_ptr<Node> root;

public:
    Tree();

    virtual void insert(const T& key) = 0;
    virtual void remove(const T& key) noexcept = 0;
    virtual BaseIterator<T> find(const T& key) const noexcept = 0;
    virtual BaseIterator<T> begin() const noexcept;
    virtual BaseIterator<T> end() const noexcept;
    virtual BaseIterator<T> rbegin() const noexcept;
    virtual BaseIterator<T> rend() const noexcept;

    virtual void print() const noexcept = 0;

};

template<typename T>
Tree<T>::Tree() : root(nullptr){
}

template<typename T>
BaseIterator<T> Tree<T>::begin() const noexcept {
    std::shared_ptr<Tree<T>::Node> temp = root;

    while (temp->previous() != nullptr){
        temp = temp->previous();
    }

    return BaseIterator<T>(temp, std::make_shared<ForwardIteration<T>>());
}

template<typename T>
BaseIterator<T> Tree<T>::end() const noexcept {
    return BaseIterator<T>(nullptr, std::make_shared<ForwardIteration<T>>());
}

template<typename T>
BaseIterator<T> Tree<T>::rbegin() const noexcept {
    std::shared_ptr<Tree<T>::Node> temp = root;
    while (temp->next() != nullptr){
        temp = temp->next();
    }

    return BaseIterator<T>(temp, std::make_shared<ReverseIteration<T>>());
}

template<typename T>
BaseIterator<T> Tree<T>::rend() const noexcept {
    return BaseIterator<T>(nullptr, std::make_shared<ReverseIteration<T>>());
}


template<typename T>
Tree<T>::Node::Node(const T &key) : data(key){
}


template<typename T>
class BalancedTreeContext{
public:
    explicit BalancedTreeContext(const Tree<T>& tree);

    /*
     * Тут потім будуть методи для взаємодії з деревом, але зараз це не важливо
     * */
};

