#include "selection_sort.h"
#include <iostream>
using namespace std;

Item* findMin(Item * head){
    if (head == NULL) return nullptr;

    Item*returnavl = head;
    //loop until hits the last one
    while (head->next!=nullptr){
        if (returnavl->getValue() > head->next->getValue()){
            returnavl = head->next;
        }
        head = head->next;
    }
    return returnavl;
}

//need to SWAP!!!!!!!!!
Item* LLSelectionSort(Item * head){
    if (head == NULL) return nullptr;
    head->prev = NULL;
    Item*tmp = head;
    Item*returnval = head;
    while (tmp->next != NULL){
    Item*min = findMin(tmp);
    //if the min is the first one, then nothing to do
    if(min == tmp){}
    //if the min and prev is next to each other
    //then the swap would be easy
    else if(min->prev == tmp){
            if(min->next != NULL){
                min->next->prev = tmp;
            }
            if(tmp->prev!=NULL){
                tmp->prev->next = min;
            }
            min->prev = tmp->prev;
            tmp->next = min->next;
            min->next = tmp;
            tmp->prev = min;
            tmp = min;}
    //else if they are not next to each other
    //and should be consider whether min is the last
    //or the tmp is the first
        else{
        if(min->next!=NULL){
        min->next->prev = tmp;}
        min->prev->next = tmp;
        if(tmp->prev !=NULL){
            tmp->prev->next = min;
        }
        tmp->next->prev = min;
        Item* minpre = min->prev;
        Item* minnext = min->next;
        min->prev = tmp->prev;
        min->next = tmp->next;
        tmp->prev = minpre;
        tmp->next = minnext;
        tmp = min;
    }
    //record the head address
    if(tmp->prev == nullptr){
        returnval = tmp;
    }
    tmp = tmp->next;
    }
    return returnval;



}