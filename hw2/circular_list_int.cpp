#include "circular_list_int.h"
#include <iostream>

	CircularListInt::CircularListInt(){

    }

    CircularListInt::~CircularListInt(){
        
        Item* tmp = head;
        for(size_t i = 0; i < count; i++){
            tmp = head->next;
            delete head;
            head = tmp;
        }
        count = 0;
    }
    

    int CircularListInt::get(size_t index) const{
                //return 0 if nothing inside
        if (count == 0) return 0; 
                //return if invalid index input
        if (index < 0) return 0;     
                //wrap around  
        size_t num = size();
        Item*tmp = head;
        int returnval = head->value;

        index = index%num;
        for (size_t a = 0; a < index; a++){
            returnval = tmp->next->value;
            tmp = tmp->next;
        }
        return returnval;
    }
    
    //not including the it
	size_t CircularListInt::size() const{
        if (head == NULL) return 0;
        size_t retval = 1;
        Item* tmp = head;
        while (tmp->next !=head){
            tmp = tmp->next;
            retval++;}
        return retval;
        }

	bool CircularListInt::empty() const{
        if (head == NULL) return true;
    else return false;}

	void CircularListInt::push_back(int value){
        count++;
        Item* toAdd = new Item;
        toAdd->value = value;
        if(head == nullptr){
            head = toAdd;
            head->next = head;
            head->prev = head;
            return;}
        if(head->next == head){
            head->prev = toAdd;
            head->next = toAdd;
            toAdd->next = head;
            toAdd->prev = head;
        }
        else{
        toAdd->next = head;
        toAdd->prev = head->prev;
        head->prev->next = toAdd;
        head->prev = toAdd;}
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

        Item*toRemove = head;
        for (unsigned int i = 0; i < index; i++){
            toRemove = toRemove->next;
        }
        if(toRemove == head){
            if(head->next == head){
                head = nullptr;
               // delete head;
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
        }
        //toRemove = nullptr;
        delete toRemove;
        count--;
    }

