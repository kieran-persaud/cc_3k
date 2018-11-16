#include <cstdlib>
#include <iostream>
#include "spawner.h"
#include "cell.h"
#include "door.h"
#include "emptycell.h"
#include "floortile.h"
#include "passage.h"
#include "wall.h"
#include "gold.h"
#include "dragonhoard.h"
#include "merchanthoard.h"
#include "normal.h"
#include "small.h"
#include "potion.h"
#include "ba.h"
#include "bd.h"
#include "ph.h"
#include "rh.h"
#include "wa.h"
#include "wd.h"
#include "invalidtype.h"
#include "halfling.h"
#include "merchant.h"
#include "orc.h"
#include "dwarf.h"
#include "elf.h"
#include "dragon.h"

using namespace std; 

int Spawner::getRandInt(int start, int end) {
	if (end == 0) { 
		// TODO: Make an exn for this 
		cout << "Cannot divide by zero" << endl; 
		exit(1); 
	}
	int y = start + rand() % (end-start); 
	return y;
}

std::shared_ptr<Item> Spawner::createItem(int row, int col, int randInt) {
	// TODO: Make it throw in case they entered an invalid number? 
	// Note: The conditions (intervals) for creating
	// a specific type of Potion/Gold for a random
	// number or a value from the file map to the same
	// int so we can just reuse this function. 
	shared_ptr<Item> ret; 
	cout << "randint is " << randInt << endl;
	// Potions:
	if(randInt >= 0 && randInt <= 5) {
		switch(randInt) {
			case 0: 
				ret = make_shared<RH>(row, col);
				return ret; 
			case 1: 
				ret = make_shared<BA>(row, col);
				return ret; 
			case 2: 
				ret = make_shared<BD>(row, col);
				return ret; 
			case 3: 
				ret = make_shared<PH>(row, col);
				return ret; 
			case 4: 
				ret = make_shared<WA>(row, col);
				return ret; 
			case 5:
				ret = make_shared<WD>(row, col);
				return ret; 
		}
	}

	// Gold: 
	if (randInt >= 10 && randInt <= 14) {
		ret = make_shared<Normal>(row, col);
	} 
	else if (randInt >= 15 && randInt <= 16) {
		ret = make_shared<Small>(row, col);
	} 
	else if (randInt == 17) {
		ret = make_shared<DragonHoard>(row, col);
	}
	else {
		ret = make_shared<MerchantHoard>(row, col); 
	}
	return ret; 
}

shared_ptr<Cell> Spawner::createCell(int row, int col, char c) {

	shared_ptr<Cell> newCell;  
	if (c == '-' || c == '|') {
		newCell = make_shared<Wall>(row, col, c); 
	} else if (c == '.') {
		newCell = make_shared<FloorTile>(row, col); 
	} else if (c == '#') {
		newCell = make_shared<Passage>(row, col); 
	} else if (c == '+') { 
		newCell = make_shared<Door>(row, col); 
	} else if (isspace(c)) {
		newCell = make_shared<EmptyCell>(row, col); 
	} else {
		throw InvalidType{c};
	}
	return newCell; 
}

std::shared_ptr<Human> Spawner::createEnemyFromFile(int row, int col, char c) {
	shared_ptr<Human> newEnemy;
	if (c == 'H'){
		newEnemy = make_shared<Human>(row, col);
	} else if (c == 'W'){
		newEnemy = make_shared<Dwarf>(row, col);
	} else if (c == 'E'){
		newEnemy = make_shared<Elf>(row, col);
	} else if (c == 'O'){
		newEnemy = make_shared<Orc>(row, col);
	} else if (c == 'M'){
		newEnemy = make_shared<Merchant>(row, col);
	} else if (c == 'D'){
		newEnemy = make_shared<Dragon>(row, col);
	} else if (c == 'L'){
		newEnemy = make_shared<Halfling>(row, col);
	} else {
		throw InvalidType{c};
	}
	return newEnemy;
}

std::shared_ptr<Human> Spawner::createEnemy(int row, int col, int randInt) {
	shared_ptr<Human> newEnemy;
	if (randInt >= 0 && randInt <= 3){
		newEnemy = make_shared<Human>(row, col);
	} else if (randInt >= 4 && randInt <= 6){
		newEnemy = make_shared<Dwarf>(row, col);
	} else if (randInt >= 7 && randInt <= 11){
		newEnemy = make_shared<Halfling>(row, col);
	} else if (randInt == 11 || randInt == 12){
		newEnemy = make_shared<Elf>(row, col);
	} else if (randInt == 13 || randInt == 14){
		newEnemy = make_shared<Orc>(row, col);
	} else if (randInt == 15 || randInt == 16){
		newEnemy = make_shared<Merchant>(row, col);
	}
	return newEnemy;
}
