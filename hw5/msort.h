#include <vector>
#include <iostream>
#include <algorithm>

template <class T, class Comparator>
void Merge(std::vector <T>& myArray, const std::vector<int> indices,Comparator comp){
    std::vector<int> newindices;
    for (size_t i = 0; i < indices.size();i++){
        newindices.push_back(indices[i]);
    }
    std::vector <T> tmp;
   
    for (int t = 0; t < indices[indices.size()-1] - indices[0] ; t++){
        //keep track of the first element
        //and initiate the minimum to it
        //update after each round
        T min;
        bool findMin = false;
        size_t numGroup;

        for (size_t num = 0; num < newindices.size()-1; num++){
            if (newindices[num] < indices[num+1]){
                //initial a minimum number to compare
                //make sure it only runs once for finding one minimum
                if(!findMin){
                    min = myArray[newindices[num]+1];
                    numGroup = num;
                    findMin = true;
                }
                if (comp(myArray[newindices[num]+1],min))  
                {
                    numGroup = num;
                    min = myArray[newindices[num]+1];
                }
            }
        }
        tmp.push_back(min);
        newindices[numGroup] ++;
    }
    size_t j = 0;
    for (size_t i = indices[0]+1; i < indices[0]+1+tmp.size();i++){
        myArray[i] = tmp[j];
        j++;
    }
}


template <class T, class Comparator>
void mergeSortHelper(int r, int l, std::vector <T>& myArray, Comparator comp, int k){
     //base case
    if(r < l){
    size_t remaining = (l-r+1) %k;
    size_t num = (l-r+1)/k;
    std::vector<int> indices;
    indices.push_back(r-1);
    size_t j = 1;

    //totally I have k+1 indices
    //the first one is at index -1 and the lasts one is at index myArray.size()-1
    for (size_t i = 1; i <= (size_t)std::min(k, l-r+1); i++){
        if(j <= remaining)  indices.push_back(num + 1 + indices[i-1]);
        else    indices.push_back(num + indices[i-1]);
        j++;
    }

    for (size_t i = 0; i < (size_t)std::min(k, l-r+1); i++){
        mergeSortHelper(indices[i]+1, indices[i+1], myArray, comp, k);
    }
    Merge< T, Comparator>(myArray,indices,comp);
    }
}


template <class T, class Comparator>
void mergeSort (std::vector <T>& myArray, int k, Comparator comp){
    mergeSortHelper(0,myArray.size()-1,myArray,comp,k);
}
