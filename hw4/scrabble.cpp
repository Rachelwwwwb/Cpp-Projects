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
    cin.ignore();

    for (size_t i = 0; i < numOfPlayers; i++){
        string name;
        cout << "The name for player "<< (int)i+1 << ": ";
        getline(std::cin,name);
        playerList.push_back(new Player (name , handSize));
        std::vector<Tile*> tilesDrawn = myBag.drawTiles (handSize);
        playerList[i]->addTiles(tilesDrawn);

    }

   
    size_t pass_num = 0; 
    bool contPlay = true;
    //the condition that the game ends
    while(contPlay && pass_num < numOfPlayers){
        //each individual get to choose
        for (size_t i = 0; i < numOfPlayers; i++){
            bool ifcontinue = true;
        while(ifcontinue){
            ifcontinue = false;
             myBoard.printBoard();

            printer.printBoard(myBoard);
            printer.printHand(*playerList[i]);
            
            //cin.ignore();
            string moveString = "";
            cout<< "It is Player "<< i+1 <<" " << playerList[i] -> getName() <<"'s turn" <<endl;
            cout << "Enter your move: ";
            getline (std::cin, moveString);
            
            cerr << moveString<<endl;
            Move*_move;
            Move* oneMove;
            oneMove = _move->parseMove(moveString, *playerList[i]);

            if (oneMove -> isPass()){
                ifcontinue = false;
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
               
               try{
                place -> execute(myBoard, myBag, myDic);
               }
               catch (out_of_range& o){
                   ifcontinue = true;
                   cout << "Out of range: "<< o.what() <<endl;
               }
               catch (invalid_argument& i){
                    ifcontinue = true;
                   cout << "Invalid Word: " << i.what() << endl;
               }
               catch (length_error& l){
                    ifcontinue = true;
                   cout<< "Not start at starting position" << l.what() << endl;
               }
               catch (domain_error& d){
                   ifcontinue = true;
                   cout << "the starting position is occupied "<< d.what() << endl;
               }
               catch (range_error& r){
                   ifcontinue = true;
                   cout << "not next to certain letter " << r.what() << endl;
               }

               if (!ifcontinue){
                printer.printBoard(myBoard);
                printer.printHand(*playerList[i]);
                cout << "New words added: ";
                place->printNewWord();
                cout << endl;
                cout << "New score earned: " << place -> getNewScore() << endl;
                cout << "Total score for player "<< i+1 <<": "<<playerList[i]->getScore()<<endl;
               }
            }
            delete oneMove;

        }
            //check if the player has used up all the tiles
            if (playerList[i] -> isEmpty()){
                contPlay = false;
                break;
            }

            cout << "Enter return to continue..."<<endl;
            cin.ignore();

        //each round for each player
        }
    //while loop
    }

    //score calculation:
    vector <int> scoreList;
    int scoreOnHandTotal = 0;
    for (size_t i = 0; i < playerList.size(); i++){
         scoreOnHandTotal += playerList[i] -> scoresInHand();                
    }
    for (size_t i = 0; i < playerList.size();i++){
        int score = 0;
        if (playerList[i] -> scoresInHand() == 0){
            cout << "Player "<< i+1 <<"uses all!" << endl;
            score = scoreOnHandTotal + playerList[i] -> getScore();
        }
        else{
            score = playerList[i] -> getScore() - playerList[i] -> scoresInHand();
        }
        scoreList.push_back(score);
    }
    for (size_t i = 0; i < scoreList.size();i++){
        cout << "Player "<< i+1 << "'s score is "<< scoreList[i] << endl;
    }

    for (size_t i = playerList.size()-1; i > 0; i--){
        for (size_t j = 0; j < i; j++){
            if (playerList[j]->getScore() > playerList[j+1]->getScore()){
                    Player* tmp = playerList[j];
                    playerList[j] = playerList[j+1];
                    playerList[j+1] = tmp;
            }
        }
    }
    
    for(size_t i = 0; i < playerList.size();i++){
        cout << playerList[i] -> getName() << " is Winner!!!" <<endl;
        if (i+1 == playerList.size())  break;
        if (playerList[i+1]->getScore() < playerList[i]->getScore()) break;
    }




//the big main
}