#include <iostream>
#include <fstream>

using namespace std;


int main (int argc, char* argv[]){

if (argc < 2) {
    cout << "File name!!!" <<endl;
    return -1;
}

ifstream infile (argv[1]);
int num = 0;
infile >> num;
string singleword;

string * words = new string [num];
for (int i = 0; i < num; i++){
    infile >> singleword;
    words[num-1-i] = singleword;
}

for (int i = 0; i < num; i++){
    cout << words[i]<<endl;
}

delete[] words;



    return 0;
}