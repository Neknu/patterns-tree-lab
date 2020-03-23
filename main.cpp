#include <Tree.h>
#include <BTree.h>
#include <BplusTree.h>
#include <SplayTree.h>
#include <iostream>


int main () {
//    SplayTree<int> tree;
    BTree<int> tree(3);
    tree.insert(4);
    tree.insert(499);
    tree.insert(5);
    tree.insert(11);
    tree.insert(12);
    tree.insert(14);
    tree.insert(23);
    tree.insert(12);
    tree.insert(14);
    tree.insert(444);
    tree.insert(12);
    tree.insert(14);
    auto it = tree.find(5);
    while(it != tree.end()) {
        std::cout << it.operator*() << " ";
        ++it;
    }

    tree.print();

    BalancedTreeContext<BTree, int> context(std::make_shared<BTree<int>>(3));



    return 0;
}