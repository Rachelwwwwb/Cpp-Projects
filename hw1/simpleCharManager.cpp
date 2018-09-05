#include <cstddef>
#include "simpleCharManager.h"
#include <iostream>

simpleCharManager::simpleCharManager(){
    for (int i = 0; i < 10000; i++){
        buffer[i] = '\0';
    }
    free_place = buffer;
}

simpleCharManager::~simpleCharManager(){}

char* simpleCharManager::alloc_chars(int n){

    char*ptr = NULL;
    if(free_place == buffer) {
    ptr = buffer;
    free_place = buffer + n;}
    else{
    ptr = free_place;
    free_place += n;
    }
    if (free_place >= buffer+10000*sizeof(char)){
       // std::cout<<free_place;
        return NULL;
    }
    else return ptr;
}

void simpleCharManager::free_chars(char* p){
    if(p!=NULL){
        for (char* i = p; i < buffer + 10000; i++){
                *i = '\0';
        }
    }
}