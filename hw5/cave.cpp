#include <stack>
#include <iostream>
#include <string>
using namespace std;

int main(){
    string command;
    stack<char> stk;
    bool isLegal = true;
    cin >> command;
    for (size_t i = 0; i < command.size();i++){
        if (command[i] != 'e' && command[i] != 'w'&& command[i] != 'n'&& command[i] != 's'){
            isLegal = false;
            break;}
        if(!stk.empty()){
            if ((stk.top() == 'w' && command[i] == 'e') || (stk.top() == 'e' && command[i] == 'w') ||
                (stk.top() == 'n' && command[i] == 's') || (stk.top() == 's' && command[i] == 'n'))
                stk.pop();
                continue;}
        stk.push(command[i]);
    }
    if(isLegal){
        if (!stk.empty()) cout << "not rolled up" << endl;
        else cout << "rolled up" <<endl;}
    else    cout << "invalid" << endl;
}
