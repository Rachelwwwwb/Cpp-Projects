#ifndef ROTATEBST_H
#define ROTATEBST_H

#include <iostream>
#include <cstdlib>
#include "bst.h"

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree
{
    private:
        
    protected:
        void leftRotate(Node<Key, Value>* r);
        void rightRotate(Node<Key, Value>* r);
    public:
        bool sameKeys(const rotateBST& t2) const;
        void transform(rotateBST& t2) const;
        
};

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r){

}
