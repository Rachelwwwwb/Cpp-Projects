#include <vector>
#include <iostream>
#include <algorithm>

template <class T, class Comparator>
Merge(std::vector <T>& myArray, int l, int r, int*k){
    
}


template <class T, class Comparator>
void mergeSortHelper(int l, int r, std::vector <T>& myArray, Comparator comp, int k){
     //base case
    if(l >= r) return;

    int remaining = (r-l+1) %k;
    int num = (r-l+1)/k;
    int* indices;
    indices[0] = l-1;
    size_t j = 1;

    //totally I have k+1 indices
    //the first one is at index -1 and the last one is at index myArray.size()-1
    for (size_t i = 1; i <= min(k, r-l+1); i++){
        if(j <= remaining)  indices[i] = num + 1 + indices[i-1];
        else    indices[i] = num + indices[i-1];
        j++;
    }

    for (size_t i = 0; i < min(k, r-l+1); i++){
        mergeSortHelper(indices[i]+1, indices[i+1], myArray, comp, k);
    }


}


template <class T, class Comparator>
void mergeSort (std::vector <T>& myArray, int k, Comparator comp){
    mergeSortHelper(0,myArray.size()-1,comp,k);
    

}
