#include "Trie.h"

using namespace std;

int main(){
    TrieSet trie;
    trie.insert("node");
    trie.insert("no");
    trie.insert("children");

    trie.remove("children");

    TrieNode* tmp = trie.prefix("nod");
    if (tmp == NULL)    cout << "false" << endl;
    else    cout << "true" << endl;

    tmp = trie.prefix("children");
    if (tmp == NULL)    cout << "true" << endl;
    else    cout << "false" << endl;
    return 0;
}