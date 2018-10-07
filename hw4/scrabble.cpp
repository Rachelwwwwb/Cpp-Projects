#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>

#include "Bag.h"
#include "Board.h"
#include "Move.h"
#include "Square.h"
#include "Dictionary.h"
#include "Player.h"
#include "Tile.h"
#include "rang.h"
#include "ConsolePrinter.h"
#include "Exceptions.h"

using namespace std;

int main(int argc, char* argv[]){
    ifstream config (argv[1]);
    size_t handSize;
    string boardFile;
    string bagFile;
    string dictionaryFile;
    uint32_t seed;

    string line;
    while(getline(config,line)){
        stringstream ss (line);
        string command;
        ss >> command;

        if (command == "HANDSIZE:"){
            ss >> handSize;
            ss >> handSize;
           // cout << handSize <<endl;
        }
        else if (command == "BOARD:"){
            ss >> boardFile;
            ss >> boardFile;
           // cout<< boardFile <<endl;
        }
        else if (command == "TILES:"){
            ss >> bagFile;
            ss >> bagFile;
           // cout << bagFile <<endl;
        }
        else if (command == "DICTIONARY:"){
            ss >> dictionaryFile;
            ss >> dictionaryFile;
           // cout << dictionaryFile <<endl;
        }
        else if (command == "SEED:"){
            ss >> seed;
            ss >> seed;
           // cout<< seed<<endl;
        }
    }

     //initial board, bag, dictionary before playing 
    Board myBoard (boardFile);
    Bag myBag (bagFile, seed);
    Dictionary myDic (dictionaryFile);
    ConsolePrinter printer;
    
    size_t numOfPlayers = 0;
    while(numOfPlayers < 1 || numOfPlayers > 8){
    cout << "Enter the number of players: ";
    cin >> numOfPlayers;
    }
    vector<Player*> playerList;
    for (size_t i = 0; i < numOfPlayers; i++){
        string name;
        cout << "The name for player "<< (int)i+1 << ": ";
        getline(std::cin,name);
        cin.ignore();
        playerList.push_back(new Player (name , handSize));
        std::vector<Tile*> tilesDrawn = myBag.drawTiles (handSize);
        playerList[i]->addTiles(tilesDrawn);

    }

   
    size_t pass_num = 0; 
    bool contPlay = true;
    //the condition that the game ends
   // while(contPlay && pass_num < numOfPlayers){
        //each individual get to choose
        for (size_t i = 0; i < numOfPlayers; i++){
            printer.printBoard(myBoard);
            printer.printHand(*playerList[i]);
            
            cin.ignore();
            string moveString = "";
            cout<< "It is Player "<< i+1 <<"'s turn" <<endl;
            cout << "Enter your move: ";
            getline (std::cin, moveString);
            
            Move*_move;
            Move* oneMove;
            oneMove = _move->parseMove(moveString, *playerList[i]);

            if (oneMove -> isPass()){
                pass_num ++;
                cout << "Your are passing this round..."<<endl;
            }
            else if (oneMove -> isExchange()){
                ExchangeMove* exchange = (ExchangeMove*)oneMove;
                exchange -> execute(myBoard, myBag, myDic);
                cout << "New letter picked up: "<< exchange -> newLetterPicked()<<endl;

                printer.printHand(*playerList[i]);
                }
            else if (oneMove -> isWord()){
                PlaceMove* place = (PlaceMove*) oneMove;
                //cerr<< place->getStartx();
                //cerr<< place->getStarty();
                //cerr << place->getDirection();

                place -> execute(myBoard, myBag, myDic);
                //printer.printBoard(myBoard);
                //printer.printHand(*playerList[i]);

            }





            cout << "Enter return to continue..."<<endl;
            cin.ignore();

        //each round for each player
        }
    //while loop
    //}

//the big main
}