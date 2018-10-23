#include <iostream>
#include <vector>
#include <utility>

int compareHelper (std::pair<int,int> stu1, std::pair<int,int> stu2){
    if (stu1.first == stu2.first || stu1.second == stu2.second)     return true;
    else if (stu1.first > stu2.first){
        if (stu1.second < stu2.second)  return false;
    }
    else if (stu1.second > stu2.second){
        if (stu1.first < stu2.second)   return false;
    }
    return true;
}


void Merge(std::vector<std::pair<int,int>>& grades, int l, int r, int m){
    int i = l, j = m+1, k = 0;
    std::vector <std::pair<int,int>> temp;
    //for (int round = 0; round < r-l+1; round++){
    while (i <= m || j <= r){
        if (i <= m && (j > r || grades[i].first > grades[j].first)){
            temp.push_back(grades[i]);
            i++; k++;
        }
        else if (grades[i].first == grades[j].first){
            if (grades[i].second > grades[j].second){
                temp.push_back(grades[i]);
                i++; k++;
            }
            else{
                temp.push_back(grades[j]);
                j++; k++;
            }
        }
        else {
            temp.push_back(grades[j]);
            j++; k++;
        }
    }
    for (k = 0; k < r+1-l; k++) grades[k] = temp[k];
}

void MergeSort(std::vector<std::pair<int,int>>& grades , int l , int r) { 
    if (l < r) {
        int m= (l+r)/2;
        MergeSort(grades,l ,m);
        MergeSort(grades,m+1,r);
        Merge(grades,l,r,m);
    } 
}

bool FatalistHypothesis(std::vector<std::pair<int,int> > grades){
    MergeSort(grades, 0, grades.size()-1);
    for (int i = 0; i < (int)grades.size()-1; i++){
        if(!compareHelper(grades[i],grades[i+1])) return false;
    }
    return true;

}

