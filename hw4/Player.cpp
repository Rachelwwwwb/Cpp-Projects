#include <string>
#include <set>
#include <vector>

#include "Tile.h"
#include "Player.h"


	/* Constructor giving the player the given name, and setting their points to 0.
	   Does not give the player any tiles.
	*/
	Player::Player (std::string const & name, size_t maxTiles){
    _name = name;
	_maxTiles = maxTiles;
	_score = 0;
    }

	/* Destructor for a player. Deletes all the tiles the player still has. */
	Player::~Player (){
        for(std::vector<Tile*>::iterator tileIter = _tilesOnHand.begin(); tileIter != _tilesOnHand.end(); ++tileIter)
	{
		delete *tileIter;
	}
}

	/* Returns the set of tiles the player currently holds. */
    //set cannot store repeat stuff
	std::set<Tile*> Player::getHandTiles() const{
        std::set<Tile*> handTiles;
        for (size_t i = 0; i < _tilesOnHand.size();i++){
            handTiles.insert(handTiles.at(i));
        }
    return handTiles;
    }

	/* Reads a move string and confirms that the player has the tiles necessary to
	   execute this move.

	   The move string is case-insensitive.

	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as.

	   By definition, if this function returns true, then takeTiles() would
	   succeed.
	 */
	//"move" is string of char that the player wish to move
	//check to see if the player has all the letters (num and letter)
	//if resolve blanks is true
		//set '?' if it has one (use useAs(char))
	//if false, then the string is the letters need to be exchanged
	//if all goes good, push them to the vector ready to move
	bool hasTiles(std::string const & move, bool resolveBlanks) const{
	
        bool hasLetter = false;
        for (size_t i = 0; i < move.size();i++){

				//when there's a '?' and the move is place
				if(resolveBlanks && move[i] == '?'){
				if (i+1 >= move.size()) return false;
				else if(move[i+1] == '?') return false;
				else{ // take away the letter behind it
					std::string firsthalf, secondhalf;
					char actualUse = move [i+1];
					firsthalf = move.substr(0,(int)i+1);
					secondhalf = move.substr((int)i+3, move.size()-(int)i-2);
					move = firsthalf + secondhalf;
				}
			}

            size_t j = 0;
            while (!hasLetter && j < _tilesOnHand.size())){
                if(move[i] == _tilesOnHand.at(j)->getLetter()){
                    hasLetter = true;
					if(resolveBlanks && move[i] == '?'){
						_tilesOnHand[j]->useAs(actualUse);
					}
					//push it to the toMOve and delete the tile
					_toMove.push_back(_tilesOnHand.at(j));
					delete _tilesOnHand.at(i);//may have some problems
					_tilesOnHand.erase(j). 
                }
                else if(j = _tilesOnHand.size()-1 && move[i]!= _tilesOnHand.at(j)->getLetter()){
                    return false;
                }
                j++;
            }
		
		return true;
        }
        
    }


	/* Reads a move string, finds the corresponding tiles in the player's hand, and
	   removes and returns those tiles in the order they appear in the move string.

	   The move string is case-insensitive.

	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as,
	   and the "use" field of the tile is set accordingly.

	   The move string is assumed to have correct syntax.
	*/
	std::vector<Tile*> takeTiles (std::string const & move, bool resolveBlanks){
		return _toMove;

	}

	// Adds all the tiles in the vector to the player's hand.
	void addTiles (std::vector<Tile*> const & tilesToAdd){
		for (int i = 0; i < tilesToAdd.size();i++){
		_tilesOnHand.push_back(tilesToAdd.at(i));
		}
	}

	//Add more public/protected/private functions/variables here.
	void Player::addScore (int num){
        _score += num;
    }

};


