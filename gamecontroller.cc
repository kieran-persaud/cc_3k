#include "gamecontroller.h"
#include "gold.h"
#include "potion.h"
#include "drow.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "shade.h"
#include <sstream>
using namespace std;

GameController::GameController(string file) : floor(make_unique<Floor>()), curFloor{1}, file{file} {}

void GameController::startGame() {
	if (file==""){ floor->makeFloor(spawner, curFloor, p); }
	else { floor->makeFloor(spawner, curFloor, p, file); }
	floor->passStats(p->getRace(), p->getGold(), curFloor, p->getHp(), p->getAtk(), p->getDef());
}

void GameController::print(){
	cout << *floor;
}

void GameController::printScore(){
	cout << "You earned " << p->getGold() << " coins this game! Wow!" << endl;
}

//============================= Helper functions =============================
bool GameController::playerOnStairs(int x, int y) {
	Info stairInfo = floor->getStairInfo();
	if ((x == stairInfo.x) && (y == stairInfo.y)) {
		return true;
	} else { 
		return false; 
	}
}


// Checks block around Player
// - called whenever player physically moves (move, usePotion, attackEnemy)
void GameController::checkBlock(int x, int y) {
	cout << "r: " << x << ", c: " << y << endl;
	shared_ptr<Cell> cellPtr = floor->getCell(x,y);
	if (cellPtr->isOpen()) { return; } //end early
	cout << "not open" << endl;

	char cellChar = (cellPtr->getInfo()).sc;

	if (cellChar == 'P') { //Potion detected
			cout << "p" << endl;
		shared_ptr<Subject> subjPotion = cellPtr->getSubject(); 
		shared_ptr<Potion> potion = dynamic_pointer_cast<Potion>(subjPotion); 
		string potionStr = potion->getDescription();
		stringstream ss;
		ss << "Player sees a " << potion->getDescription() << ". ";
		floor->passAction(ss.str()); 

	} else if (cellChar == 'G') {
			cout << "g" << endl;

		shared_ptr<Subject> subjGold = cellPtr->getSubject();
		shared_ptr<Gold> gold = dynamic_pointer_cast<Gold>(subjGold);
		cout << "good cast my man" << endl;
		if (gold->getAmount() == 6) {
			cout << "wat" << endl;

			int oldHp = p->getHp();

			gold->getAttacked(*p); //not sure if it should be dereferenced?
			int damage = oldHp - p->getHp();

			stringstream ss;
			ss << "D deals " << damage << " to PC. ";
			floor->passAction(ss.str());		
			floor->passStats(p->getRace(), p->getGold(), curFloor, p->getHp(), p->getAtk(), p->getDef());
			if (p->getHp() <= 0) { gameOver = true; }

			//gold->getmoed(*p); //lol
		}
		cout << "done" << endl;

	} else if ((cellChar == 'H') || (cellChar == 'W') || (cellChar == 'E') || (cellChar == 'O') ||
		(cellChar == 'M') || (cellChar == 'D') || (cellChar == 'L')) { 
	//else if (cellChar != '\\' && cellChar != '|' && cellChar != '-' && cellChar!= '+' && cellChar != ' ') { //Enemy detected	
		cout << "e" << endl;

		shared_ptr<Subject> subjEnemy = cellPtr->getSubject(); 
		shared_ptr<Human> enemy = dynamic_pointer_cast<Human>(subjEnemy); 

		int oldHp = p->getHp();

		enemy->attack(*p); //not sure if it should be dereferenced?
		int damage = oldHp - p->getHp();

		stringstream ss;
		ss << cellChar << " deals " << damage << " to PC. ";
		floor->passAction(ss.str());		
		floor->passStats(p->getRace(), p->getGold(), curFloor, p->getHp(), p->getAtk(), p->getDef());
		if (p->getHp() <= 0) { gameOver = true; }
	}

}


// Checks 1-block radius
void GameController::checkRadius(){
	Info playerInfo = p->getInfo();
	int x = playerInfo.x;
	int y = playerInfo.y;
	cout << "Player coords: " << x << " " << y << endl;

	// Call checkBlock() on all 8 blocks
	checkBlock(x,y+1);
	checkBlock(x,y-1);
	checkBlock(x+1, y);
	checkBlock(x-1, y);
	checkBlock(x-1, y+1);
	checkBlock(x+1, y+1);
	checkBlock(x-1, y-1);
	checkBlock(x+1, y-1);
	cout << "checked" << endl;
}


