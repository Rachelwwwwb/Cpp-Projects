#include <iostream>
#include <cstdlib>
#include <set>
#include "bst.h"

template <typename Key, typename Value>
class rotateBST : public BinarySearchTree <Key, Value>
{
    private:
        int height(Node<Key, Value>* root) const;
        void PreOrderRotate(Node<Key, Value>* root1, Node<Key, Value>* root2, const rotateBST<Key, Value>& t1, rotateBST<Key, Value>& t2) const;
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

     //the rotation will only be on two nodes
    //std::cerr << r->getLeft()->getLeft() << r->getLeft()->getRight()<<std::endl;
    if(r->getRight()->getLeft() == NULL && r->getRight()->getRight() == NULL){
        y->setParent(r->getParent());
        if(r->getParent() != NULL){
            if (r->getParent()->getKey() > r->getKey()) r->getParent()->setLeft(y);
            else    r->getParent()->setRight(y);
        } 
        if(y->getLeft() != NULL){
            y->getLeft()->setParent(r);
            r->setRight(y->getLeft());
        }
        else{
            r->setRight(NULL);
        }
        y->setLeft(r);
        r->setParent(y);
        if(r == BinarySearchTree<Key, Value>::mRoot)    BinarySearchTree<Key, Value>::mRoot = y;
        return;
    }

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
   

}



template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r){
    bool zigzig;
    Node<Key, Value>* y;
    Node<Key, Value>* x;

    if(r->getLeft() == NULL)   return;
    y = r->getLeft();

    //the rotation will only be on two nodes
    //std::cerr << r->getLeft()->getLeft() << r->getLeft()->getRight()<<std::endl;
    if(r->getLeft()->getLeft() == NULL && r->getLeft()->getRight() == NULL){
        y->setParent(r->getParent());
        if(r->getParent() != NULL){
            if (r->getParent()->getKey() > r->getKey()) r->getParent()->setLeft(y);
            else    r->getParent()->setRight(y);
        } 
        if(y->getRight() != NULL){
            y->getRight()->setParent(r);
            r->setLeft(y->getRight());
        }
        else{
            r->setLeft(NULL);
        }
        y->setRight(r);
        r->setParent(y);
        if(r == BinarySearchTree<Key, Value>::mRoot)    BinarySearchTree<Key, Value>::mRoot = y;
        return;
    }
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
   /*
    std::cout << "r: "<<r->getKey() << std::endl;
    std::cout << "y: "<<y->getKey() << std::endl;
    std::cout << "x: "<<x->getKey() << std::endl;
    */
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
/*
    std::cout << "t2: -------------------------"<<std::endl;
    t2.BinarySearchTree<Key, Value>::print();
    std::cout << "this: -------------------------"<<std::endl;
    this->BinarySearchTree<Key, Value>::print();
*/
    if (BinarySearchTree<Key, Value>::mRoot == NULL && t2.BinarySearchTree<Key, Value>::mRoot == NULL)	return true;
    else if (BinarySearchTree<Key, Value>::mRoot == NULL || t2.BinarySearchTree<Key, Value>::mRoot == NULL) return false;
	
    typename BinarySearchTree<Key, Value>::iterator t2it = t2.begin();
    for (typename BinarySearchTree<Key, Value>::iterator it = this->begin(); it != this->end(); ++it){
        if(t2it == t2.end())    return false;
        //std::cerr << "it:" << it->first<< " t2it: " << t2it->first<<std::endl;
        if(it->first != t2it->first)  return false;
        ++t2it;
        }
    if (t2it != t2.end())   return false;
    return true;
 }

 template <typename Key, typename Value>
void rotateBST<Key, Value>::PreOrderRotate(Node<Key, Value>* root1, Node<Key, Value>* root2, const rotateBST<Key, Value>& t1, rotateBST<Key, Value>& t2) const {
	
    if (root1 == root2 && root2 == NULL)	return;
    while (root1->getKey() != root2 ->getKey()) {
        if (root2->getRight() != NULL && root2->getLeft() != NULL){
            if (root2->getKey() > root1->getKey()){
                t2.rightRotate(root2);
            }
            else{
                t2.leftRotate(root2);
            }
        }
        else if (root2->getLeft() == NULL)
        t2.leftRotate(root2);
        else if (root2->getRight() == NULL)
        t2.rightRotate(root2);
        
        root2 = root2->getParent();
    }
	if(root2->getLeft() != NULL) 
        PreOrderRotate(root1->getLeft(), root2->getLeft(), t1, t2);
    if(root2->getRight() != NULL)
        PreOrderRotate(root1->getRight(), root2->getRight(), t1, t2);
        
}
 
 template <typename Key, typename Value>
 void rotateBST<Key, Value>::transform(rotateBST<Key, Value>& t2) const{
    //if they don't have the same key, do nothing
    if (!this->sameKeys(t2)) return;
    if(t2.BinarySearchTree<Key, Value>::mRoot == NULL || this->BinarySearchTree<Key, Value>::mRoot == NULL) return;
    //continuing to do the right rotation, until it becomes linked list
    Node<Key, Value>* tmp = t2.BinarySearchTree<Key, Value>::mRoot;
    //std::cerr<<tmp->getRight()<<" "<<tmp->getLeft()<<std::endl;
    //std::cout<<tmp->getKey()<<std::endl;
    while(tmp->getLeft() == NULL)   tmp = tmp->getLeft();
    
    while(tmp != NULL){
        while (tmp->getLeft() != NULL){
            t2.rightRotate(tmp);
            tmp = tmp->getParent();
            //t2.BinarySearchTree<Key, Value>::print();
            //std::cout<<tmp->getKey()<<std::endl;
        }
    tmp = tmp->getRight();
    }

    std::cout << "linked list t2: -------------------------"<<std::endl;
        //std::cerr<<"stop"<<std::endl;

/*
    //check to see if it's a linked list
    Node<Key, Value>* tmp = t2.BinarySearchTree<Key, Value>::mRoot;
    while (tmp->getRight() != NULL){
        if (tmp->getLeft() != NULL) std::cerr << tmp->getKey()<<" has a left child!!" <<std::endl;
    }
*/
    Node<Key, Value>* tmp2 = t2.BinarySearchTree<Key, Value>::mRoot;
    Node<Key, Value>* tmp1 = this->BinarySearchTree<Key, Value>::mRoot;
    //std::cerr<<"start"<<std::endl;
    PreOrderRotate(tmp1, tmp2, *this, t2);
 }