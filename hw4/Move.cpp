#include <vector>
#include <string>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Move.h"


	static Move * Move::parseMove(std::string moveString, Player &p){
		_player = p;
		for (int i = 0; i < moveString.size();i++){
			moveString[i] = tolower(moveString[i]);
		}
		if(moveString == "pass"){
			return PassMove(p);
		}
		else if (moveString == "exchange"){
			return ExchangeMove(moveString,p);
		}
		else if (moveString == "place"){
			return PlaceMove();//how to initiate it?
			//PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p);

		}
	}


	/* Returns true iff the move is a PASS move */
	virtual bool Move::isPass () const
	{
		return false;
	}

	/* Returns true iff the move is an EXCHANGE move */
	virtual bool Move::isExchange () const
	{
		return false;
	}

	/* Returns true iff the move is a PLACE move */
	virtual bool Move::isWord () const
	{
		return false;
	}

	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	virtual void Move::execute(Board & board, Bag & bag, Dictionary & dictionary) = 0;

	virtual ~Move::Move();

	//Add more public/protected/private functions/variables here.




	/* Constructs a pass move. */
	PassMove::PassMove(Player * player){
		_player = p;
	}

	/* Returns true iff the move is a PASS move */
	bool PassMove::isPass () const
	{
		return true;
	}

	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	   //add an index or bool variable to show that this player has passed
	   //so that when all players pass we can end the game
	void PassMove::execute(Board & board, Bag & bag, Dictionary & dictionary);
	
	
	//Add more public/protected/private functions/variables here.




	/* Creates an EXCHANGE move, exchanging the tiles listed in the
	   string (formatted according to the EXCHANGE command description)
	   with new tiles from the bag.
	   */
	ExchangeMove::ExchangeMove(std::string tileString, Player * p){
		_tileString = tileString;
		_player = p;
	}

	/* Returns true iff the move is an EXCHANGE move */
	bool ExchangeMove::isExchange () const
	{
		return true;
	}

	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	void ExchangeMove::execute(Board & board, Bag & bag, Dictionary & dictionary){
		if (bag.tilesRemaining() < _tileString.size()){
			//throw exceptions here
			//and some warnings here	
		}
		if (_player.hasTiles(_tileString,false)){
			//put the tiles back in
			std::vector<Tile*> toPutBack = _player.takeTiles(_tileString,false);
			bag.addTiles(toPutBack);
			std::vector<Tile*> toAdd = bag.drawTiles((size_t)_tileString.size());
			_player.addTiles(toAdd);
		}




public:
	/* Creates a PLACE move, starting at row y, column x, placing the tiles
	   described by the string tileString. If "horizontal" is true, then the tiles
	   are placed horizontally, otherwise vertically.
	   Coordinates start with 1.
	   The string m is in the format described in HW4; in particular, a '?'
	   must be followed by the letter it is to be used as.
	*/
	PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p){
		_x = x;
		_y = y;
		_horizontal = horizontal;
		_player = p; 
		_tileString = tileString
	}
	//check if the square is empty; else throw exceptions
	//check if the string is next to at least one letter
	//maybe not here but check if the words are legal
	//if anything is wrong, ask the user again and choose among three moves again
	//which means need to going back to the move class
	//check if it is the beginner player

	/* Returns true iff the move is a PLACE move */
	bool PlaceMove::isWord () const
	{
		return true;
	}

	/* Returns the vector of tiles associated with a PLACE/EXCHANGE move.
	   Return value could be arbitrary for PASS moves. */
	std::vector<Tile*> const & PlaceMove::tileVector () const{
		if(_player.hasTiles(_tileString,true)){
			return _player.takeTiles(_tileString,true);
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

	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	void PlaceMove::execute(Board & board, Bag & bag, Dictionary & dictionary){}
//check if physically feasible
//board bacier
//	std::vector<std::pair<std::string, unsigned int>> getPlaceMoveResults(const PlaceMove &m) const;
//dictionary
//	bool isLegalWord (std::string const & word) const;
//board put words
//	void executePlaceMove (const PlaceMove & m);
//every word has to be used


	//Add more public/protected/private functions/variables here.
	
	//maybe bool horizontal???
private:
string _tileString;
size_t _x;
size_t _y;
bool _horizontal;

