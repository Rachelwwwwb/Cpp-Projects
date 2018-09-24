#include "stackint.h"
#include "circular_list_int.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int arithmeticParser(const string& line){

const int OPEN_PAREN = -1;
const int CLOSE_PAREN = -2;
const int PLUS = -3;
const int MULTIPLY = -4;
const int SHIFTLEFT = -5;
const int SHIFTRIGHT = -6;
const int SPACE = -7;

     StackInt stk;
    //convert any operator in the string into int
    int numAry[line.size()];

        for (size_t i = 0; i < line.size();i++){

            if(line[i] == '('){
                numAry[i] = OPEN_PAREN;
            }
            else if(line[i] == ')'){
                numAry[i] = CLOSE_PAREN;
            }
            else if(line[i] == '+'){
                numAry[i] = PLUS;
            }
            else if(line[i] == '*'){
                numAry[i] = MULTIPLY;
            }
            else if(line[i] == '<'){
                numAry[i] = SHIFTLEFT;
            }
            else if(line[i] == '>'){
                numAry[i] = SHIFTRIGHT;
            }
            else if (line[i] == ' '||line[i] == '\t'){
                numAry[i] = SPACE;
            }
            else{
                //if there's other character in the line like &{[
                if(line[i] < '0' || line[i] > '9'){
                    return -999;
                }
                numAry[i] = int(line[i]-'0');
                
            }

        }


    for (size_t i = 0; i < line.size();i++){
         
         //when meet operators
         if (numAry[i] == OPEN_PAREN || numAry[i] == PLUS ||numAry[i] == MULTIPLY){   
             stk.push(numAry[i]);
         }

        //when meeting "<" / ">"
         else if (numAry[i] == SHIFTLEFT || numAry[i] == SHIFTRIGHT){
            //all the numbers are now in char
            //i need to transfer them into int in the first place
            size_t j = i+1;
            bool isTrue = true;
            bool shiftSolved = true;
            while(isTrue){
                //if j has reached end of the string and still cannot find a number
                //then return false directly
                if(j-1 == line.size()-1){
                    return -999;
                }
                //if it encounters a number
                //find the position of the first digit
                else if(numAry[j] >= 0){
                    isTrue = false;
                }
                //if the next is a < / > operators
                else if (numAry[j] == SHIFTLEFT || numAry[j] == SHIFTRIGHT){
                    isTrue = true;
                }

                else if (numAry[j] == OPEN_PAREN){
                    isTrue = false;
                    shiftSolved = false;
                }
                else if (numAry[j] == SPACE){
                    //nothing need to do
                }
                else{
                    //when </> is not followed by a number/</>
                    return -999;
                }
                j++;
            }
            //o represents the position of the last digit
            j--;
            //if there's a number immediately after the shifts
            if(shiftSolved){
            size_t o = j;
            string strNum = "";
            strNum += char(numAry[o]) + '0'; 
            int pushValue;
            while(o+1 < line.size() ){
            if (numAry[o+1] >= 0){
                //transfer it into a complete number
                strNum += char(numAry[o+1]) + '0';
                o++;
            }
            else break;
            }
            //the value that is gonna push into the stack
            pushValue = stoi(strNum);

            for (int count = (int)j-1; count >= (int)i; count--){
                if(numAry[count] == SHIFTLEFT){
                    pushValue *= 2; 
                }
                else if (numAry[count] == SHIFTRIGHT){
                    pushValue = pushValue/2;
                }
            }
        
            stk.push(pushValue);
            i = o;
            }
            else{
                for (i = i; i <= j; i++){
                stk.push(numAry[i]);}
                i--;
            }
         }

        //when meeting numbers
        else if (numAry[i] >= 0){
            int pushVal;
            string strNum = "";
            //add the number to the string
            strNum += char(numAry[i]) + '0';
            
            for ( i = i;i < line.size(); i++){
                if(i == line.size()-1){
                    break;
                }
                else if(numAry[i+1] >= 0){
                strNum += char(numAry[i+1]) + '0';}
                else{
                    break;
                }
                }
            
            pushVal = stoi(strNum);
            stk.push(pushVal);
        }
        
        //when meeting a space
        else if (numAry[i] == SPACE){
            //nothing happened
        }

        //when meeting close paren
        else if (numAry[i] == CLOSE_PAREN){
           if(stk.empty()){return -999;}

           int stk_ary [65535];
           int count = 0;
           bool openParen = false;
           while(!stk.empty()){
               if(stk.top() == OPEN_PAREN){
                   stk.pop();
                   openParen = true;
                   break;
               }
               else{
            //store the top in the int array
               stk_ary[count] = stk.top();   
               stk.pop();
               count++;
           }
        }

            //if no open_paren at the end
            if(!openParen) {return -999;}
            

            //cases like (3) / (<3)
            if(count < 3){return -999;}
            int first = -888;
            int next = -888;
            int oprt = -888;
            int consOpt = -888;
            //something like (+) or (*<) || ((12+12)(123+1))
            for (int ary_num = 0; ary_num < count; ary_num++){
                if(ary_num%2 == 0){
                    if(stk_ary[ary_num] < 0) {return -999;}
                    else {
                        if (first == -888) {
                            first = stk_ary[ary_num];}
                        else if (next == -888) {
                            next = stk_ary[ary_num];
                            if (oprt == -888){return -999;}
                            //do the operation finally
                            else if (oprt == PLUS){
                                first += next;
                                next = -888;
                                oprt = -888;
                            }
                            else if (oprt == MULTIPLY){
                                first *= next;
                                next = -888;
                                oprt = -888;
                            }
                        
                        }
                        else {return -999;}
                    }

                }

                else if(ary_num%2 == 1){
                    if(stk_ary[ary_num] >= 0) {return -999;}
                    else if (stk_ary[ary_num] == PLUS || stk_ary[ary_num] == MULTIPLY){
                        if(consOpt == -888){
                        oprt = stk_ary[ary_num];
                        consOpt = oprt;}
                        else{
                            oprt = stk_ary[ary_num];
                            if(oprt!=consOpt) return -999;
                        }
                    }
                    else {return -999;}
                }
            }

            if(next == -888 && oprt == -888){
            stk.push(first);}
            else{return -999;}
     }

    }




     int retval = -999;
    
      if(stk.top() < 0){
         return -999;}
    else{
        retval = stk.top();
        stk.pop();

        while(!stk.empty()){
        if(stk.top() == SHIFTRIGHT || stk.top()==SHIFTLEFT){
            if (stk.top() == SHIFTRIGHT){ retval = retval/2; stk.pop();}
            if (stk.top() == SHIFTLEFT){ retval = retval*2; stk.pop();}
        }
        else {
            return -999;}
        }
    }

    return retval;
}




int main(int argc, char* argv[]){

   if(argc < 2){
        cerr<<"Provide file name!"<<endl;
        return -1;
    }
    ifstream ifile (argv[1]);
    if (ifile.fail()){
        return -1;
    }
    char line[65535];
    ifile.getline(line, 65535);
    while(!ifile.fail()){
        string str(line);
        bool isFull = true;
        //start the stack stuff for one line
        for (size_t i = 0; i < str.size(); i++){
            if(str[i]!=' '&& str[i]!='\t'){
                isFull = false;
                break;
            }
        }
        if(!isFull){
       int result = 0;
       result = arithmeticParser(str);
       if (result < 0){
           cout<< "Malformed"<<endl;
       }
       else{
           cout<<result<<endl;
       }
    }
   //start of the next line 
    ifile.getline(line, 65535);}
    
   
return 0;}
