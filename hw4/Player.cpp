#include <string>
#include <set>
#include <vector>
#include <iostream>

#include "Tile.h"
#include "Player.h"

using namespace std;


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
        for(std::vector<Tile*>::iterator tileIter = _tilesOnHand.begin(); tileIter != _tilesOnHand.end(); ++tileIter){
		delete *tileIter;
		}
	}

	/* Returns the set of tiles the player currently holds. */
    //set cannot store repeat stuff
	std::set<Tile*> Player::getHandTiles() const{
        std::set<Tile*> handTiles;
        for (size_t i = 0; i < _tilesOnHand.size();i++){
            handTiles.insert(_tilesOnHand[i]);
        }
    return handTiles;
    }

	void Player::showHand(){
		cout << "_tilesOnHand.size" << _tilesOnHand.size()<<endl;
		for (size_t i = 0; i < _tilesOnHand.size();i++){
			cout << _tilesOnHand[i]->getLetter()<<endl;
		}
	}

	//"move" is string of char that the player wish to move
	//check to see if the player has all the letters (num and letter)
	//if resolve blanks is true
		//set '?' if it has one (use useAs(char))
	//if false, then the string is the letters need to be exchanged
	//if all goes good, push them to the vector ready to move
	bool Player::hasTiles(std::string const & move, bool resolveBlanks) const{
	
        bool hasLetter = false;
		//create a copy of move
		string movecpy = move;
		std::vector<Tile*> copyOfHand = _tilesOnHand;

        for (size_t i = 0; i < movecpy.size();i++){

				//if it is a '?'
				//when there's a '?' and the move is place
				if(resolveBlanks && movecpy[i] == '?'){
				if (i+1 >= movecpy.size()) return false;
				else if(movecpy[i+1] == '?') return false;
				else{ // take away the letter behind it
					std::string firsthalf, secondhalf;
					firsthalf = movecpy.substr(0,(int)i+1);
					secondhalf = movecpy.substr((int)i+3, movecpy.size()-(int)i-2);
					movecpy = firsthalf + secondhalf;
				}
				}

            size_t j = 0;
            while (!hasLetter && j < copyOfHand.size()){
                if(tolower(movecpy[i]) == tolower(copyOfHand[j]->getLetter())){
                    copyOfHand.erase(copyOfHand.begin()+j);
					hasLetter = true; 
                }
				else if (toupper (movecpy[i]) == toupper (copyOfHand[j]->getLetter())){
                    copyOfHand.erase(copyOfHand.begin()+j);
					hasLetter = true; 
                }
                else if (j == copyOfHand.size()-1 && movecpy[i]!= copyOfHand[j]->getLetter()){
                    return false;
                }
                j++;
            }
		
        }
	return true;
        
    }



	std::vector<Tile*> Player::takeTiles (std::string const & move, bool resolveBlanks){
		
		for (size_t i = 0; i < move.size();i++){
			char actualUse;
			string movecpy = move;

			if(movecpy[i] == '?' && resolveBlanks == true){
					std::string firsthalf, secondhalf;
					actualUse = movecpy[i+1];
					firsthalf = movecpy.substr(0,(int)i+1);
					secondhalf = movecpy.substr((int)i+3, movecpy.size()-(int)i-2);
					movecpy = firsthalf + secondhalf;
			}
		
			size_t j = 0;
			bool hasLetter = false;
        	while (!hasLetter && j < _tilesOnHand.size()){
                if(toupper(movecpy[i]) == toupper(_tilesOnHand[j]->getLetter())){
                    hasLetter = true; 
					if(resolveBlanks && movecpy[i] == '?'){
					_tilesOnHand[j]->useAs(actualUse);
					}
				
				cout <<i<<": "<< _tilesOnHand[j]->getLetter()<<endl;
				//push it to the toMOve and delete the tile
				_toMove.push_back(_tilesOnHand[j]);
				//delete _tilesOnHand[j];//may have some problems
				_tilesOnHand.erase(_tilesOnHand.begin()+j);

				}
                
                j++;
        	}
		}
	return _toMove;

	}

	// Adds all the tiles in the vector to the player's hand.
	void Player::addTiles (std::vector<Tile*> const & tilesToAdd){
		for (size_t i = 0; i < tilesToAdd.size();i++){
		_tilesOnHand.push_back(tilesToAdd[i]);
		/*char letter = tilesToAdd[i]->getLetter();
		letter = toupper(letter);
		_tilesOnHand.push_back(new Tile(letter,tilesToAdd[i]->getPoints()));*/
		}
	}

	//Add more public/protected/private functions/variables here.
	void Player::addScore (int num){
        _score += num;
    }


	size_t Player::getMaxTiles () const{
		return _maxTiles;
	}

