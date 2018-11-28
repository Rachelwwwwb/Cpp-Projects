/*
 * Board.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

/* The class Board encodes the state of the Scrabble board.
   It provides functions for displaying the board,
   and for returning the words (and score) that would be obtained by a move.
*/

#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include <set>
#include <map>
#include <vector>
#include "Tile.h"
#include "Square.h"
#include "Move.h"
#include "Dictionary.h"
#include "Trie.h"

class Board
{
	
public:
	/* constructor that initializes the board state with an empty board
           and the size and bonuses and start square based on the given file. */
	Board (std::string board_file_namey);

	~Board ();

	std::vector<std::pair<std::string, unsigned int>> getPlaceMoveResults(const PlaceMove &m) const;

	void executePlaceMove (const PlaceMove & m);

	Square * getSquare (size_t x, size_t y) const;

	/* Returns the number of rows of the board.*/
	size_t getRows() const;

	/* Returns the number of columns of the board.*/
	size_t getColumns() const;

	void getInitial(std::string inifile);

	bool checkLegalMove(const PlaceMove& m);

	bool checkHorizontal(size_t x, size_t y, std::string word,TrieSet& trie);

	bool checkVertical(size_t x, size_t y, std::string word,TrieSet& trie);
	
private:
size_t _rows;
size_t _columns;
size_t _x;
size_t _y;
std::vector<std::vector<Square*>> _board;


};


#endif /* BOARD_H_ */
