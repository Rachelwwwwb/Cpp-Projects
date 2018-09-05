#include <iostream>
#include <stdlib.h>
#include "flexCharManager.h"
using namespace std;

int main(int argc, char *argv[])
{
    simpleCharManager simplest_mem_manager;
    
    /*write driver code as described in the assignment to replace this */
    
    char* p1 = simplest_mem_manager.alloc_chars(6);
    p1[0] = 'H';
    p1[1] = 'e';
    p1[2] = 'l';
    p1[3] = 'l';
    p1[4] = 'o';
    p1[5] = ' ';
    
    char* p2 = simplest_mem_manager.alloc_chars(7);
    p2[0] = 'w';
    p2[1] = 'o';
    p2[2] = 'r';
    p2[3] = 'l';
    p2[4] = 'd';
    p2[5] = '!';
    p2[6] = '\n';
    
    cout<< p1;
    simplest_mem_manager.free_chars(p2);

    char* p3 = simplest_mem_manager.alloc_chars(11);
    p3[0] = 'm';
    p3[1] = 'o';
    p3[2] = 'o';
    p3[3] = 'n';
    p3[4] = '!';
    p3[5] = ' ';
    p3[6] = 'B';
    p3[7] = 'y';
    p3[8] = 'e';
    p3[9] = '.';
    p3[10] = '\n';
    cout << p2;

    return 0;
}

