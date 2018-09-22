#include "circular_list_int.h"
#include <iostream>

	CircularListInt::CircularListInt(){

    }

    CircularListInt::~CircularListInt(){
        
        if(head == NULL) return;
        Item* tmp = head;
        for(size_t i = 0; i < count; i++){
            //some problem with the count here
            tmp = head->next;
            delete head;
            head = tmp;
        }
        count = 0;
    }
    

    int CircularListInt::get(size_t index) const{
                //return 0 if nothing inside
        if (head == NULL || tail == NULL) return -999; 
                //return if invalid index input
        else if (index < 0) return -999;
                //if getting the value of head
        else if (index == 0) return head->value;
                //if getting the value of tail
        else if (index == count-1) return tail->value;

        else{
        size_t num = size();
        Item*tmp = head;
        int returnval = head->value;
                //wrap around  
        index = index%num;
        for (size_t a = 0; a < index; a++){
            returnval = tmp->next->value;
            tmp = tmp->next;
        }
        return returnval;}
    }
    
    //not including the it
    //get the size of the list
	size_t CircularListInt::size() const{
    
        return count;
        }

    //whether the list is empty
	bool CircularListInt::empty() const{
        if (head == NULL) return true;
    else return false;}

	void CircularListInt::push_back(int value){
        count++;
        Item* toAdd = new Item;
        toAdd->value = value;
        //if the list is empty
        if(head == nullptr){
            head = toAdd;
            tail = toAdd;
            head->next = head;
            head->prev = head;
            return;}
        //if only the head is in the list
        if(head->next == head){
            head->prev = toAdd;
            head->next = toAdd;
            toAdd->next = head;
            toAdd->prev = head;
            tail = toAdd;
        }
        else{
        toAdd->next = head;
        toAdd->prev = head->prev;
        head->prev->next = toAdd;
        head->prev = toAdd;
        tail = toAdd;
        }
    }

	// Sets the item at the given index to have the given value.
	// If an index is passed that is >= the number of items in the list, it should "wrap around" back to the first element.
	void CircularListInt::set(size_t index, int value){
        if(head == nullptr || index < 0){return;}
        //wrap around
        index = index%count;
        //set the value
        Item*toChange = head;
        for (unsigned int i = 0; i < index; i++){
            toChange = toChange->next;
        }
        toChange->value = value;
    }

	// Removes the item at the given index from the list.
	// List elements after the removed element are pulled forward, so their indicies decrease by one.
	// If an index is passed that is larger then the number of items in the list, it should "wrap around" back to the first element.
	void CircularListInt::remove(size_t index){
        
        if (head == nullptr || index < 0 ) {return;}
        //wrap around
        if(index >= count && count !=0){
        index = index % count;}

        //if the index pointing to is the tail
        if (index == count -1){
        Item* toRemove = tail;
        if(toRemove == nullptr){return;}
        else if (toRemove->next == toRemove){
        head = nullptr;
        tail = nullptr;}
    else{
        toRemove->next->prev = toRemove->prev;
        toRemove->prev->next = toRemove->next;
        tail = toRemove->prev;
    }
        delete toRemove;
        count--;
        return;
        }

        Item*toRemove = head;
        for (unsigned int i = 0; i < index; i++){
            toRemove = toRemove->next;
        }
        if(toRemove == head){
            if(head->next == head){
                //which means only one element is in the list
                head = nullptr;
                tail = nullptr;
                }
            else{
            toRemove->prev->next = toRemove->next;
            toRemove->next->prev = toRemove->prev;
          //  delete head;
            head = toRemove->next;
            }
        }
        else if(toRemove!=head){
        toRemove->prev->next = toRemove->next;
        toRemove->next->prev = toRemove->prev;
        if (toRemove == tail){
            tail = toRemove->prev;
        }
        }
        //toRemove = nullptr;
        delete toRemove;
        count--;
    }

