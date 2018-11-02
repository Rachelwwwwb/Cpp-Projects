#include "MinHeap.h"
#include <iostream>

using namespace std;
int main(){
    MinHeap <int> minh(5);
    cout << minh.isEmpty()<<endl;   //should be 1
    minh.add(4,7);
    minh.add(10,1);
    minh.add(9,2);
    minh.add(6,5);
    minh.add(5,6);
    minh.add(8,3);
    minh.add(1,10);
    minh.add(2,9);
    minh.add(3,8);
    minh.add(6,4);

    cout << minh.parent(9)<<endl;   //parent of nonde 1, should be 9
    cout<<minh.peek()<<endl;    //should be 10
    minh.remove();
    cout<<minh.peek()<<endl;    //should be 9
    minh.remove();
    minh.remove();
    minh.remove();
    cout<<minh.peek()<<endl;    //should be 6


    return 0;
}