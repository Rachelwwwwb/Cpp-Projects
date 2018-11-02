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
      // whatever you need to naturally store things.
      // You may also add helper functions here.



     public:
       MinHeap (int d){
        if (d >= 2){
          this->d = d;
          head = NULL;
        }
       }
       /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/
       //template <class T>
       ~MinHeap (){
         for (int i = 0; i < (int) heap.size(); i++){
           delete heap[i];
         }
       }
      
      //template <T>
       void add (T item, int priority){
         Node<T>* toAdd = new Node<T>(item,priority);
         if(heap.size() == 0) head = toAdd;
         else if (((int)heap.size()-1-1)/d >= 0) {
         toAdd->_parent = heap[((int)heap.size()-1-1)/d];}
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
         /* adds the item to the heap, with the given priority. */
      //template <T>
       const T & peek () const{
        if (heap.size() == 0)  throw std::length_error ("not access to head!");
        return head->_item;
       }
         /* returns the element with smallest priority.  
            Break ties however you wish.  
            Throws an exception if the heap is empty. */
      //template <T>
       void remove (){
          if (heap.size() == 0)  throw std::out_of_range ("The heap is empty!");
          //swap the first node with the last node
          head->_priority = heap[(int)heap.size()-1]->_priority;
          head->_item = heap[(int)heap.size()-1]->_item;
          delete heap[(int)heap.size()-1];
          heap[(int)heap.size()-1] = NULL;
          
          Node<T>* newHead = head;
          int numSwap = 0;
          //move the new head to its position
          //the loop should stop when it is a leaf node
          //and record the new node
          while (head->_children.size() != 0){
            //find the smallest children of the head
            int index = 0;
            int smallest = head->_children[0]->_priority;
            for (int i = 1; i < (int) head->_children.size();i++){
                if (head->_children[i]->_priority < smallest){
                  index = i;
                  smallest = head->_children[i]->_priority;
                }
            }
            int tmpPro = head->_children[index]->_priority;
            T tmpItem = head->_children[index]->_item;
            head->_children[index]->_priority = head->_priority;
            head->_children[index]->_item = head->_item;
            head->_item = tmpItem;
            head->_priority = tmpPro;
            head = head->_children[index];
            numSwap ++;
          }
            head = newHead;
       }
         /* removes the element with smallest priority.
            Break ties however you wish.
            Throws an exception if the heap is empty. */


       //template <T>
       bool isEmpty (){
         if (heap.size() == 0) return true;
         else return false;
       }
         /* returns true iff there are no elements on the heap. */

        const T& parent (int i){
          return heap[i]->_parent->_item;
        }

  };
