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
    std::string getMove(Board & board, Dictionary & dictionary, Player& p,TrieSet& trie);
    bool isCPUS() const;


private:
    std::string _lettersOnHand;
    std::vector<PlaceMove*> legalMoves;
    bool _isCPUS;
};