// Parses direction string to a vector
vector<int> GameController::parseDir(string dir){
	vector<int> v(2);
	if (dir=="no") 			{ return v={-1,0}; }
	else if (dir == "so") 	{ return v={1,0}; } 
	else if (dir == "ea") 	{ return v={0,1}; } 
	else if (dir == "we") 	{ return v={0,-1}; }
	else if (dir == "nw") 	{ return v={-1,-1}; }
	else if (dir == "ne") 	{ return v={-1,1}; }
	else if (dir == "sw") 	{ return v={1,-1}; }
	else					{ return v={1,1}; } //se
}


// - Returns true for valid input 
// - false if the place you're moving to is a wall or if it's occupied
// Valid directions are: no,so,ea,we,nw,ne,sw,se
bool GameController::validDir(string dir){
	if ((dir == "no") || (dir == "so") || (dir == "ea") || (dir == "we") ||
		(dir == "nw") || (dir == "ne") || (dir == "sw") || (dir == "se")) {

			return true;
	} 
	return false; 
}


bool GameController::hasSubject(string dir){ //returns True if something is there
	vector<int> dirVec = parseDir(dir);
	Info playerInfo = p->getInfo();

	int x = playerInfo.x + dirVec[0];
	int y = playerInfo.y + dirVec[1];
	cout << "THE CELL'S CHARACTER IS: " << floor->getCell(x,y)->getInfo().sc << endl;

	if ((floor->getCell(x,y))->canMoveTo() || //nothing is there
		floor->getCell(x,y)->getInfo().sc == '\\') { // (floor->getCell(x,y) = floor[][] = a Cell pointer
		cout << "canMoveTo() successful" << endl;
		return false;
	} else {
		return true;
	}
}


string GameController::getDirString(string dir){
	if (dir == "no") { return "North"; }
	else if (dir == "so") {return "South";}
	else if (dir == "ea") {return "East";}
	else if (dir == "we") {return "West";}
	else if (dir == "nw") {return "Northwest";}
	else if (dir == "ne") {return "Northeast";}
	else if (dir == "sw") {return "Southwest";}
	else {return "Southeast";}
}

//====================== Mutators and Accessors =======================

void GameController::setGameOver(bool b) {
	gameOver = b;
}

bool GameController::getGameOver() {
	return gameOver;
}

//====================== Command interpreter functions =======================

bool GameController::movePlayer(string dir){
	if (!validDir(dir) || hasSubject(dir)) { //bad direction
		cout << "got a bad direction" << endl;
		return false; //let main handle reprompting user for valid input
	}
	cout << "Valid input!" << endl;
	vector<int> dirVec = parseDir(dir);
	cout << "parseDir" << endl;
	Info playerInfo = p->getInfo();
	cout << "get info" << endl;
	floor->getCell(playerInfo.x, playerInfo.y)->detachSubject();
	cout << "detach" << endl;
	int x = playerInfo.x + dirVec[0];
	int y = playerInfo.y + dirVec[1];
	cout << "failed here" << endl; 

	p->move(dirVec[0], dirVec[1]); //move player
	cout << "played moved" << endl; 
	cout << "seg fault next" << endl;

	if (playerOnStairs(x, y)) { //player won
		if (curFloor == 5) {
			gameOver = true;
			return true;
		} else {
			++curFloor;
			floor.reset(new Floor);
			cout << "reset floor" << endl;
			p->resetStats();
			cout << "reset stats" << endl; 
			floor->makeFloor(spawner, curFloor, p, file);
			cout << "made floor" << endl; 
			floor->passAction("CONGRATS, YOU REACHED THE NEXT FLOOR!!! ( ^ ______ ^ )");
			cout << "reached next level message passed action" << endl;
			startGame();
			Info newPlayerInfo = p->getInfo();
			cout << "PLAYER COORDS AFTER NEW FLOOR" << newPlayerInfo.x << " " << newPlayerInfo.y << endl;
		}
	}

	string dirString = getDirString(dir);
	cout << "seg fault?" << endl; 
 	stringstream ss;
 	cout << "trying to cout dirstring" << endl; 
 	cout << dirString << endl; 
	ss << "Player moves " <<  dirString << ".";
	floor->passAction(ss.str()); //update textDisplay action field
	cout << "passed action" << endl; 

	if (((floor->getCell(x,y))->getInfo()).sc == 'G') { 
		shared_ptr<Subject> goldSubjPtr = (floor->getCell(x,y))->getSubject(); // Subject ptr to Gold ptr, make auto??
		shared_ptr<Gold> goldPtr = dynamic_pointer_cast<Gold>(goldSubjPtr);
		cout << "trying to pick up gold" << endl; 
		cout << "the amount of gold we are going to try to pick up is: " << goldPtr->getAmount() << endl;
		goldPtr->getPickedUp(*p); //does this have to be dereferenced?
		cout << "called picked up gold" << endl;
	}
	floor->passStats(p->getRace(), p->getGold(), curFloor, p->getHp(), p->getAtk(), p->getDef());
	floor->getCell(x,y)->addSubject(p);
	cout << "added sub" << endl;
	checkRadius();
	cout << "check rad" << endl;
	if (!p->getExists()) { gameOver = true; }
	cout << "checked exist" << endl;

	floor->moveEnemies();
	return true; 
}


