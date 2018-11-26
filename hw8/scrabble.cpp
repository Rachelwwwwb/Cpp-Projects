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
#include "Trie.h"

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
        string command = "";
        string fileName;
        for (size_t i = 0; i < line.size(); i++){
            command += line[i];
            if(line[i] == ':'){
                size_t j= i+1;
                while(line[j] == ' '){
                j++;}
                fileName = line.substr(j, line.size()-j);
                break;
            }
        }

        if (command == "HANDSIZE:"){
            handSize = stoi(fileName, 0, 10);
        }
        else if (command == "BOARD:"){
            boardFile = fileName;
        }
        else if (command == "TILES:"){
            bagFile = fileName;

        }
        else if (command == "DICTIONARY:"){
            dictionaryFile = fileName;
        }
        else if (command == "SEED:"){
            seed = stoi(fileName, 0, 10);
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
    bool allpass = false; 
    bool contPlay = true;
    //the condition that the game ends
    while(contPlay){

        //each individual get to choose
        for (size_t i = 0; i < numOfPlayers; i++){
            bool ifcontinue = true;
        while(ifcontinue && !allpass){
            ifcontinue = false; 
            printer.printBoard(myBoard);
            printer.printHand(*playerList[i]);
            
            string moveString = "";
            cout<< "It is Player "<< i+1 <<" " << playerList[i] -> getName() <<"'s turn" <<endl;
            cout << "Enter your move: ";
            getline (std::cin, moveString);
            
            Move*_move;
            Move* oneMove;
            oneMove = _move->parseMove(moveString, *playerList[i]);

            //If the user enters pass
            if (oneMove -> isPass()){
                ifcontinue = false;
                pass_num ++;
                 cout << "Your are passing this round..."<<endl;
                if (pass_num == numOfPlayers)   {
                    contPlay = false;
                    allpass = true; 
                    i = numOfPlayers;
                    delete oneMove;
                    break;}
            }

            //If the user enters exchange
            else if (oneMove -> isExchange()){
                ExchangeMove* exchange = (ExchangeMove*)oneMove;
                try{
                exchange -> execute(myBoard, myBag, myDic);
                }
                catch(invalid_argument &i){
                    ifcontinue = true;
                    delete oneMove;
                    cout << "No such tile" << i.what() <<endl;
                }
                if (!ifcontinue){
                cout << "New letter picked up: "<< exchange -> newLetterPicked()<<endl;
                pass_num = 0;
                printer.printHand(*playerList[i]);}
                }

            //If the user enters move
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
                    cout << "Words formed: ";
                    place->printNewWord();
                    cout << endl;
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
                pass_num = 0;
               }
            }
                 delete oneMove;

        }
            if (allpass) break;
            //check if the player has used up all the tiles
            if (playerList[i] -> getHandTiles().empty()){
                ifcontinue = false;
                contPlay = false;
                break;
            }

            cout << "Enter return to continue..."<<endl;
            cin.ignore();

        }
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
            if (playerList[j+1]->getScore() > playerList[j]->getScore()){
                    Player* tmp = playerList[j];
                    playerList[j] = playerList[j+1];
                    playerList[j+1] = tmp;
            }
        }
    }
    cout << "Winner:";
    for(size_t i = 0; i < playerList.size();i++){
        cout<< " " << playerList[i] -> getName();
        if (i+1 == playerList.size())  break;
        if (playerList[i+1]->getScore() < playerList[i]->getScore()) break;
    }
    cout << endl;

    for (size_t i = 0; i < playerList.size(); i++){
        delete playerList[i];
    }


}