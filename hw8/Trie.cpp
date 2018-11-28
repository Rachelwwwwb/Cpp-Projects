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
    TrieNode* end = this->prefix(input);
    if (end == NULL)    return;
    for (int i = input.size()-1; i >= 0; i--){
        input[i] = tolower(input[i]);
        int num = (int) input[i] - 'a';
        TrieNode* tmp = end->parent;
        delete end->children[i];
        tmp->children[num] = NULL;

        if (tmp == head)    return;
        //check if the deleted word is the only children
        for (int j = 0; j < 26; j++){
            if (tmp->children[j] != NULL)   return;
        }
        //else if all the children of tmp is NULL
        //continue deleting tmp
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

