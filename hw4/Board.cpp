#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <exception>
#include "exception"
#include "Tile.h"
#include "Square.h"
#include "Move.h"
#include "Dictionary.h"
#include "Board.h"

using namespace std;

	/* constructor that initializes the board state with an empty board
           and the size and bonuses and start square based on the given file. */
	Board::Board (std::string board_file_namey){

	std::ifstream boardFileStream(board_file_namey);

	if(!boardFileStream)
	{
	   // throw FileException("BOARD");
	}
    boardFileStream >> _columns >> _rows;
    boardFileStream >> _x >> _y;

    size_t numRow = 1;
	while(!boardFileStream.eof())
	{
	    vector<Square*> oneRow;
        string line;
        getline(boardFileStream,line);

        //inside a line (_x)
        if (line != ""){
		for(size_t i = 1; i <= _columns; i++){
            bool isStart = false;
			if (numRow == _y && i == _x) isStart = true;
            unsigned int LMult = 1;
            unsigned int WMult = 1;
            if (line[i-1] == '2') LMult = 2;
            else if (line[i-1] == '3') LMult = 3;
            else if (line [i-1] == 'd') WMult = 2;
            else if (line [i-1] == 't') WMult = 3;
            Square* oneSquare = new Square(LMult, WMult, isStart);
            oneRow.push_back(oneSquare);
           // if(isStart)     _start = oneSquare;
		}
        numRow++;
        _board.push_back(oneRow);
    }
    }

   
    }

    void Board::printBoard() const{
        for (size_t i = 0; i < _board.size();i++){
        for (size_t j = 0; j < _board[i].size();j++){
            cout << _board[i][j] -> getLMult();
        }
        cout << endl;
    }
    }


	Board::~Board (){
        for (size_t i = 0; i < _board.size();i++){
            for(std::vector<Square*>::iterator squareIter = _board[i].begin(); squareIter != _board[i].end(); ++squareIter){
		        delete *squareIter;
	        }
           
        }
    }


	std::vector<std::pair<std::string, unsigned int>> Board::getPlaceMoveResults(const PlaceMove &m) const{
        size_t startX = m.getStartx();
        size_t startY = m.getStarty();
        bool horizontal = m.getDirection();
        bool isNextto = false;
        std::vector<Tile*> tileVector = m.tileVector();
        cerr << "size of tileVector in Board.cpp: "<< tileVector.size() << endl;
        std::vector <std::pair<std::string, unsigned int>> words;
        

        //check if the 1st player starts at the START
        if (!_board[_x-1][_y-1]->isOccupied()){
            if (startX != _x || startY != _y){
                //throw exceptions
                throw domain_error ("START POSITION");
            }
            else{
                isNextto = true;
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
                    if (startX-1+i<0 && startY-1-upperhalf < 0) break;
                    if (!_board[startX-1+i][startY-1-upperhalf]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startX-1+i][startY-1-upperhalf]->getLMult()*_board[startX-1+i][startY-1-upperhalf]->getScore();
                    wordMul *= _board[startX-1+i][startY-1-upperhalf]->getWMult();
                    word += _board[startX-1+i][startY-1-upperhalf]->getLetter();
                }
                    //As we read the word from up to down, we need to reverse the order of the first half;
                    reverse(word.begin(),word.end());
                    //add the letter we want to put here
                    word += tileVector[i]->getUse();

                //then check the lower part of the word
                for ( size_t lowerhalf = 1 ; startY-1+lowerhalf <= _rows-1 ;lowerhalf++){
                    if (startY-1+lowerhalf > _rows-1) break;
                    if (!_board[startX-1+i][startY-1+lowerhalf]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startX-1+i][startY-1+lowerhalf]->getLMult()*_board[startX-1+i][startY-1+lowerhalf]->getScore();
                    wordMul *= _board[startX-1+i][startY-1+lowerhalf]->getWMult();
                    word += _board[startX-1+i][startY-1-lowerhalf]->getLetter();
                }
        
                if (word.size() > 1){
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
                    points += _board[startX-1-leftHalf][startY-1+i]->getLMult()*_board[startX-1-leftHalf][startY-1+i]->getScore();
                    wordMul *= _board[startX-1-leftHalf][startY-1+i]->getWMult();
                    word += _board[startX-1-leftHalf][startY-1+i]->getLetter();
                }
                    //As we read the word from up to down, we need to reverse the order of the first half;
                    reverse(word.begin(),word.end());
                    //add the letter we want to put here
                    word += tileVector[i]->getUse();

                //then go to the right
                for (size_t rightHalf = 1 ; startY-1+rightHalf <= _columns-1 ;rightHalf++){
                    if (!_board[startX-1+i][startY-1+rightHalf]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startX-1+rightHalf][startY-1+i]->getLMult()*_board[startX-1+rightHalf][startY-1+i]->getScore();
                    wordMul *= _board[startX-1+rightHalf][startY-1+i]->getWMult();
                    word += _board[startX-1+rightHalf][startY-1+i]->getLetter();
                }
        
                if (word.size() > 1){
                    pair<string,int> aWord (word , points*wordMul);
                    words.push_back(aWord);
                }


            }
            if(!isNextto){
                throw range_error ("Not NEXT TO SOME LETTER");
            }
            

        }
        //check the dirc that the word is placing
        string mainWord = "";
        int point = 0;
        int wordMul = 1;
        if (horizontal){
            for (size_t leftSide = 1; startX-1-leftSide >= 0; leftSide++){
                if(!_board[startX-1-leftSide][startY-1]->isOccupied())  break;

                isNextto = true;
                point += _board[startX-1-leftSide][startY-1]->getLMult()*_board[startX-1-leftSide][startY-1]->getScore();
                wordMul *= _board[startX-1-leftSide][startY-1]->getWMult();
                mainWord += _board[startX-1-leftSide][startY-1]->getLetter();
            }

            //As we read the word from up to down, we need to reverse the order of the first half;
            reverse(mainWord.begin(),mainWord.end());
            //add all the letters we want to put here
            size_t occupied  = 0;
            for (size_t i = 0; i < tileVector.size();i++){
                while(_board[startX-1+i+occupied][startY-1]->isOccupied()){
                isNextto = false;
                mainWord += _board[startX-1+i+occupied][startY-1]->getLetter();
                occupied++;
                }
                mainWord += tileVector[i]->getUse();
                point += tileVector[i]->getPoints()*_board[startX-1+i+occupied][startY-1]->getLMult();
                wordMul *= _board[startX-1+i+occupied][startY-1]->getWMult();
            }

            size_t tail = startX-1+tileVector.size()+occupied-1;
            if (tail > _columns-1) throw out_of_range ("OUT OF THE BOARD");

            for (size_t rightSide = 1; tail+rightSide <= _columns-1; rightSide++){
                if(!_board[tail+rightSide][startY-1]->isOccupied())  break;

                isNextto = true;
                point += _board[tail+rightSide][startY-1]->getLMult()*_board[tail+rightSide][startY-1]->getScore();
                wordMul *= _board[tail+rightSide][startY-1]->getWMult();
                mainWord += _board[tail+rightSide][startY-1]->getLetter();
            }
        //the main word
        pair<string,int> MainWord (mainWord , point*wordMul);
        words.push_back(MainWord);
        }
        
        //if it is vertical
        else{
                //check the upper side first
                for (size_t upper = 1; startY-1-upper >= 0; upper++){
                if(!_board[startX-1][startY-1-upper]->isOccupied())  break;

                isNextto = true;
                point += _board[startX-1][startY-1-upper]->getLMult()*_board[startX-1][startY-1-upper]->getScore();
                wordMul *= _board[startX-1][startY-1-upper]->getWMult();
                mainWord += _board[startX-1][startY-1-upper]->getLetter();
                }

            //As we read the word from up to down, we need to reverse the order of the first half;
            reverse(mainWord.begin(),mainWord.end());
            //add all the letters we want to put here
            size_t occupied  = 0;
            for (size_t i = 0; i < tileVector.size();i++){
                while(_board[startX-1][startY-1+i]->isOccupied()){
                isNextto = false;
                mainWord += _board[startX-1][startY-1+i]->getLetter();
                occupied++;
                }
                mainWord += tileVector[i]->getUse();
                point += tileVector[i]->getPoints()*_board[startX-1+i+occupied][startY-1]->getLMult();
                wordMul *= _board[startX-1+i+occupied][startY-1]->getWMult();
            }
            size_t tail = startY-1+tileVector.size()+occupied-1;
            if (tail > _rows-1) throw out_of_range ("OUT OF THE BOARD");

            for (size_t below = 1; tail+below <= _rows-1; below++){
                if(!_board[startX-1][tail+below]->isOccupied())  break;

                isNextto = true;
                point += _board[startX-1][tail+below]->getLMult()*_board[startX-1][tail+below]->getScore();
                wordMul *= _board[startX-1][tail+below]->getWMult();
                mainWord += _board[startX-1][tail+below]->getLetter();
            }
            //the main word
            pair<string,int> MainWord (mainWord , point*wordMul);
            words.push_back(MainWord);
        }

    return words;
    }

	void Board::executePlaceMove (const PlaceMove & m){
        size_t startX = m.getStartx();
        size_t startY = m.getStarty();
        bool horizontal = m.getDirection();
        size_t occupiedNum = 0;
        std::vector<Tile*> tileVector = m.tileVector();
        for (size_t i = 0; i < tileVector.size();i++){
            if(horizontal){
                while(_board[startX-1+i+occupiedNum][startY-1]->isOccupied()){
                    occupiedNum ++;
                }
                if (startX-1+i+occupiedNum <= _columns-1){
                _board[startX-1+i+occupiedNum][startY-1]->placeTile(tileVector[i]);
                }
                else{
                    throw out_of_range ("OUT OF BORDER");
                }
            }
            
            else{
                while(_board[startX-1][startY-1+i+occupiedNum]->isOccupied()){
                    occupiedNum ++;
                }
                if (startY-1+i+occupiedNum <= _rows-1){
                _board[startX-1][startY-1+i+occupiedNum]->placeTile(tileVector[i]);
                }
                else{
                    throw out_of_range ("OUT OF BORDER");
                }
            }
        }


    }

	Square * Board::getSquare (size_t x, size_t y) const{
        return _board[x-1][y-1];
    }

	size_t Board::getRows() const{
        return _rows;
    }

	size_t Board::getColumns() const{
        return _columns;
    }


