#include "bst.h"
#include <iostream>
#include <exception>

using namespace std;

int main(){
    BinarySearchTree <int,string> binary;


    pair<int,string> pair2;
    pair2.first = 1;
    pair2.second = "bbb";
    binary.insert(pair2);

    pair<int,string> pair1;
    pair1.first =0;
    pair1.second = "aaa";
    binary.insert(pair1);

    pair<int,string> pair3;
    pair3.first = 10;
    pair3.second = "ccc";
    binary.insert(pair3);

    pair<int,string> pair7;
    pair7.first = 2;
    pair7.second = "bbb";
    binary.insert(pair7);

    pair<int,string> pair8;
    pair8.first = 8;
    pair8.second = "aaa";
    binary.insert(pair8);

    pair<int,string> pair6;
    pair6.first = 3;
    pair6.second = "ccc";
    binary.insert(pair6);

    pair<int,string> pair11;
    pair11.first = 11;
    pair11.second = "fff";
    binary.insert(pair11);
/*
    pair<int,string> pair5;
    pair5.first = 5;
    pair5.second = "eee";
    binary.insert(pair5);

    pair<int,string> pair4;
    pair4.first = 4;
    pair4.second = "ddd";
    binary.insert(pair4);*/

    binary.remove(10);

    


    //cerr << "over"<<endl;
    binary.printTree(binary.getRoot());
    cout<< "--------------------------"<<endl;
    binary.print();

   return 0;
}