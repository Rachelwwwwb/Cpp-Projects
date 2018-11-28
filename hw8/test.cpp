#include "Trie.h"

using namespace std;

int main(){
    TrieSet trie("test.txt");

    TrieNode* tmp = trie.prefix("node");

    cout << tmp->inSet;


    TrieNode* tmp2 = trie.prefix("no");

    cout << tmp2->inSet;


    TrieNode* tmp3 = trie.prefix("");

    cout << tmp3->inSet;
    return 0;
}