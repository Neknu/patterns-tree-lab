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


template<typename T, typename TreeType>
class BalancedTreeContext{
public:
    explicit BalancedTreeContext(std::shared_ptr<TreeType> tree);

    /*
     * Тут потім будуть методи для взаємодії з деревом, але зараз це не важливо
     * */

    void insert(const T& key);
    void remove(const T& key) noexcept;
    void print() const noexcept;

    auto find(const T& key);


private:
    std::shared_ptr<TreeType> tree;
};



template<typename T, typename TreeType>
BalancedTreeContext<T, TreeType>::BalancedTreeContext(std::shared_ptr<TreeType> tree) : tree(tree){

}



template<typename T, typename TreeType>
void BalancedTreeContext<T, TreeType>::insert(const T &key) {
    tree->insert(key);
}



template<typename T, typename TreeType>
void BalancedTreeContext<T, TreeType>::remove(const T &key) noexcept {
    tree->remove(key);
}

template<typename T, typename TreeType>
void BalancedTreeContext<T, TreeType>::print() const noexcept {
    tree->print();
}

template<typename T, typename TreeType>
auto BalancedTreeContext<T, TreeType>::find(const T &key) {

    return tree->find(key);
}

