#include <vector>
#include <string>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Move.h"
#include "Board.h"

using namespace std;


	 Move * Move::parseMove(std::string moveString, Player &p){
		for (size_t i = 0; i < moveString.size();i++){
			moveString[i] = toupper(moveString[i]);
		}
		if(moveString == "PASS"){
			Move *pass = new PassMove(&p);
			return pass;
		}

		else if (moveString.substr(0,8) == "EXCHANGE"){
			Move * exchange = new ExchangeMove(moveString.substr(9,moveString.size()-9), &p);
			return exchange;
		}

		else if (moveString.substr(0,5) == "PLACE"){
			bool horizontal = true;
			if (moveString[6] == '-') horizontal = true;
			else if (moveString[6] == '|') horizontal = false;

			Move* Place = new PlaceMove(moveString[8]-'0',moveString[10]-'0',horizontal,moveString.substr(12,moveString.size()-12),&p);
			return Place;
		}
	}


	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	 Move::~Move(){return;}
	//Add more public/protected/private functions/variables here.

	Move::Move(Player * player){
		_player = player;
	}


	/* Constructs a pass move. */
	PassMove::PassMove(Player * player) : Move(player){
		_player = player;
	}

	void PassMove::execute(Board & board, Bag & bag, Dictionary & dictionary){
		return;
	}
	
	




	/* Creates an EXCHANGE move, exchanging the tiles listed in the
	   string (formatted according to the EXCHANGE command description)
	   with new tiles from the bag.
	   */
	ExchangeMove::ExchangeMove(std::string tileString, Player * p):Move(p){
		_tileString = tileString;
		_player = p;
	}



	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	void ExchangeMove::execute(Board & board, Bag & bag, Dictionary & dictionary){
		if (bag.tilesRemaining() < _tileString.size()){
			//throw exceptions here
			//and some warnings here	
		}
		if (_player->hasTiles(_tileString,false)){
			//put the tiles back in
			std::vector<Tile*> toPutBack = _player->takeTiles(_tileString,false);
			bag.addTiles(toPutBack);
			//check whether bag is put back
			_toAdd = bag.drawTiles((size_t)_tileString.size());
			_player->addTiles(_toAdd);
		}

	}

	string ExchangeMove::newLetterPicked(){
		string toAdd = "";
		for (size_t i = 0; i < _toAdd.size(); i++){
			toAdd += _toAdd[i]->getLetter();
		}
		return toAdd;
	}




	PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p) : Move(p){
		_x = x;
		_y = y;
		_horizontal = horizontal;
		_player = p; 
		_tileString = tileString;
	}
	//check if the square is empty; else throw exceptions
	//check if the string is next to at least one letter
	//maybe not here but check if the words are legal
	//if anything is wrong, ask the user again and choose among three moves again
	//which means need to going back to the move class
	//check if it is the beginner player

	std::vector<Tile*> const & PlaceMove::tileVector () const{
		if(_player->hasTiles(_tileString,true)){
			std::vector<Tile*> retval = _player->takeTiles(_tileString,true);
			return retval;
		}
	}

	size_t PlaceMove::getStartx() const{
		return _x;
	}

	size_t PlaceMove::getStarty() const{
		return _y;
	}
	bool PlaceMove::getDirection() const{
		return _horizontal;
	}

	void PlaceMove::execute(Board & board, Bag & bag, Dictionary & dictionary){
		//check if physically feasible
		vector<pair<std::string, unsigned int>> words = board.getPlaceMoveResults(*this);
		vector<string> toCheck;
		for (size_t i = 0; i < words.size(); i++){
			toCheck.push_back(words[i].first);
		}
		for (size_t i = 0; i < toCheck.size(); i++){
			if(!dictionary.isLegalWord(toCheck[i])){
				throw invalid_argument ("ILLEGAL WORD");
			}
		}
		board.executePlaceMove(PlaceMove(_x,_y,_horizontal,_tileString,_player));
		_toAdd = bag.drawTiles((size_t)_tileString.size());
		_player->addTiles(_toAdd);
		

	}