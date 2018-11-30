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
    void setLongest(size_t size);
    size_t getLongest() const;
    std::string getMove(Board & board, Dictionary & dictionary, Player& p,TrieSet& trie);
    bool isCPUS() const;


private:
    std::string _lettersOnHand;
    std::vector<PlaceMove*> legalMoves;
    std::vector<std::string> _permutations;
    bool _isCPUS;
};
