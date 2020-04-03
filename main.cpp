#include <Tree.h>
#include <BTree.h>
#include <BplusTree.h>
#include <SplayTree.h>
#include <iostream>


int main () {
    BalancedTreeContext<BTree, int> context(std::make_shared<BTree<int>>(3));

    return 0;
}