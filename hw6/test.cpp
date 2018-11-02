#include "MinHeap.h"
#include <iostream>

using namespace std;
int main(){
    MinHeap <int> mh(2);
//   cout << minh.isEmpty()<<endl;   //should be 1
  mh.add(100, 2);
  mh.add(400, 7);
  mh.add(300, 3);
  mh.add(500, 10);
  mh.add(1, 1);

//    cout << minh.isEmpty()<<endl;   //should be 0


    cout << mh.parent(1)<<endl;   //parent of nonde 100, should be 1
    cout << mh.parent(2)<<endl;   //parent of nonde 300, should be 1
    cout << mh.parent(3)<<endl;   //parent of nonde 500, should be 1
    cout << mh.parent(4)<<endl;   //parent of nonde 400, should be 100

  cout << mh.peek()<<endl; //should be 1
  mh.remove();

  cout << mh.peek()<<endl; //should be 100
  mh.remove();

  cout << mh.peek()<<endl; //should be 300
  mh.remove();

  cout << mh.peek()<<endl; //should be 400
  mh.remove();

  cout << mh.peek()<<endl; //should be 500
  mh.remove();

  cout << mh.isEmpty()<<endl;    //should be true
/*
    cout<<minh.peek()<<endl;    //should be 10
    minh.remove();
    cout<<minh.peek()<<endl;    //should be 9
    minh.remove();
    minh.remove();
    minh.remove();
    cout<<minh.peek()<<endl;    //should be 6

*/
    return 0;
}