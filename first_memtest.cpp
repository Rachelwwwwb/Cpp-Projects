#include <iostream>
#include <stdlib.h>
#include "simpleCharManager.h"
using namespace std;

int main(int argc, char *argv[])
{
    simpleCharManager simplest_mem_manager;
    
    /*write driver code as described in the assignment to replace this */
    
    char* p1 = simplest_mem_manager.alloc_chars(13);
    p1[0] = 'H';
    p1[1] = 'e';
    p1[2] = 'l';
    p1[3] = 'l';
    p1[4] = 'o';
    p1[5] = ' ';
    p1[6] = 'w';
    p1[7] = 'o';
    p1[8] = 'r';
    p1[9] = 'l';
    p1[10] = 'd';
    p1[11] = '!';
    p1[12] = '\n';
    
    cout<< p1;
    simplest_mem_manager.free_chars(&p1[6]);

    char* p2 = simplest_mem_manager.alloc_chars(11);
    p2[0] = 'm';
    p2[1] = 'o';
    p2[2] = 'o';
    p2[3] = 'n';
    p2[4] = '!';
    p2[5] = ' ';
    p2[6] = 'B';
    p2[7] = 'y';
    p2[8] = 'e';
    p2[9] = '.';
    p2[10] = '\n';

    return 0;
}

