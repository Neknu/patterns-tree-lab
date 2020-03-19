#include <Tree.h>
#include <BTree.h>
#include <BplusTree.h>
#include <SplayTree.h>
#include <iostream>


int main () {
    SplayTree<int> tree;

    BalancedTreeContext<int, SplayTree<int>> context(std::make_shared<SplayTree<int>>(tree));



    return 0;
}