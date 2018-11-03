#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>

  template <class T>
  struct Node{
    T _item;
    int _priority;
    Node* _parent;
    std::vector<Node*> _children;
    Node (T item, int priority){
      _item = item;
      _priority = priority;
    }

  };


  template <class T>
  class MinHeap {
     private:
      std::vector<Node<T>*> heap; 
      int d;
      Node<T>* head;
      

     public:
       MinHeap (int d){
        if (d >= 2){
          this->d = d;
          head = NULL;
        }
       }
       
       ~MinHeap (){
         for (int i = 0; i < (int) heap.size(); i++){
           delete heap[i];
         }
       }
      
       void add (T item, int priority){
         Node<T>* toAdd = new Node<T>(item,priority);
         if(heap.size() == 0) head = toAdd;
         else if (((int)heap.size()-1-1)/d >= 0) {
         toAdd->_parent = heap[((int)heap.size()-1)/d];}
          heap.push_back(toAdd);

         while (toAdd != head){
          if (priority < toAdd->_parent->_priority){
            Node<T>* tmp = new Node<T>(toAdd->_item,toAdd->_priority);
            toAdd->_item = toAdd->_parent->_item;
            toAdd->_priority = toAdd->_parent->_priority;
            toAdd->_parent->_item = tmp->_item;
            toAdd->_parent->_priority = tmp->_priority;
            toAdd = toAdd->_parent;
            delete tmp;
          }
          else{
            break;
          }
         }
       }
         
       const T & peek () const{
        if (heap.size() == 0)  throw std::length_error ("not access to head!");
        return head->_item;
       }
        
       void remove (){
          if (heap.size() == 0)  throw std::out_of_range ("The heap is empty!");
          //swap the first node with the last node
          head->_priority = heap[(int)heap.size()-1]->_priority;
          head->_item = heap[(int)heap.size()-1]->_item;
          delete heap[(int)heap.size()-1];
          heap.pop_back();
          //heap[(int)heap.size()-1] = NULL;
          
          Node<T>* newHead = head;
          //move the new head to its position
          //the loop should stop when it is a leaf node
          //and record the new node
          int headPos = 0;
          while (headPos*d + 1 <= (int)heap.size()-1){
            //find the smallest children of the head
            int smallest = heap[headPos*d + 1]->_priority;
            int index = 1;
            int numOfChild;
            if (headPos*d + d <= (int)heap.size()-1) numOfChild = d;
            else numOfChild = (int)heap.size() - (headPos*d + 1);
            for (int i = 1; i <= numOfChild;i++){
                if (heap[headPos * d + i]->_priority < smallest){
                  index = i;
                  smallest = heap[headPos * d + i]->_priority;
                }
            }
            if (head->_priority <= smallest)  break;
            else{
            int tmpPro = heap[headPos * d + index]->_priority;
            T tmpItem = heap[headPos * d + index]->_item;
            heap[headPos * d + index]->_priority = head->_priority;
            heap[headPos * d + index]->_item = head->_item;
            head->_item = tmpItem;
            head->_priority = tmpPro;
            head = heap[headPos * d + index];
            headPos = headPos * d + index;
            }
          }
            head = newHead;
       }
        
       bool isEmpty (){
         if (heap.size() == 0) return true;
         else return false;
       }
        
  };
