#include "Player.h"
#include "AIPlayer.h"
#include "Board.h"
#include "Tile.h"
#include "Move.h"
#include "Trie.h"

#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

AIPlayer::AIPlayer(bool isCPUS){
        _lettersOnHand = "";
        _isCPUS = isCPUS;
}
AIPlayer::~AIPlayer(){
    for(int i = 0; i < (int)legalMoves.size();i++){
        delete legalMoves[i];
    }
}

    string AIPlayer::getMove(Board & board, Dictionary & dictionary, Player& p,TrieSet& trie){
  
        //try all the squares and all the permutations on board
        //make sure at least the main word is legal
        //push them in the vector of legalMoves
        set<Tile*> handTile;
        handTile = p.getHandTiles();
        for (set<Tile*>::iterator it = handTile.begin();it != handTile.end(); ++it){
            _lettersOnHand += (*it)->getLetter();
        }
        for (size_t y = 0; y < board.getRows();y++){
            for (size_t x = 0; x < board.getColumns(); x++){
            board.checkHorizontal(x,y,x,y,"","", _lettersOnHand,legalMoves,trie,NULL,&p);
            board.checkVertical(x,y,x,y,"","", _lettersOnHand,legalMoves,trie,NULL,&p);
            }
        }

        int highest_score = 0;
        size_t longest_word = 0;
        PlaceMove* highest = NULL;
        PlaceMove* longest = NULL;

        for(int i = 0; i < (int)legalMoves.size(); i++){
            bool legal = true;
            try{
            legalMoves[i]->allLegal(board,dictionary); 
            }
            catch(exception &e){
                legal = false;
            }
            if(legal){
                if (legalMoves[i]->getNewScore() > highest_score){
                highest = legalMoves[i];
                highest_score = legalMoves[i]->getNewScore();}
                if (legalMoves[i]->getTrueSize() > longest_word){
                longest_word = legalMoves[i]->getTrueSize();
                longest = legalMoves[i];
                }
            }
        }
        
        string retval;
        if (_isCPUS){
            if (highest != NULL){ 
            string direction;  
            if (highest->getDirection())    direction = " - ";
            if (!highest->getDirection())   direction = " | ";
            retval = "PLACE" + direction+ to_string((int)highest->getStarty()) + " "+to_string((int)highest->getStartx()) + " " + highest->getTileString();
            return retval;
            }
        }
        else{
            if (longest != NULL){
            string direction;  
            if (longest->getDirection())    direction = " - ";
            if (!longest->getDirection())   direction = " | ";
            retval = "PLACE" +direction+ to_string((int)longest->getStarty()) + " "+to_string((int)longest->getStartx()) + " " + longest->getTileString();
            return retval;
            }
        }
        
        return "pass";

    }


bool AIPlayer::isCPUS() const{
        return _isCPUS;
}
