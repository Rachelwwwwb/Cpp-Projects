#include <iostream>
#include <cstdlib>
#include <set>
#include "bst.h"

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree <Key, Value>
{
    private:
        int height(Node<Key, Value>* root) const;
    protected:
        void leftRotate(Node<Key, Value>* r);
        void rightRotate(Node<Key, Value>* r);
    public:
        rotateBST();
        ~rotateBST();
        bool sameKeys(const rotateBST<Key, Value>& t2) const;
        void transform(rotateBST<Key, Value>& t2) const;
        
};

//do i really need the constructor and destructor?
template<typename Key, typename Value>
rotateBST<Key, Value>::rotateBST(){

}

template<typename Key, typename Value>
rotateBST<Key, Value>::~rotateBST(){

}


template<typename Key, typename Value>
int rotateBST<Key, Value>::height (Node<Key, Value>*root) const{
    if (root == NULL)   return 0;
	return 1 + std::max(height(root->getLeft()),height(root->getRight()));
}

template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r){
    bool zigzig;
    Node<Key, Value>* y;
    Node<Key, Value>* x;

    if(r->getRight() == NULL)   return;
    y = r->getRight();

    if(y->getLeft() != NULL && y->getRight() != NULL){
        if(height(y->getLeft()) > height(y->getRight())){
            x = y->getLeft();
            zigzig = false;
        }
        else if(height(y->getLeft()) < height(y->getRight())) {
            x = y->getRight();
            zigzig = true;
        }
        else if((height(y->getLeft()) == height(y->getRight()))){
            x = y->getRight();
            zigzig = true;
        }
    }
    else if (y->getLeft() == NULL && y->getRight() != NULL){
        x = y->getRight();
        zigzig = true;
    }
    else if (y->getLeft() != NULL && y->getRight() == NULL){
        x = y->getLeft();
        zigzig = false;
    }
    /*
    std::cout << "r: "<<r->getKey() << std::endl;
    std::cout << "y: "<<y->getKey() << std::endl;
    std::cout << "x: "<<x->getKey() << std::endl;
    */

    //we got x, y and z(r) now, so start the rotation
    //if it is zigzag, unzig the zag first
    if (!zigzig){
        if (x->getRight() != NULL)  {
            x->getRight()->setParent(y);
            y->setLeft(x->getRight());
        }
        else{
            y->setLeft(NULL);
        }
        r->setRight(x);
        x->setParent(r);
        x->setRight(y);
        y->setParent(x);

        zigzig = true;
        //update the x, y and r
        y = x;
        x = y->getRight();
    //std::cout << BinarySearchTree<Key, Value>::mRoot->getRight()->getLeft()->getLeft()<<std::endl;
   /* 
    std::cout << "r: "<<r->getKey() << std::endl;
    std::cout << "y: "<<y->getKey() << std::endl;
    std::cout << "x: "<<x->getKey() << std::endl;
    */
    } 

    //do the zigzig left rotation

    //r adopt the left child of y
    if (y->getLeft() != NULL){
        y->getLeft()->setParent(r);
        r->setRight(y->getLeft());
    }
    else{
        r->setRight(NULL);
    }
    
    //link the r's parent with y
    y->setParent(r->getParent());
    if(r->getParent() != NULL){
        if (r->getParent()->getKey() > r->getKey()) r->getParent()->setLeft(y);
        else    r->getParent()->setRight(y);
    }

    //change the relation between y and r
    r->setParent(y);
    y->setLeft(r);

    if(BinarySearchTree<Key, Value>::mRoot == r)  BinarySearchTree<Key, Value>::mRoot = y;
   
   /*
    std::cout << BinarySearchTree<Key, Value>::mRoot->getKey()<<std::endl;
    std::cout << BinarySearchTree<Key, Value>::mRoot->getLeft()->getKey()<<std::endl;
    std::cout << BinarySearchTree<Key, Value>::mRoot->getRight()->getKey()<<std::endl;
    std::cout << BinarySearchTree<Key, Value>::mRoot->getRight()->getLeft()->getKey()<<std::endl;
    std::cout << BinarySearchTree<Key, Value>::mRoot->getRight()->getRight()->getKey()<<std::endl;
    std::cout << BinarySearchTree<Key, Value>::mRoot->getRight()->getLeft()->getLeft()->getKey()<<std::endl;
    std::cout << BinarySearchTree<Key, Value>::mRoot->getRight()->getLeft()->getRight()->getKey()<<std::endl;

*/
}