bool GameController::usePotion(string dir){
	if (!validDir(dir)) { //invalid direction
		cout << "POTION INVALID DIR" << endl;
		return false; 
	}

	Info i = p->getInfo();
	vector<int> dirVec = parseDir(dir);
	int x = dirVec[0] + i.x;
	int y = dirVec[1] + i.y;

	if (((floor->getCell(x,y))->isOpen()) || //no potion
		((floor->getCell(x,y))->getInfo().sc != 'P')) { 
		cout << "POTION FALSE HERE" << endl;
		return false; 
	}
	
	shared_ptr<Subject> potionSubj = (floor->getCell(x,y))->getSubject();
	shared_ptr<Potion> potion = dynamic_pointer_cast<Potion>(potionSubj);
	potion->getDrunk(*p);
	(floor->getCell(x,y))->detachSubject();

	stringstream ss;
	ss << "PC uses " << potion->getDescription() << ". ";
	floor->passAction(ss.str());
	floor->passStats(p->getRace(), p->getGold(), curFloor, p->getHp(), p->getAtk(), p->getDef());
	checkRadius();
	floor->moveEnemies();
	if (!p->getExists()) { gameOver = true; }
	return true;
}


bool GameController::attackEnemy(string dir){
	if (!validDir(dir)) { //invalid direction
		cout << "valid direction failed :~(" << endl;
		return false; 
	}

	Info i = p->getInfo();
	vector<int> dirVec = parseDir(dir);
	int x = dirVec[0] + i.x;
	int y = dirVec[1] + i.y;

	shared_ptr<Cell> cellPtr = floor->getCell(x,y);
	char cellChar = (cellPtr->getInfo()).sc;
	cout << "the cellChar is: " << cellChar << endl;

	if ((cellChar != 'H') && (cellChar != 'W') && (cellChar != 'E') && (cellChar != 'O') &&
		(cellChar != 'M') && (cellChar != 'D') && (cellChar != 'L')) { 
		cout << "not an enemy" << endl;
		return false; 
	}

	shared_ptr<Subject> enemySubj = cellPtr->getSubject();
	shared_ptr<Human> enemy = dynamic_pointer_cast<Human>(enemySubj);
	int oldHp = enemy->getHp();
	p->attack(*enemy);
	int damage = oldHp - enemy->getHp();

	stringstream ss;
	ss << "PC deals " << damage << "to " << cellChar << ". ";

	if (enemy->getHp() <= 0) { //CHECK IF ENEMY IS DEAD
		ss << cellChar << " has been slain! ";
		enemy->die();
		if (cellChar == 'H'){
			//drop 2
			shared_ptr<Item> firstPile = spawner.createItem(x,y,11);
			shared_ptr<Cell> temp1 = floor->getCell(x,y);
			temp1->addSubject(firstPile);
			shared_ptr<Cell> temp2 = floor->getFreeCell(x,y);
			shared_ptr<Item> secondPile = spawner.createItem(temp2->getInfo().x,temp2->getInfo().y,11);
			temp2->addSubject(secondPile);
		} else if (cellChar == 'M') {
			//drop merch
			shared_ptr<Item> firstPile = spawner.createItem(x,y,19);
			shared_ptr<Cell> temp1 = floor->getCell(x,y);
			temp1->addSubject(firstPile);
		}
		cellPtr->notifyObservers();	
	}

	floor->passAction(ss.str());
	floor->passStats(p->getRace(), p->getGold(), curFloor, p->getHp(), p->getAtk(), p->getDef());
	checkRadius();
	if (!p->getExists()) { gameOver = true; }
	floor->moveEnemies();
	return true;
}


bool GameController::makePlayer(string race){
	if (race == "d") { p = make_shared<Drow>(); }
	else if (race == "v") { p = make_shared<Vampire>(); }
	else if (race == "g") { p = make_shared<Goblin>(); }
	else if (race == "t") { p = make_shared<Troll>(); }
	else if (race == "s") { p = make_shared<Shade>(); } 
	else {return false;}
	return true;
}


void GameController::freezeEnemies() {
	unique_ptr<Human> enemy= make_unique<Human>();
	enemy->toggleMove();
}
