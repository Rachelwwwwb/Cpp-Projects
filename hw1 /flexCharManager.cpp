#include "flexCharManager.h"
#include <iostream>
using namespace std;



flexCharManager::flexCharManager(){
    for (int i = 0 ; i < BUF_SIZE; i++){
        buffer[i] = '\0';
    }
    active_requests = 0;
    used_mem_size = 2;
    free_mem = 10000;
    used_memory =  new Mem_Block* [used_mem_size];
}

flexCharManager::~flexCharManager(){ 
    for (int i = 0; i < used_mem_size; i++){
        delete used_memory[i];}
    delete[] used_memory;
   }
             
char* flexCharManager::alloc_chars(int n){
    char* returnval = NULL;

    //find the space between any two blocks which >=n
    int i = 0; 
    bool istrue = true;
    if (active_requests == 0){
        returnval = buffer;
        istrue = false;}
    else {
    while (istrue){
            if (free_mem < n){
                return NULL;
            }
            if (i == active_requests-1){  
                if (used_memory[i]->physical_location + used_memory[i]->size + n < buffer + BUF_SIZE){
                    returnval = used_memory[i]->physical_location + used_memory[i]->size;
                    break;}
                else{
                    return NULL;}
            }
            if (used_memory[i]->physical_location + used_memory[i]->size + n > used_memory[i+1]->physical_location){
                i++;}
            else if (used_memory[i]->physical_location + used_memory[i]->size + n <= used_memory[i+1]->physical_location){
                returnval = used_memory[i]->physical_location + used_memory[i]->size;
                break;}
        }
    }
    m = new Mem_Block (n, returnval);

    if (active_requests >= used_mem_size){
        used_mem_size *=2;
        Mem_Block** temp = new Mem_Block*[used_mem_size];
        for (int i = 0; i < active_requests; i++){
            temp[i] = used_memory[i];
        }
        
        delete[] used_memory; 

        used_memory = temp;
    }
    else if (active_requests+1 <= used_mem_size/2){
        Mem_Block** temp = new Mem_Block*[used_mem_size/2];
        int j = 0;
        for (int i = 0; i < active_requests; i++){
            temp[j] = used_memory[i];
            j++;
        }
        delete[] used_memory; 
        used_memory = temp;
        used_mem_size /= 2;
    }

    for (int num = active_requests-1; num > i;num--){   
       used_memory[num+1] = used_memory[num]; 
    }

    if (active_requests == 0){
        used_memory[0] = m;
    }else if (active_requests == 1) {
        used_memory[1] = m;
    }else{
        used_memory[i+1] = m;
    }

    active_requests++;
    free_mem = free_mem - n;
return returnval;
}

void flexCharManager::free_chars (char* p) {

    if (p == NULL){
        return;
    }
    else if (p != NULL){
    Mem_Block blck;
    int i = 0;
    while(i < active_requests)
    {
        if (used_memory[i]->physical_location == p){
            blck = *used_memory[i];}
        i++;
    }
    for (int j = 0; j < blck.size; j++){
        *(p+j) = '\0';}

    used_memory[i] = NULL;  
    active_requests--;
    free_mem += blck.size;

    for (int num = i; num < active_requests-1; num++){
        used_memory[num] = used_memory[num+1];}

    used_memory[active_requests] = NULL;
    }
}