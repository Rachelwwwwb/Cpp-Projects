#include "bst.h"
#include "rotateBST.h"
#include <iostream>
#include <exception>

using namespace std;

int main(){
    rotateBST <int,string> binary;
    rotateBST <int, string> comp;


    pair<int,string> pair2;
    pair2.first = 1;
    pair2.second = "bbb";
    binary.insert(pair2);
    comp.insert(pair2);

    pair<int,string> pair1;
    pair1.first =0;
    pair1.second = "aaa";
    binary.insert(pair1);
    comp.insert(pair1);

    pair<int,string> pair3;
    pair3.first = 10;
    pair3.second = "ccc";
    binary.insert(pair3);
    comp.insert(pair3);

    pair<int,string> pair7;
    pair7.first = 2;
    pair7.second = "bbb";
    binary.insert(pair7);
    comp.insert(pair7);

    pair<int,string> pair8;
    pair8.first = 8;
    pair8.second = "aaa";
    binary.insert(pair8);
    comp.insert(pair8);

    pair<int,string> pair6;
    pair6.first = 3;
    pair6.second = "ccc";
    binary.insert(pair6);
    comp.insert(pair6);

    pair<int,string> pair11;
    pair11.first = 11;
    pair11.second = "fff";
    binary.insert(pair11);
    comp.insert(pair11);

    cerr<<"this is ok"<<endl;
    
    cout<< binary.sameKeys(comp)<<endl;
    binary.transform(comp);


    //cerr << "over"<<endl;
    cout<< "--------------------------"<<endl;
    //binary.print();

   return 0;
}