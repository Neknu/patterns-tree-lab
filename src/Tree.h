#pragma once

/**
* @brief Class (interface) for all trees
*/
template<typename T>
class Tree {
protected:
    class Node{
    public:
        virtual Node* next() const noexcept = 0;
        virtual Node* previous() const noexcept = 0;
    protected:
        T data;
    };

    Node* root;

public:
    virtual void insert(const T& key) = 0;
    virtual void remove(const T& key) = 0;
    virtual bool find(const T& key) const = 0;

    virtual void print() = 0;
};


template<typename T>
class BalancedTreeContext{
public:
    explicit BalancedTreeContext(const Tree<T>& tree);

    /*
     * Тут потім будуть методи для взаємодії з деревом, але зараз це не важливо
     * */
};

