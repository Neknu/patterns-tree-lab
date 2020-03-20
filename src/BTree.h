#pragma once


#include "Tree.h"
#include "BIterator.hpp"
#include <vector>

/**
* @brief Class for implementing B Tree
*/
template<typename T>
class BTree : public Tree<T> {
public:
    class BNode;
public:
    explicit BTree(int min_degree);

    void insert(const T& key) override;
    void remove(const T& key) noexcept override;
    void print() const noexcept override;

    BIterator<T> find(const T& key) const noexcept;
    BIterator<T> begin() const noexcept;
    BIterator<T> end() const noexcept;
    BIterator<T> rbegin() const noexcept;
    BIterator<T> rend() const noexcept;

    int getParentIndex(std::shared_ptr<BNode> child);
    BIterator<T> findInNode(std::shared_ptr<BNode> current, const T& key) const;


public:
    int min_degree;

    class BNode : public Tree<T>::Node {
    public:
        explicit BNode(bool is_leaf, int min_degree);
        ~BNode() {
            keys.clear();
            children.clear();
        }

        std::shared_ptr<typename Tree<T>::Node> next() const noexcept override;
        std::shared_ptr<typename Tree<T>::Node> previous() const noexcept override;

        void print();

        void insertNonFull(const T& key);

        // A utility function to split the child `child` of this node. `index` is index of child in
        // child array children[].  The Child y must be full when this function is called
        void splitChild(int index, std::shared_ptr<BNode> child);

    public:
        std::vector<T> keys;
        std::vector<std::shared_ptr<BNode>> children;
        bool is_leaf;
        int min_degree;
        int index; // index of current key (-1 if it doesn't need)
        std::shared_ptr<BNode> parent;
    };
};

#include "BTree.tpp"
