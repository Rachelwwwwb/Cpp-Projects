#include <string>
#include <set>
#include <map>
#include <vector>
#include "Tile.h"
#include "Square.h"
#include "Move.h"
#include "Dictionary.h"
#include "Board.h"


	/* constructor that initializes the board state with an empty board
           and the size and bonuses and start square based on the given file. */
	Board::Board (std::string board_file_namey){

	std::ifstream boardFileStream(board_file_namey);

	if(!boardFileStream)
	{
		throw FileException("BOARD");
	}
    boardFileStream >> _columns >> _rows;
    boardFileStream >> _x >> _y;

    size_t numRow = 1;
	while(!boardFileStream.eof())
	{
	    vector<Square*> oneRow;
        string line;
        bool isStart = false;
        getline(boardFileStream,line);

        //inside a line (_x)
		for(size_t i = 1; i <= _columns; i++)
		{
			if (numRow == _y && i == _x) isStart = true;
            unsigned int LMult = 1;
            unsigned int WMult = 1;
            if (line[i-1] == '2' || line[i-1] == '3')   LMult = line[i-1] - '0';
            else if (line [i-1] == 'd') WMult = 2;
            else if (line [i-1] == 't') WMult = 3;
            oneSquare = new Square(LMult, WMult, isStart);
            oneRow.push_back(oneSquare);
            if(isStart)     _start = oneSquare;
		}
    numRow++;
    _board.push_back(oneRow);
    }

	~Board::Board (){
        for (size_t i = 0; i < _board.size();i++){
            for(std::vector<Square*>::iterator squareIter = _board[j].begin(); squareIter != _board[j].end(); ++squareIter)
	        {
		        delete *squareIter;
	        }
           
            //delete[] _board[j];
        }
    }

	/* returns a vector of all words that would be formed by executing the
           given move. The first element of the pair is a string containing the word
           formed, and the second element is the score that that word earns
           (with all multipliers, but not the 50-point bonus for all letters).

       Words returned are all in uppercase.

	   The last entry of the vector is always the "main" word formed
	   in the direction chosen by the user; the others could be in arbitrary
	   order. (This is helpful for backtracking search.)	*/
	   //bacier
	std::vector<std::pair<std::string, unsigned int>> Board::getPlaceMoveResults(const PlaceMove &m) const{
        size_t startX = m.getStartx();
        size_t startY = m.getStarty();
        bool horizontal = m.getDirection();
        bool isNextto = false;
        std::vector<Tile*> tileVector = m.tileVector();
        std::vector <std::pair<std::string, unsigned int>> words;
        

        //check if the 1st player starts at the START
        if (!_board[_x-1][_y-1]->isOccupied()){
            if (startX != _x || startY != _y){
                //throw exceptions
                throw length_error("START POSITION");
            }
        }


        //for each word  in the opposite direction
        for (size_t i  = 0; i < tileVector.size(); i++){
            //if at least one letter is next to something
            //if it is out of border
            //check if it is placing on an empty square
            
            //if it is horizontal:
            //check all the vertical words
            //(x-1+i,y-1)
            //one above: (x-1+i,y-2)

            //tons of corner cases
            int points = 0;;
            int wordMul = 1;
            string word = "";
            if (horizontal){
                //find the upper part of the word
                for ( size_t upperhalf = 1 ; startY-1-upperhalf >=0 ;upperhalf++){
                    if (!_board[startX-1+i][startY-1-upperhalf]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startX-1+i][startY-1-upperhalf]->getLMult()*_board[startX-1+i][startY-1-upperhalf]->getPoints();
                    wordMul *= _board[startX-1+i][startY-1-upperhalf]->getWMult();
                    word += _board[startX-1+i][startY-1-upperhalf]->getLetter();
                }
                    //As we read the word from up to down, we need to reverse the order of the first half;
                    reverse(word.begin(),word.end());
                    //add the letter we want to put here
                    word += tileVector[i]->getUse();

                //then check the lower part of the word
                for ( size_t lowerhalf = 1 ; startY-1+lowerhalf <= _rows-1 ;lowerhalf++){
                    if (!_board[startX-1+i][startY-1+lowerhalf]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startX-1+i][startY-1+lowerhalf]->getLMult()*_board[startX-1+i][startY-1+lowerhalf]->getPoints();
                    wordMul *= _board[startX-1+i][startY-1+lowerhalf]->getWMult();
                    word += _board[startX-1+i][startY-1-upperhalf]->getLetter();
                }
        
                if (string.size() > 1){
                    pair<string,int> aWord (word , points*wordMul);
                    words.push_back(aWord);
                }
            }

            //if vertical
            else{
                //As before, go left first
                 for (size_t leftHalf = 1 ; startX-1-leftHalf >=0 ;leftHalf++){
                    if (!_board[startX-1-leftHalf][startY-1+i]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startX-1-leftHalf][startY-1+i]->getLMult()*_board[startX-1-leftHalf][startY-1+i]->getPoints();
                    wordMul *= _board[startX-1-leftHalf][startY-1+i]->getWMult();
                    word += _board[startX-1-leftHalf][startY-1+i]->getLetter();
                }
                    //As we read the word from up to down, we need to reverse the order of the first half;
                    reverse(word.begin(),word.end());
                    //add the letter we want to put here
                    word += tileVector[i]->getUse();

                //then go to the right
                for (size_t rightHalf = 1 ; startY-1+rightHalf <= _columns-1 ;rightHalf++){
                    if (!_board[startX-1+i][startY-1+lowerhalf]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startX-1+rightHalf][startY-1+i]->getLMult()*_board[startX-1+rightHalf][startY-1+i]->getPoints();
                    wordMul *= _board[startX-1+rightHalf][startY-1+i]->getWMult();
                    word += _board[startX-1+rightHalf][startY-1+i]->getLetter();
                }
        
                if (string.size() > 1){
                    pair<string,int> aWord (word , points*wordMul);
                    words.push_back(aWord);
                }


            }

        }
        //check the dirc that the word is placing
        string mainWord = "";
        int point = 0;
        int wordMul = 1;
        if (horizontal){
            for (size_t leftSide = 1; startX-1-leftSide >= 0; leftSide++){
                if(!_board[startX-1-leftside][startY-1]->isOccupied())  break;

                isNextto = true;
                point += _board[startX-1-leftside][startY-1]->getLMult()*_board[startX-1-leftside][startY-1]->getPoints();
                wordMul *= _board[startX-1-leftside][startY-1]->getWMult();
                mainWord += _board[startX-1-leftside][startY-1]->getLetter();
            }

            //As we read the word from up to down, we need to reverse the order of the first half;
            reverse(word.begin(),word.end());
            //add all the letters we want to put here
            size_t occupied  = 0;
            for (size_t i = 0; i < tileVector.size();i++){
                size_t j = 0;
                while(_board[startX-1+i+occupied][startY-1]->isOccupied){
                isNextto = false;
                mainWord += _board[startX-1+i+occupied][startY-1]->getLetter();
                occupied++;
                }
                mainWord += tileVector[i]->getUse();
            }
            size_t tail = startX-1+tileVector.size()+occupied-1;
            if (tail > _columns-1) throw out_of_range ("OUT OF THE BOARD");

            for (size_t rightSide = 1; tail+rightSide <= _columns-1; rightSide++){
                if(!_board[tail+rightSide][startY-1]->isOccupied())  break;

                isNextto = true;
                point += _board[tail+rightSide][startY-1]->getLMult()*_board[tail+rightSide][startY-1]->getPoints();
                wordMul *= _board[tail+rightSide][startY-1]->getWMult();
                mainWord += _board[tail+rightSide][startY-1]->getLetter();
            }
        //the main word
        words.push_back(mainWord);
        }
        
        //if it is vertical
        else{
                //check the upper side first
                for (size_t upper = 1; startY-1-upper >= 0; upper++){
                if(!_board[startX-1][startY-1-upper]->isOccupied())  break;

                isNextto = true;
                point += _board[startX-1][startY-1-upper]->getLMult()*_board[startX-1][startY-1-upper]->getPoints();
                wordMul *= _board[startX-1][startY-1-upper]->getWMult();
                mainWord += _board[startX-1][startY-1-upper]->getLetter();
            }

            //As we read the word from up to down, we need to reverse the order of the first half;
            reverse(word.begin(),word.end());
            //add all the letters we want to put here
            size_t occupied  = 0;
            for (size_t i = 0; i < tileVector.size();i++){
                while(_board[startX-1][startY-1+i]->isOccupied){
                isNextto = false;
                mainWord += _board[startX-1][startY-1+i]->getLetter();
                occupied++;
                }
                mainWord += tileVector[i]->getUse();
            }
            size_t tail = startY-1+tileVector.size()+occupied-1;
            if (tail > _rows-1) throw out_of_range ("OUT OF THE BOARD");

            for (size_t below = 1; tail+below <= _rows-1; below++){
                if(!_board[startX-1][tail+below]->isOccupied())  break;

                isNextto = true;
                point += _board[startX-1][tail+below]->getLMult()*_board[startX-1][tail+below]->getPoints();
                wordMul *= _board[startX-1][tail+below]->getWMult();
                mainWord += _board[startX-1][tail+below]->getLetter();
            }
        //the main word
        words.push_back(mainWord);
        }
    }

	/* Executes the given move by taking tiles and placing them on the board.
	   This function does not check for correctness of the move, so could
	   segfault or cause other errors if called for an incorrect move.
	   When a blank tile '?' is placed on the board, it is treated as a letter,
	   i.e., the corresponding square has that letter (with score 0) placed on it.
	*/
	void Board::executePlaceMove (const PlaceMove & m){
        size_t startX = m.getStartx();
        size_t startY = m.getStarty();
        bool horizontal = m.getDirection();
        size_t occupiedNum = 0;
        std::vector<Tile*> tileVector = m.tileVector();
        for (size_t i = 0; i < m.tileVector.size();i++){
            if(horizontal){
                while(_board[startX-1+i+occupiedNum][startY-1]->isOccupied()){
                    occupiedNum ++;
                }
                _board[startX-1+i+occupiedNum][startY-1]->placeTile(tileVector[i]);
            }
            
            else{
                while(_board[startX-1][startY-1+i+occupiedNum]->isOccupied()){
                    occupiedNum ++;
                }
                _board[startX-1+i+occupiedNum][startY-1]->placeTile(tileVector[i]);
            }
        }


    }

	/* Returns a pointer to the Square object representing the
       (y,x) position of the board. Indexing starts at 1 here.
	   This is needed only to display the board. */
	Square * Board::getSquare (size_t x, size_t y) const{
        return _board[x-1][y-1];
    }

	/* Returns the number of rows of the board.*/
	size_t Board::getRows() const{
        return _rows;
    }

	/* Returns the number of columns of the board.*/
	size_t Board::getColumns() const{
        return columns;
    }


