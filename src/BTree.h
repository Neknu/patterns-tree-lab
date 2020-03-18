#pragma once

#include "Tree.h"

#include <vector>

/**
* @brief Class for implementing BTree
*/
template<typename T>
class BTree : public Tree<T> {
private:
    int min_degree;

    class BNode : public Tree<T>::Node {
    protected:
        std::vector<T> keys;
        std::vector<BNode*> children;
        bool is_leaf;
    public:
        BNode(bool is_leaf);
        ~BNode() {
            keys.clear();
            children.clear();
        }

        void print();

        BaseIterator<T> find(const T& key);

    };

    class FindBNode: public BNode {
    private:
        int index;
    public:
        // index of current key in BNode
        FindBNode(BNode* bnode, int index);
        ~FindBNode() {
            this->keys.clear();
            this->children.clear();
        }
    };

public:
    BTree(int min_degree);
    ~BTree() override;

    void insert(const T& key) override;
    void remove(const T& key) override;
    BaseIterator<T> find(const T& key) const override;

    void print() const noexcept override;

};

#include "BTree.tpp"