template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r){
    bool zigzig;
    Node<Key, Value>* y;
    Node<Key, Value>* x;

    if(r->getLeft() == NULL)   return;
    y = r->getLeft();

    if(y->getRight() != NULL && y->getLeft() != NULL){
        if(height(y->getRight()) > height(y->getLeft())){
            x = y->getRight();
            zigzig = false;
        }
        else if(height(y->getRight()) < height(y->getLeft())) {
            x = y->getLeft();
            zigzig = true;
        }
        else if((height(y->getLeft()) == height(y->getRight()))){
            x = y->getLeft();
            zigzig = true;
        }
    }
    else if (y->getLeft() == NULL && y->getRight() != NULL){
        x = y->getRight();
        zigzig = false;
    }
    else if (y->getLeft() != NULL && y->getRight() == NULL){
        x = y->getLeft();
        zigzig = true;
    }
    /*
    std::cout << "r: "<<r->getKey() << std::endl;
    std::cout << "y: "<<y->getKey() << std::endl;
    std::cout << "x: "<<x->getKey() << std::endl;
    */

    //we got x, y and z(r) now, so start the rotation
    //if it is zigzag, unzig the zag first
    if (!zigzig){
        if (x->getLeft() != NULL)  {
            x->getLeft()->setParent(y);
            y->setRight(x->getLeft());
        }
        else{
            y->setRight(NULL);
        }
        r->setLeft(x);
        x->setParent(r);
        x->setLeft(y);
        y->setParent(x);

        zigzig = true;
        //update the x, y and r
        y = x;
        x = y->getLeft();
    //std::cout << BinarySearchTree<Key, Value>::mRoot->getRight()->getLeft()->getLeft()<<std::endl;
   
    std::cout << "r: "<<r->getKey() << std::endl;
    std::cout << "y: "<<y->getKey() << std::endl;
    std::cout << "x: "<<x->getKey() << std::endl;
    
    } 

    //do the zigzig left rotation

    //r adopt the left child of y
    if (y->getRight() != NULL){
        y->getRight()->setParent(r);
        r->setLeft(y->getRight());
    }
    else{
        r->setLeft(NULL);
    }
    
    //link the r's parent with y
    y->setParent(r->getParent());
    if(r->getParent() != NULL){
        if (r->getParent()->getKey() > r->getKey()) r->getParent()->setLeft(y);
        else    r->getParent()->setRight(y);
    }

    //change the relation between y and r
    r->setParent(y);
    y->setRight(r);

    if(BinarySearchTree<Key, Value>::mRoot == r)  BinarySearchTree<Key, Value>::mRoot = y;

}

template <typename Key, typename Value>
 bool rotateBST<Key, Value>::sameKeys(const rotateBST<Key, Value>& t2) const{
    //promote all the keys into a set 
    std::set<Key> ownKeys, otherKeys;
    
    if (BinarySearchTree<Key, Value>::mRoot == NULL && t2.BinarySearchTree<Key, Value>::mRoot == NULL)	return true;
    else if (BinarySearchTree<Key, Value>::mRoot == NULL || t2.BinarySearchTree<Key, Value>::mRoot == NULL) return false;
	
    std::queue<Node<Key, Value>*> q1;
    std::queue<Node<Key, Value>*> q2;
    Node<Key, Value>* tmp1 = BinarySearchTree<Key, Value>::mRoot;
    Node<Key, Value>* tmp2 = t2.BinarySearchTree<Key, Value>::mRoot;
	
    q1.push(tmp1);
	while (!q1.empty()){
		tmp1 = q1.front();
		q1.pop();
		if (tmp1->getLeft() != NULL)	q1.push(tmp1->getLeft());
		if (tmp1->getRight() != NULL)	q1.push(tmp1->getRight());
		ownKeys.insert(tmp1->getKey());
	}

    while (!q2.empty()){
		tmp2 = q2.front();
		q2.pop();
		if (tmp2->getLeft() != NULL)	q1.push(tmp2->getLeft());
		if (tmp2->getRight() != NULL)	q1.push(tmp2->getRight());
		otherKeys.insert(tmp2->getKey());
	}

    for (std::set<Key>::iterator it = ownKeys.begin(); it != ownKeys.end(); ++it){
        if (otherKeys.find(it) == otherKeys.end())  return false;
        ownKeys.erase(it);
        otherKeys.erase(it);
    }
    if (!ownKeys.empty()||!otherKeys.empty())   return false;
    
    return true;


 }
 
 template <typename Key, typename Value>
 void rotateBST<Key, Value>::transform(rotateBST<Key, Value>& t2) const{

 }