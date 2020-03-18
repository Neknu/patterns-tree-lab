#include "BaseIterator.hpp"
#include "Tree.h"

#include <iostream>

template<typename T>
BaseIterator<T>::BaseIterator(
        std::shared_ptr<typename Tree<T>::Node> root,
        std::shared_ptr<IterationPolicy<T>> policy
)
        : curr_node(root), policy(policy){}


template<typename T>
BaseIterator<T>& BaseIterator<T>::operator++() noexcept {
    if (curr_node != nullptr){
        curr_node = policy->next(curr_node);
    }

    return *this;
}


template<typename T>
BaseIterator<T> BaseIterator<T>::operator+(int n) const noexcept {
    auto temp = curr_node;
    for (int i = 0; i < n; ++i){
        if (temp == nullptr){
            break;
        }
        temp = policy->next(temp);
    }
    return BaseIterator(temp, policy);
}

template<typename T>
const T& BaseIterator<T>::operator*() const noexcept {
    return curr_node->data;
}

template<typename T>
bool BaseIterator<T>::operator!=(const BaseIterator &other) noexcept {
    return curr_node != other.curr_node;
}

template<typename T>
bool BaseIterator<T>::operator==(const BaseIterator &other) noexcept {
    return curr_node == other.curr_node;
}


template<typename T>
std::shared_ptr<typename Tree<T>::Node> ForwardIteration<T>::next(std::shared_ptr<typename Tree<T>::Node> node) const noexcept{
    return node->next();
}


template<typename T>
std::shared_ptr<typename Tree<T>::Node> ReverseIteration<T>::next(std::shared_ptr<typename Tree<T>::Node> node) const noexcept{
    return node->previous();
}