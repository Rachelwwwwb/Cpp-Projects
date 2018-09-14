#include "selection_sort.h"
#include <iostream>
using namespace std;

Item* findMin(Item * head){
    if (head == NULL) return nullptr;

    Item*returnavl = head;
    while (head->next!=nullptr){
        if (returnavl->getValue() > head->next->getValue()){
            returnavl = head->next;
        }
        head = head->next;
    }
    return returnavl;
}

Item* LLSelectionSort(Item * head){
    if (head == NULL) return nullptr;
    head->prev = NULL;
    Item*tmp = head;
    Item*returnval = head;
    while (tmp->next != NULL){
    Item*min = findMin(tmp);
    if(min == tmp){}

    else if(min->next == NULL){
        if(tmp->prev!=NULL){
            tmp->prev->next = min;
        }
        min->prev->next = NULL;
        min->prev = tmp->prev;
        tmp->prev = min;
        min->next = tmp;
        tmp = min;}

    else {
    if(tmp->prev!=NULL){
            tmp->prev->next = min;}
    min->next->prev = min->prev;
    min->prev->next = min->next;
    min->prev = tmp->prev;
    tmp->prev = min;
    min->next = tmp;
    tmp = min;}
    if(tmp->prev == nullptr){
        returnval = tmp;
    }
    tmp = tmp->next;
    }
    return returnval;
  //  return LLSelectionSort(head->next);



}