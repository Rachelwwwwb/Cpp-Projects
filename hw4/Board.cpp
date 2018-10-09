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

    boardFileStream >> _columns >> _rows;
    boardFileStream >> _y >> _x;

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
        
        bool startCorrect = true;
        //check if the 1st player starts at the START
        if (!_board[_y-1][_x-1]->isOccupied()){
                startCorrect = false;
                isNextto = true;
            }
        
        if (_board[startY-1][startX-1]->isOccupied()){
            m.getPlayer() -> addTiles(tileVector);
            throw out_of_range ("THE FIRST IS OCCUPIED");
        }

        size_t j = 0;
        //for each word  in the opposite direction
        for (size_t i  = 0; i < tileVector.size(); i++){
           
            int points = 0;;
            int wordMul = 1;
            string word = "";
            if (horizontal){
                if (startX-1+j > _columns-1){
                    m.getPlayer() -> addTiles(tileVector);
                    throw out_of_range ("OUT OF THE BOARD");
                }
                while (_board[startY-1][startX-1+j]->isOccupied()){
                    j++;
                }
                //find the upper part of the word
                for ( int upperhalf = 1 ; (int) startY-1-upperhalf >=0 ;upperhalf++){
                    if (startX-1+j < 0 && startY-1-upperhalf < 0) break;
                    if (!_board[startY-1-upperhalf][startX-1+j]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startY-1-upperhalf][startX-1+j]->getLMult()*_board[startY-1-upperhalf][startX-1+j]->getScore();
                    wordMul *= _board[startY-1-upperhalf][startX-1+j]->getWMult();
                    word += _board[startY-1-upperhalf][startX-1+j]->getLetter();
                }
                    //As we read the word from up to down, we need to reverse the order of the first half;
                    reverse(word.begin(),word.end());
                    //add the letter we want to put here
                    word += tileVector[i]->getUse();
                    points += tileVector[i]->getPoints() * _board[startY-1][startX-1+j]->getLMult();
                    wordMul *=  _board[startY-1][startX-1+j]->getWMult();

                //then check the lower part of the word
                for ( size_t lowerhalf = 1 ; startY-1+lowerhalf <= _rows-1 ;lowerhalf++){
                    if (startY-1+lowerhalf > _rows-1) break;
                    if (!_board[startY-1+lowerhalf][startX-1+j]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startY-1+lowerhalf][startX-1+j]->getLMult()*_board[startY-1+lowerhalf][startX-1+j]->getScore();
                    wordMul *= _board[startY-1+lowerhalf][startX-1+j]->getWMult();
                    word += _board[startY-1+lowerhalf][startX-1+j]->getLetter();
                }
        
                if (word.size() > 1){
                    pair<string,int> aWord (word , points*wordMul);
                    words.push_back(aWord);
                }
                cerr << "Horizontal each letter: "<< i << "th : "<< word;
                j++;
            }

            //if vertical
            else{
                if (startY-1+j > _rows-1){
                     m.getPlayer() -> addTiles(tileVector);
                    throw out_of_range ("OUT OF THE BOARD");
                }
                while (_board[startY-1+j][startX-1]->isOccupied()){
                    j++;
                }
                //As before, go left first
                 for (int leftHalf = 1 ; (int)startX-1-leftHalf >=0 ;leftHalf++){
                    if (!_board[startY-1+j][startX-1-leftHalf]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startY-1+j][startX-1-leftHalf]->getLMult()*_board[startY-1+j][startX-1-leftHalf]->getScore();
                    wordMul *= _board[startY-1+j][startX-1-leftHalf]->getWMult();
                    word += _board[startY-1+j][startX-1-leftHalf]->getLetter();
                }
                    //As we read the word from up to down, we need to reverse the order of the first half;
                    reverse(word.begin(),word.end());
                    //add the letter we want to put here
                    word += tileVector[i]->getUse();
                    points += tileVector[i]->getPoints() * _board[startY-1+j][startX-1]->getLMult();
                    wordMul *= _board[startY-1+j][startX-1]->getWMult();


                //then go to the right
                for (size_t rightHalf = 1 ; startX-1+rightHalf <= _columns-1 ;rightHalf++){
                    if (!_board[startY-1+j][startX-1+rightHalf]->isOccupied())   break;
                    
                    isNextto = true;
                    points += _board[startY-1+j][startX-1+rightHalf]->getLMult()*_board[startY-1+j][startX-1+rightHalf]->getScore();
                    wordMul *= _board[startY-1+j][startX-1+rightHalf]->getWMult();
                    word += _board[startY-1+j][startX-1+rightHalf]->getLetter();
                }
        
                if (word.size() > 1){
                    pair<string,int> aWord (word , points*wordMul);
                    words.push_back(aWord);
                }

                j++;
            }

        }
        //check the dirc that the word is placing
        string mainWord = "";
        cerr << "line 184: mainWord: "<<mainWord << "this"<<endl;
        int point = 0;
        int wordMul = 1;
        if (horizontal){
            for (int leftSide = 1; (int) startX-1-leftSide >= 0; leftSide++){
                if(!_board[startY-1][startX-1-leftSide]->isOccupied())  break;
                
                isNextto = true;
                point += _board[startY-1][startX-1-leftSide]->getLMult()*_board[startY-1][startX-1-leftSide]->getScore();
                wordMul *= _board[startY-1][startX-1-leftSide]->getWMult();
                mainWord += _board[startY-1][startX-1-leftSide]->getLetter();
            }

            //As we read the word from up to down, we need to reverse the order of the first half;
            reverse(mainWord.begin(),mainWord.end());
            //add all the letters we want to put here

            size_t occupied  = 0;
            for (size_t i = 0; i < tileVector.size();i++){
                if (startX-1+i+occupied > _columns-1){
                    m.getPlayer() -> addTiles(tileVector);
                    throw out_of_range ("OUT OF THE BOARD");
                }
                while(_board[startY-1][startX-1+i+occupied]->isOccupied()){
                mainWord += _board[startY-1][startX-1+i+occupied]->getLetter();
                point += _board[startY-1][startX-1+i+occupied]->getScore();
                occupied++;
                isNextto = true;
                }
                mainWord += tileVector[i]->getUse();
                cerr << "line 208: mainWord: "<<i<<": "<<mainWord<<endl;
                cerr << "mainWord.size()" << mainWord.size()<<endl;
                point += tileVector[i]->getPoints()*_board[startY-1][startX-1+i+occupied]->getLMult();
                wordMul *= _board[startY-1][startX-1+i+occupied]->getWMult();
               if (startX-1+i+occupied == _x-1 && startY-1 == _y-1){
                   startCorrect = true;
               }
            }
            if (!_board[_y-1][_x-1]->isOccupied() && !startCorrect){
                //throw exceptions
                m.getPlayer() -> addTiles(tileVector);
                throw domain_error ("START POSITION");
            }

            size_t tail = startX-1+tileVector.size()+occupied-1;
            if (tail > _columns-1) {
                m.getPlayer() -> addTiles(tileVector);
                throw out_of_range ("OUT OF THE BOARD");}

            for (size_t rightSide = 1; tail+rightSide <= _columns-1; rightSide++){
                if(!_board[startY-1][tail+rightSide]->isOccupied())  break;

                isNextto = true;
                point += _board[startY-1][tail+rightSide]->getLMult()*_board[startY-1][tail+rightSide]->getScore();
                wordMul *= _board[startY-1][tail+rightSide]->getWMult();
                mainWord += _board[startY-1][tail+rightSide]->getLetter();

            }
        //the main word
        if (mainWord.size()>1){
        pair<string,int> MainWord (mainWord , point*wordMul);
        words.push_back(MainWord);}
        }
        
        //if it is vertical
        else{
                //check the upper side first
                for (int upper = 1; (int) startY-1-upper >= 0; upper++){
                if(!_board[startY-1-upper][startX-1]->isOccupied())  break;

                isNextto = true;
                point += _board[startY-1-upper][startX-1]->getLMult()*_board[startY-1-upper][startX-1]->getScore();
                wordMul *= _board[startY-1-upper][startX-1]->getWMult();
                mainWord += _board[startY-1-upper][startX-1]->getLetter();
            }

            //As we read the word from up to down, we need to reverse the order of the first half;
            reverse(mainWord.begin(),mainWord.end());
            //add all the letters we want to put here
            size_t occupied  = 0;
            for (size_t i = 0; i < tileVector.size();i++){
                 if (startY-1+i+occupied > _rows-1){
                    m.getPlayer() -> addTiles(tileVector);
                    throw out_of_range ("OUT OF THE BOARD");
                }
                while(_board[startY-1+i+occupied][startX-1]->isOccupied()){
                mainWord += _board[startY-1+i+occupied][startX-1]->getLetter();
                point += _board[startY-1+i+occupied][startX-1]->getScore();
                occupied++;
                isNextto = true;
                }
                mainWord += tileVector[i]->getUse();
                point += tileVector[i]->getPoints()*_board[startY-1+i+occupied][startX-1]->getLMult();
                wordMul *= _board[startY-1+i+occupied][startX-1]->getWMult();

                if (startX-1 == _x-1 && (int)startY-1 + (int)i + (int)occupied == (int)_y-1){
                   startCorrect = true;
                }
                
            }
            if (!_board[_y-1][_x-1]->isOccupied() && !startCorrect){
                //throw exceptions
                m.getPlayer() -> addTiles(tileVector);
                throw domain_error ("START POSITION");
            }
            size_t tail = startY-1+tileVector.size()+occupied-1;
            if (tail > _rows-1) {
                m.getPlayer() -> addTiles(tileVector);
                throw out_of_range ("OUT OF THE BOARD");}

            for (size_t below = 1; tail+below <= _rows-1; below++){
                if(!_board[tail+below][startX-1]->isOccupied())  break;

                isNextto = true;
                point += _board[tail+below][startX-1]->getLMult()*_board[tail+below][startX-1]->getScore();
                wordMul *= _board[tail+below][startX-1]->getWMult();
                mainWord += _board[tail+below][startX-1]->getLetter();
            }
            //the main word
            if (mainWord.size() > 0){
            pair<string,int> MainWord (mainWord , point*wordMul);
            words.push_back(MainWord);}
        }
             if(!isNextto){
                m.getPlayer() -> addTiles(tileVector);
                throw range_error ("Not NEXT TO SOME LETTER");
            }

            for (size_t i = 0; i <  words.size();i++){
                cout << i << " : " << words[i].first << ": "<< words[i].second << endl;
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
                if (startX-1+i+occupiedNum <= _columns-1){
                while(_board[startY-1][startX-1+i+occupiedNum]->isOccupied()){
                    occupiedNum ++;
                }
                if (startX-1+i+occupiedNum <= _columns-1){
                _board[startY-1][startX-1+i+occupiedNum]->placeTile(tileVector[i]);
                }
                }
                else{
                    m.getPlayer() -> addTiles(tileVector);
                    throw out_of_range ("OUT OF BORDER");
                }
            }
            
            else{
                if(startY-1+i+occupiedNum <= _rows-1){
                while(_board[startY-1+i+occupiedNum][startX-1]->isOccupied()){
                    occupiedNum ++;
                }
                if (startY-1+i+occupiedNum <= _rows-1){
                _board[startY-1+i+occupiedNum][startX-1]->placeTile(tileVector[i]);
                }
                }
                else{
                    m.getPlayer() -> addTiles(tileVector);
                    throw out_of_range ("OUT OF BORDER");
                }
            }
        }


    }

	Square * Board::getSquare (size_t x, size_t y) const{
        return _board[y-1][x-1];
    }

	size_t Board::getRows() const{
        return _rows;
    }

	size_t Board::getColumns() const{
        return _columns;
    }
