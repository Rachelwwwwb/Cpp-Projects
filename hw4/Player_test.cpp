/* Ziang Liu
 * 9114346039
 * ziangliu@usc.edu
 * CSCI 104 HW #4
 */

#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <exception>

#include "Player.h"
#include "Tile.h"
#include "Exceptions.h"
#include "Bag.h"

using namespace std;

int main(){
	
	string name;
	const size_t maxTiles = 10;

	cout << "Please enter player name: " << endl;
	getline(cin, name);

	Player* my_player = new Player(name, maxTiles);
	Bag* my_bag = new Bag("bag.txt", 0);

	/*Test addTiles
	draw tiles from bag
	*/
	my_player->addTiles(my_bag->drawTiles(maxTiles));

	//add a '?' character
	Tile* my_tile = new Tile('?', 0);
	vector<Tile*> test_hand;
	test_hand.push_back(my_tile);
	my_player->addTiles(test_hand);

	/*check getHandTiles()
	check name()
	check getName()*/
	set<Tile*> my_hand = my_player->getHandTiles();
	//cout << "Hello " << my_player->getName() << "!" << endl;
	cout << "Current Tiles in Hand: ";
	for(set<Tile*>::iterator it=my_hand.begin(); it!=my_hand.end(); ++it){
		cout << (*it)->getLetter() << " ";
	}
	cout << endl;

    bool resolveBlanks = true;

	/*Check hasTiles()*/
	cout << "Enter the tiles you want to check: ";
	string move;
	cin >> move;
	if(my_player->hasTiles(move, resolveBlanks)){
		cout << "You have these tiles!" << endl;
	}
	else{
		cout << "You don't have these tiles!" << endl;
	}

	/*Check taketiles*/
	cout << "Enter the tiles you want to take: ";
	string move_1;
	cin >> move_1;
	//bool resolveBlanks = false;
	vector<Tile*> my_take;

    my_take = my_player->takeTiles(move_1, resolveBlanks);

	/*try{
		//my_take = my_player->toVector(move_1, resolveBlanks);
	}
	catch (InputException &e){
		cout << "Input Error: " << e.getMessage() << endl;
		return 1;
	}*/
	//check hand after take
	my_hand = my_player->getHandTiles();
	cout << "Current Tiles in Hand: ";
	for(set<Tile*>::iterator it=my_hand.begin(); it!=my_hand.end(); ++it){
		cout << (*it)->getLetter() << " ";
	}
	cout << endl;

	cout << "You have taken: ";
	for(size_t i=0; i<my_take.size(); i++){
		cout << my_take[i]->getLetter() << " ";
	}
	cout << endl;



	delete my_player;
	//delete my_tile;
	delete my_bag;


	return 0;
}
