#include "stackint.h"
#include "circular_list_int.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int OPEN_PAREN = -1;
const int CLOSE_PAREN = -2;
const int PLUS = -3;
const int MULTIPLY = -4;
const int SHIFTLEFT = -5;
const int SHIFTRIGHT = -6;
const int SPACE = -7;


int arithmeticParser(const string& line){
     StackInt stk;
    //convert any operator in the string into int
    int numAry[line.size()];
    //cerr << line.size()<<endl;
        for (size_t i = 0; i < line.size();i++){
            //if can't numAry.size
            //then change it back to line.size()
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
            else{
                //if there's other character in the line like &{[
                //what if there's a space between those stuffs
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
            int j = i+1;
            bool isTrue = true;
            while(isTrue){
                //if it is end of the string
                //then return false directly
                if(i == line.size()-1){
                    return -1;
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
                else{
                    //when </> is not followed by a number/</>
                    //return false
                    return -1;
                }
                j++;
            }
            //o represents the position of the last digit
            j--;
            int o = j;
            string strNum = "";
            strNum += char(numAry[o]) + '0'; //might have problem here
            //try to nest it into the string
            int pushValue;
            while (numAry[o+1] >= 0){
                //transfer it into a complete number
                strNum += char(numAry[o+1]) + '0';
                o++;
            }
            //the value that is gonna push into the stack
            pushValue = stoi(strNum);

            for (size_t count = j-1; count >= i; count--){
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

        //when meeting numbers
        else if (numAry[i] >= 0){
            int pushVal;
            string strNum = "";
            //add the number to the string
            strNum += char(numAry[i]) + '0';
            
            for (size_t count = i;count < line.size(); count++){
                if(numAry[count+1] >= 0){
                strNum += char(numAry[count+1]) + '0';
                i = count;}
                else{
                    break;
                }
                }
            
            pushVal = stoi(strNum);
            stk.push(pushVal);
        }

        //when meeting close paren
        else if (numAry[i] == CLOSE_PAREN){
           if(stk.empty()){return -999;}

           int stk_ary [100];//better solution?????????????
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
            //not sure about this
            //check more test cases

            //cases like (3) / (<3)
            if(count < 3){return -999;}
            int first = -888;
            int next = -888;
            int oprt = -888;
            //something like (+) or (*<) || ((12+12)(123+1))
            for (int ary_num = 0; ary_num < count; ary_num++){
                if(ary_num%2 == 0){
                    if(stk_ary[ary_num] < 0) {return -999;}
                    else {
                        if (first == -888) first = stk_ary[ary_num];
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
                        else {return -999;}//not really understand what i'm doing here
                    }

                }

                else if(ary_num%2 == 1){
                    if(stk_ary[ary_num] >= 0) {return -999;}
                    else if (stk_ary[ary_num] == PLUS || stk_ary[ary_num] == MULTIPLY){
                        oprt = stk_ary[ary_num];
                    }
                    else {return -999;}
                }
            }

            //add more restriction maybe
            stk.push(first);
     }

    }




     int retval = -999;
     if(stk.top() < 0){
         return false;}
    else{
        retval = stk.top();
        stk.pop();
        if(stk.empty()){
        }
        else{
            return -999;
        }
    }

   // cerr << "noway: ";
   // cerr << retval<<endl;
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
    char line[100];
    ifile.getline(line, 100);
    while(!ifile.fail()){
        string str(line);
        //start the stack stuff for one line
        if(str != ""){
       int result = 0;
       result = arithmeticParser(str);
     //  cerr << "RESULT!!: "<<result<<endl;
       if (result < 0){
           cout<< "Malformed"<<endl;
       }
       else{
           cout<<result<<endl;
       }
    }
   //start of the next line 
    ifile.getline(line, 100);}
    
   
return 0;}
