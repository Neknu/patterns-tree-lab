#include "../src/BTree.h"

#include "catch.hpp"
#include <string>

TEST_CASE("Insertion", "[BTree]") {

    std::shared_ptr<BTree<int>> tree = std::make_shared<BTree<int>>(3);
    SECTION( "Just simple insert" ) {
        tree->insert(10);
        REQUIRE(tree->root != nullptr);
    }

    SECTION("Insert a lot of elements") {
        for(int i = 0; i < 1000; i++)
            tree->insert(i);

        auto current = std::dynamic_pointer_cast<typename BTree<int>::BNode>(tree->root);
        current = current->children[0];

        SECTION("check keys size > min_degree and < 2 * min_degree ") {
            REQUIRE(current->keys.size() >= current->min_degree - 1);
            REQUIRE(current->keys.size() < 2 * current->min_degree);
        }

        SECTION("check children size = keys size + 1 ") {
            REQUIRE(current->children.size() == current->keys.size() + 1);
        }

        REQUIRE(tree->root != nullptr);
    }
}

TEST_CASE("Finding", "[BTree]") {
    std::shared_ptr<BTree<int>> tree = std::make_shared<BTree<int>>(3);

    SECTION("Find for root") {
        tree->insert(10);
        auto it = tree->find(10);
        REQUIRE(*it == 10);
    }

    SECTION("Find inside root (not only one element)") {
        tree->insert(10);
        tree->insert(15);
        tree->insert(20);
        auto it = tree->find(15);
        REQUIRE(*it == 15);
    }

    SECTION("Find with a lot of elements") {
        for(int i = 0; i < 1000; i++)
            tree->insert(i);

        SECTION("Find near to min elem") {
            auto it = tree->find(5);
            REQUIRE(*it == 5);
        }

        SECTION("Find near to middle elem") {
            auto it = tree->find(400);
            REQUIRE(*it == 400);
        }

        SECTION("Find near to max elem") {
            auto it = tree->find(950);
            REQUIRE(*it == 950);
        }

        SECTION("Find max elem") {
            auto it = tree->find(999);
            REQUIRE(*it == 999);
        }

    }
}

TEST_CASE("Check next and prev for BNode", "[BTree]") {
    std::shared_ptr<BTree<int>> tree = std::make_shared<BTree<int>>(3);

    tree->insert(10);
    tree->insert(11);

    auto current = std::dynamic_pointer_cast<typename BTree<int>::BNode>(tree->root);
    current->index = 0;
    auto next = current->next();
    REQUIRE(next->previous() == current);

}

TEST_CASE("BIterators in find function", "[BTree]") {
    std::shared_ptr<BTree<int>> tree = std::make_shared<BTree<int>>(3);

    SECTION("Get next value with BIterator") {
        tree->insert(10);
        tree->insert(15);
        auto it = tree->find(10);
        REQUIRE(*it == 10);
        ++it;
        REQUIRE(*it == 15);
    }

    SECTION("Check print method with BIterators") {
        std::string tree_result;
        for(int i = 0; i < 500; i++) {
            tree_result += std::to_string(i);
            tree->insert(i);
        }

        std::string iterator_result;
        int counter = 0;
        auto it = tree->find(0);
        while(it != tree->end()) {
            iterator_result += std::to_string(*it);
            counter++;
            ++it;
        }

        REQUIRE(iterator_result == tree_result);
    }
}
