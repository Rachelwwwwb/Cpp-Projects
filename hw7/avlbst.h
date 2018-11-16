#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "rotateBST.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{

public:
	// Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they 
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent)
    , mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public rotateBST<Key, Value>
{
private:
    int checkBalanced(AVLNode <Key, Value>* node);
    void adjustHeight(AVLNode <Key, Value>* tmp);

public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    void remove(const Key& key);

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/


template<typename Key, typename Value>
int AVLTree<Key, Value>::checkBalanced(AVLNode <Key, Value>* node){
    int left, right;
    if (node->getRight() == NULL)   right = 0;
    else    right = node->getRight()->getHeight();
    
    if (node->getLeft() == NULL)   left = 0;
    else    left = node->getLeft()->getHeight();

    //the node is balanced, no need to change
    if(left == right || abs(left-right) == 1)   return 0;
    else if(left - right > 1)   return -1;
    else if (right - left > 1)  return 1;    
    return 0;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::adjustHeight(AVLNode <Key, Value>* tmp){
     if(tmp->getLeft() == NULL && tmp->getRight() == NULL)  tmp->setHeight(1);
        else if (tmp->getRight() != NULL && tmp->getLeft() == NULL)    tmp->setHeight(tmp->getRight()->getHeight()+1);
        else if (tmp->getRight() == NULL && tmp->getLeft() != NULL)    tmp->setHeight(tmp->getLeft()->getHeight()+1);
        else{
            tmp->setHeight(1 + std::max(tmp->getRight()->getHeight(),tmp->getLeft()->getHeight()));
        }
}



template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    //insert node
    AVLNode<Key, Value>* toAdd = new AVLNode<Key, Value> (keyValuePair.first, keyValuePair.second, NULL);
	if (this->BinarySearchTree<Key, Value>::mRoot == NULL){
		this->BinarySearchTree<Key, Value>::mRoot = toAdd; 
		this->BinarySearchTree<Key, Value>::mRoot->setLeft(NULL);
		this->BinarySearchTree<Key, Value>::mRoot->setRight(NULL);
        dynamic_cast<AVLNode<Key, Value>*>(this->BinarySearchTree<Key, Value>::mRoot)->setHeight(1);
		return;
	}
	else{
		AVLNode<Key, Value>* tmp = dynamic_cast<AVLNode<Key, Value>*>(this->BinarySearchTree<Key, Value>::mRoot);
		while (this->BinarySearchTree<Key, Value>::mRoot != NULL){
			if (keyValuePair.first > tmp->getKey()){
				if (tmp -> getRight() == NULL){
					tmp -> setRight(toAdd);
					toAdd -> setParent(tmp);
					toAdd->setLeft(NULL);
					toAdd->setRight(NULL);
					break;
				}
				tmp = tmp -> getRight();
			}
			else if (keyValuePair.first < tmp->getKey()){
				if (tmp -> getLeft() == NULL){
					tmp -> setLeft(toAdd);
					toAdd -> setParent(tmp);
					toAdd->setLeft(NULL);
					toAdd->setRight(NULL);
					break;
				}
				tmp = tmp -> getLeft();
			}
			else if (keyValuePair.first == tmp->getKey()){
				tmp->setValue(toAdd->getValue());
				delete toAdd;
				toAdd = NULL;
				return;	
                //no need to update height
                //the tree must keep as an avl tree			
			}
		}
	}
	
    AVLNode<Key, Value>*tmp = toAdd;
    while (tmp != NULL){
        //manually cast the root
        //would have error here but WO LAN DE GAO
        /*
        if (tmp == this->BinarySearchTree<Key, Value>::mRoot)   
        dynamic_cast<AVLNode<Key, Value>*>(this->BinarySearchTree<Key, Value>::mRoot)->setHeight(1+std::max(this->BinarySearchTree<Key, Value>::mRoot->getLeft()->));
        */
        int oldHeight = tmp->getHeight();
        adjustHeight(tmp);
        //if the node is not changing height, no more adjustment need to be made
        if (oldHeight == tmp->getHeight())  return;
        //check balance or not
         int balanced = checkBalanced(tmp);
    
        //unbalanced and left is longer
        //the heights of all the sub-nodes are garanteed not changed
        if(balanced == -1){
        this->rotateBST<Key, Value>::rightRotate(tmp);
        adjustHeight(tmp);
        adjustHeight(tmp->getParent()->getLeft());
        adjustHeight(tmp->getParent());
        tmp = tmp->getParent();
        }
        else if(balanced == 1){
        this->rotateBST<Key, Value>::leftRotate(tmp);
        adjustHeight(tmp);
        adjustHeight(tmp->getParent()->getRight());
        adjustHeight(tmp->getParent());
        tmp = tmp->getParent();
        }

        tmp = tmp->getParent();
    }
    
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
   //literally copy from the bst.h
	if (this->BinarySearchTree<Key, Value>::mRoot == NULL)	return;
	AVLNode<Key, Value>* tmp = dynamic_cast<AVLNode<Key, Value>*>(this->BinarySearchTree<Key, Value>::mRoot);
    //the parent of the deleted root
    //the root we need to begin to check
    AVLNode<Key, Value>* parent = NULL;
	bool toRight;
	while (tmp != NULL){
		if (key > tmp->getKey()){
			tmp = tmp->getRight();
			toRight = true;
		}
		else if (key < tmp->getKey()){
			tmp = tmp->getLeft();
			toRight = false;
		}
		
		else if (key == tmp->getKey()){
            if (tmp->getParent() != NULL)   parent = tmp->getParent();
			//if the node has no children
			if (tmp->getLeft() == NULL && tmp->getRight() == NULL){
				if (tmp->getParent() != NULL){
					if (toRight)	tmp->getParent()->setRight(NULL);
					else if (!toRight)	tmp->getParent()->setLeft(NULL);
				}
				if(tmp == dynamic_cast<AVLNode<Key, Value>*>(this->BinarySearchTree<Key, Value>::mRoot))	this->BinarySearchTree<Key, Value>::mRoot = NULL;
				delete tmp;
				tmp = NULL;
			}
			//only has the left child
			else if (tmp->getLeft() != NULL && tmp->getRight() == NULL){
				tmp->getLeft()->setParent (tmp->getParent());
				if (tmp->getParent() != NULL){
					if (toRight) tmp->getParent()->setRight(tmp->getLeft());
					else if (!toRight)	tmp->getParent()->setLeft(tmp->getLeft());
				}
				if(tmp == dynamic_cast<AVLNode<Key, Value>*>(this->BinarySearchTree<Key, Value>::mRoot))	this->BinarySearchTree<Key, Value>::mRoot = tmp->getLeft();
				delete tmp;
				tmp = NULL;
			}
			//only has the right child
			else if (tmp->getLeft() == NULL && tmp->getRight() != NULL){
				tmp->getRight()->setParent (tmp->getParent());
				if (tmp->getParent() != NULL){
					if (toRight) tmp->getParent()->setRight(tmp->getRight());
					else if (!toRight)	tmp->getParent()->setLeft(tmp->getRight());
				}
				if(tmp == dynamic_cast<AVLNode<Key, Value>*>(this->BinarySearchTree<Key, Value>::mRoot))	this->BinarySearchTree<Key, Value>::mRoot = tmp->getRight();
				delete tmp;
				tmp = NULL;
			}
			//if it has both left child and right child
			else if (tmp->getLeft() != NULL && tmp->getRight() != NULL){
				//find the predecessor
				bool predecessorToRight = false;
				Node<Key, Value>* predecessor = tmp->getLeft();
				while (predecessor->getRight() != NULL)	{
					predecessor = predecessor->getRight();
					predecessorToRight = true;
				}
				//swap the predecesor with the tmp

				//if predecessor has children, then its parent would be the parent of predecessor
				//only when the tmp is not the parent of predecessor
				if(predecessor->getParent() != tmp){
					if (predecessor->getLeft() != NULL)	predecessor->getLeft()->setParent(predecessor->getParent());
					
					//let the parent of predecessor adopt predecessor's children
					//only when the parent of predecessor is not tmp
					if(predecessor->getLeft() != NULL || predecessor->getRight() != NULL){
						if(predecessorToRight)	predecessor->getParent()->setRight(predecessor->getLeft());
						else if (!predecessorToRight) predecessor->getParent()->setLeft(predecessor->getLeft());
					}
				}
					
				//if the tmp has a parent
				if (tmp->getParent() != NULL){
					if(toRight)	tmp->getParent()->setRight(predecessor);
					else if (!toRight)	tmp->getParent()->setLeft(predecessor);}
					predecessor->setParent(tmp->getParent());

				//the tmp must has two children
				//set the children of tmp to be the children of predecessor
				//only when tmp's child is not predecessor
				if(tmp->getLeft()!=predecessor) 
				{	
					tmp->getLeft()->setParent(predecessor);
					predecessor->setLeft(tmp->getLeft());
				}
				predecessor->setRight(tmp->getRight());
				tmp->getRight()->setParent(predecessor);
				
				if (tmp == dynamic_cast<AVLNode<Key, Value>*>(this->BinarySearchTree<Key, Value>::mRoot))	this->BinarySearchTree<Key, Value>::mRoot = predecessor;
				delete tmp;
				tmp = NULL;
			}
		}
	}
    while (parent != NULL){
        int oldHeight = parent->getHeight();
        adjustHeight(parent);
        int balanced = checkBalanced(parent);

        if(balanced == 0 && oldHeight == parent->getHeight())   return;
        //the heights of all the sub-nodes are garanteed not changed
        if(balanced == -1){
        this->rotateBST<Key, Value>::rightRotate(parent);
        adjustHeight(parent);
        adjustHeight(parent->getParent()->getLeft());
        adjustHeight(parent->getParent());
        parent = parent->getParent();
        }
        else if(balanced == 1){
        this->rotateBST<Key, Value>::leftRotate(parent);
        adjustHeight(parent);
        adjustHeight(parent->getParent()->getRight());
        adjustHeight(parent->getParent());
        parent = parent->getParent();
        }
        parent = parent->getParent();
    }
	//if the key is not in the tree
    return;




}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
