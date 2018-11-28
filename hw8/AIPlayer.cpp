#include "Player.h"
#include "AIPlayer.h"
#include "Board.h"
#include "Tile.h"
#include "Move.h"
#include "Trie.h"

#include <string>
#include <vector>
#include <set>

using namespace std;

AIPlayer::AIPlayer(bool isCPUS){
        _lettersOnHand = "";
        _isCPUS = isCPUS;
}
AIPlayer::~AIPlayer();


void AIPlayer::permutationHelper(const string& letters, size_t n, string curr,vector<string>& collection)
{
        if(n == curr.size()){
        collection.push_back(curr);  
        }
        else {
            for(unsigned int i=0; i < letters.size(); i++){
            string tmp = letters.substr(0,i) + letters.substr(i+1, letters.size()-i-1);
            if (letters[i] != '?')
            permutationHelper(tmp, n, curr+letters[i], collection);  
            }
            else{
            for (int j = 0; j < 26; j++)
            permutationHelper(tmp, n, curr+(char) j + 'a', collection);     
            }
        }
}

    //get all the possible permutations of words given the tiles on hand
std::vector<std::string> AIPlayer::getPermutations(Player& p){
    bool hasQuest = false;
    set<Tile*> handTile;
    handTile = p.getHandTiles();
    for (set<Tile*>::iterator it = handTile.begin();it != handTile.end(); ++it){
        _lettersOnHand += *it->getLetter();
        if (*it->getLetter() == '?')   hasQuest = true;
    }

    //where should I set the use of '?'
    //????????????????????????????????????????????
    for (int questUse = 0; questUse < 26; questUse++){
        _
        for (int i = 1; i <= _lettersOnHand.size(); i++){
            permutationHelper(_lettersOnHand,i,"", permutations);
        }
    }
    
    //check if there's a '?' in use
    //some repetition in it
    if (hasQuest){
        for (size_t i = 0; i < permutations.size();i++){
            for (size_t j = 0; j < permutations[i].size();j++){
                if (permutations[i][j] == '?'){
                    for (int letter = 0; letter < 26; letter++){
                        permutations[i][j] = permutations[i].substr(0,j+1) + char(letter+'a') + permutations[i].substr(j+1,permutations[i].size()-j);
                        permutations.push_back(permutations[i]);
                    }
                    permutations.erase(permutations.begin()+i);
                    i--;
                    break;
                }
            }
        }
    }
return permutations;

}


    Move* AIPlayer::getMove(Board & board, Dictionary & dictionary, Player& p,TrieSet& trie){

        //try all the squares and all the permutations on board
        //make sure at least the main word is legal
        //push them in the vector of legalMoves
        for (size_t y = 0; y < board.getRows();y++){
            for (size_t x = 0; x < board.getColumns(); x++){
                //if the square is occupied, go to the next one
                if(board.getSquare(x,y)->isOccupied())  continue;
                for (int i = 0; i < permutations.size();i++){
                    //no rush to create, first check first at least one word is formed
                    //hepler function in board
                    bool horizontal = board.checkHorizontal(x,y, permutations[i],trie);
                    if (horizontal){
                    PlaceMove* h = new PlaceMove (x,y,true,permutations[i],p)
                    legalMoves.push_back(h);
                    }

                    bool vertical = board.checkVertical(x,y,permutations[i],trie);
                    if (vertical){
                    PlaceMove* v = new PlaceMove (x,y,false,permutations[i],p);
                    legalMoves.push_back(v);
                    }
                }
            }
        }
        int highest_score = 0;
        size_t longest_word = 0;
        PlaceMove* highest = NULL;
        PlaceMove* longest = NULL;

        for(int i = 0; i < legalMove.size(); i++){
            bool legal = true;
            try{
            legalMove[i]->allLegal();
            }
            catch(exception &e){
                legal = false;
            }
            if(legal){
                if (legalMove[i]->getNewScore() > highest_score) highest = legalMove[i];
                if (legalMove[i]->getTrueSize() > longest_word) longest = legalMove[i];
            }
        }

        if (_isCPUS){
            if (highest != NULL)    
            return highest;
        }
        else{
            if (longest != NULL)
            return longest;
        }
        
        return new PassMove(p);

    }


bool AIPlayer::isCPUS() const{
        return _isCPUS;
}


};