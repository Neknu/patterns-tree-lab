#pragma once

/**
* @brief Class (interface) for all trees
*/
template<typename T>
class Tree {
public:

    class BaseNode{
    public:
        T data;

        virtual BaseNode* next() const noexcept = 0;
        virtual BaseNode* previous() const noexcept = 0;
    };

    BaseNode* root;
};

