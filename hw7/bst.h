#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <queue>
#include <algorithm>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{	
	private:
		//determine the height of a given root
		int height (Node<Key, Value>*root) const;
		bool isBalancedHelper(Node<Key, Value>*root) const;

	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
  		virtual void insert(const std::pair<Key, Value>& keyValuePair); //TODO
        virtual void remove(const Key& key); //TODO
  		void clear(); //TODO
  		void print() const;
  		bool isBalanced() const; //TODO

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<Key,Value>& operator*() const;
				std::pair<Key,Value>* operator->() const;

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;

				friend class BinarySearchTree<Key, Value>;
		};

	public:
		iterator begin() const;
		iterator end() const;
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	public:
		void print() {this->printRoot(this->mRoot);}
		//should be protected
		//move here for debugging use
		Node<Key, Value>* internalFind(const Key& key) const; //TODO

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	mRoot = NULL; 
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	if (mRoot == NULL) return;
	this->clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	Node<Key, Value>* toAdd = new Node<Key, Value> (keyValuePair.first, keyValuePair.second, NULL);
	if (mRoot == NULL){
		mRoot = toAdd; 
		mRoot->setLeft(NULL);
		mRoot->setRight(NULL);
		return;
	}
	else{
		Node<Key, Value>* tmp = mRoot;
		while (mRoot != NULL){
			if (keyValuePair.first > tmp->getKey()){
				if (tmp -> getRight() == NULL){
					tmp -> setRight(toAdd);
					toAdd -> setParent(tmp);
					toAdd->setLeft(NULL);
					toAdd->setRight(NULL);
					return;
				}
				tmp = tmp -> getRight();
			}
			else if (keyValuePair.first < tmp->getKey()){
				if (tmp -> getLeft() == NULL){
					tmp -> setLeft(toAdd);
					toAdd -> setParent(tmp);
					toAdd->setLeft(NULL);
					toAdd->setRight(NULL);
					return;
				}
				tmp = tmp -> getLeft();
			}
			else if (keyValuePair.first == tmp->getKey()){
				tmp->setValue(toAdd->getValue());
				delete toAdd;
				toAdd = NULL;
				return;				
			}
		}
	}
	
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	if (mRoot == NULL)	return;
	Node<Key, Value>* tmp = mRoot;
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
			//if the node has no children
			if (tmp->getLeft() == NULL && tmp->getRight() == NULL){
				if (tmp->getParent() != NULL){
					if (toRight)	tmp->getParent()->setRight(NULL);
					else if (!toRight)	tmp->getParent()->setLeft(NULL);
				}
				if(tmp == mRoot)	mRoot = NULL;
				delete tmp;
				tmp = NULL;
				return;
			}
			//if the node has only one children
			//promote the children and remove it

			//only has the left child
			else if (tmp->getLeft() != NULL && tmp->getRight() == NULL){
				tmp->getLeft()->setParent (tmp->getParent());
				if (tmp->getParent() != NULL){
					if (toRight) tmp->getParent()->setRight(tmp->getLeft());
					else if (!toRight)	tmp->getParent()->setLeft(tmp->getLeft());
				}
				if(tmp == mRoot)	mRoot = tmp->getLeft();
				delete tmp;
				tmp = NULL;
				return;
			}
			//only has the right child
			else if (tmp->getLeft() == NULL && tmp->getRight() != NULL){
				tmp->getRight()->setParent (tmp->getParent());
				if (tmp->getParent() != NULL){
					if (toRight) tmp->getParent()->setRight(tmp->getRight());
					else if (!toRight)	tmp->getParent()->setLeft(tmp->getRight());
				}
				if(tmp == mRoot)	mRoot = tmp->getRight();
				delete tmp;
				tmp = NULL;
				return;
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
					else{
						if(predecessorToRight)	predecessor->getParent()->setRight(NULL);
						else if(!predecessorToRight)	predecessor->getParent()->setLeft(NULL);
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
				
				if (tmp == mRoot)	mRoot = predecessor;
				delete tmp;
				tmp = NULL;
				return;
			}
		}
	}
	//if the key is not in the tree
	return;
}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	if (mRoot == NULL)	return;
	std::queue<Node<Key, Value>*> q;
	q.push(mRoot);
	while (!q.empty()){
		mRoot = q.front();
		q.pop();
		if (mRoot->getLeft() != NULL)	q.push(mRoot->getLeft());
		if (mRoot->getRight() != NULL)	q.push(mRoot->getRight());
		delete mRoot;
		mRoot = NULL;
	}

}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	Node<Key, Value>* tmp = mRoot;
	while(tmp->getLeft() != NULL){
		tmp = tmp->getLeft();
	}
	return tmp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{	
	if (mRoot == NULL)	return NULL;
	Node<Key, Value>* tmp = mRoot;
	while (tmp != NULL){
		if (tmp->getKey() > key)	tmp = tmp->getLeft();
		else if (tmp->getKey() < key)	tmp = tmp->getRight();
		else if (tmp->getKey() == key)	return tmp;
	}
	return NULL;
}

/**
 * Return true iff the BST is an AVL Tree.
 */


template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height (Node<Key, Value>*root) const{
    if (root == NULL)   return 0;
	return 1 + std::max(height(root->getLeft()),height(root->getRight()));
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>*root) const
{
   int leftHeight;
   int rightHeight; 
  
   if(root == NULL) return true;  
  
   leftHeight = height(mRoot->getLeft()); 
   rightHeight = height(mRoot->getRight()); 

   if(abs(leftHeight-rightHeight) <= 1 && isBalancedHelper(root->getLeft()) && isBalancedHelper(root->getRight())) return true; 
	return false;
}


template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
   return isBalancedHelper(mRoot);
}


/**
 * Lastly, we are providing you with a print function, BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->mRoot)

   It will print up to 5 levels of the tree rooted at the passed node, in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
