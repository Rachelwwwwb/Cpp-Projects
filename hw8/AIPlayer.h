#include "Player.h"
#include "Move.h"
#include "Board.h"
#include "Trie.h"

#include <string>
#include <vector>

class AIPlayer
{
public:
    AIPlayer(bool isCPUS);
    ~AIPlayer();
    //get all the possible permutations of words given the tiles on hand
    void permutationHelper(const string& letters, size_t n, string curr,vector<string>& collection);
    std::vector<std::string> getPermutations(Player& p);
    void setLongest(size_t size);
    size_t getLongest() const;
    Move* getMove(Board & board, Dictionary & dictionary, Player& p,TrieSet& trie);
    bool isCPUS() const;


private:
    std::string _lettersOnHand;
    std::vector<PlaceMove*> legalMoves;
    std::vector<std::string> permutations;
    bool _isCPUS;
};
