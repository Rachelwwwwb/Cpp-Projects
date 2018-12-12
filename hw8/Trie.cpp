#include "Trie.h"
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

TrieSet::TrieSet (const std::string& Dictionary){
    head = this->createNew(NULL);
    std::ifstream dicStream(Dictionary);

    while (!dicStream.eof()){
        string word;
        dicStream >> word;
        this->insert(word);
    }
    

  }

TrieSet::~TrieSet (){
	if (head == NULL)	return;
	std::queue<TrieNode*> q;
	q.push(head);
	while (!q.empty()){
		head = q.front();
		q.pop();
		for (int i = 0; i < 26; i++){
            if (head->children[i] != NULL){
                q.push(head->children[i]);
            }
        }
		delete head;
		head = NULL;
	}

}

//create a new node and return it
//set parent and all children 
TrieNode* TrieSet::createNew(TrieNode* _parent){
    TrieNode* newNode = new TrieNode;
    newNode->parent = _parent;
    for (int i = 0; i < 26; i++){
        newNode->children[i] = NULL;
    }
    newNode->inSet = false;
    return newNode;
}

void TrieSet::insert (std::string input){
    TrieNode* tmp = head;
    for (size_t i = 0; i < input.size(); i++){
        input[i] = tolower(input[i]);
        int num = (int) input[i] - 'a';
        if (tmp->children[num] == NULL){
            tmp->children[num] = createNew(tmp);
        }
        tmp = tmp->children[num];
    }
    tmp->inSet = true;
}

void TrieSet::remove (std::string input){
   /* Removes this string from the set.
       Do nothing if the string is not already in the set. */
 TrieNode* curr = head;

 for(size_t i=0; i<input.length(); i++){
  if(curr->children[toupper(input[i]) - 'A'] != nullptr){
   curr = curr->children[toupper(input[i]) - 'A'];
  }
  else{
   //if not in set, then do nothing
   return;
  }
 }

 //if input is a prefix of a longer string
 for(int i=0; i<26; i++){
  if(curr->children[i] != nullptr){
   curr->inSet = false;
   return;
  }
 }

 TrieNode* end = curr;

 //if it is not a prefix, then trace back untill it's parent has more than 1 child
 while(curr != head && (curr == end || curr->inSet == false)){
  for(int i=0; i<26; i++){
   //if curr's parent has another child that's not curr
   if(curr->parent->children[i] != nullptr && curr->parent->children[i] != curr){
    //set parent's curr child to null
    for(int j=0; j<26; j++){
     if(curr->parent->children[j] == curr){
      curr->parent->children[j] = nullptr;
      break;
     }
    }
    //just delete curr and then return
    delete curr;
    return;
   }
  }

  //if curr is the only child, then delete curr, continue
  TrieNode* temp = curr;
  curr = curr->parent;

  //set parent's curr child to null
  for(int j=0; j<26; j++){
   if(curr->children[j] == temp){
    curr->children[j] = nullptr;
    break;
   }
  }
  delete temp;
 }
}
   

TrieNode* TrieSet::prefix(std::string px){
    if (px.size() == 0) return head;
    TrieNode* tmp = head;
    for (size_t i = 0; i < px.size(); i++){
        px[i] = tolower(px[i]);
        int num = (int) px[i] - 'a';
        if (tmp->children[num] == NULL){
            return NULL;
        }
        tmp = tmp->children[num];
    }
    return tmp;
}

