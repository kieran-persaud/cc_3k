#ifndef SPAWNER_H
#define SPAWNER_H
#include <memory> 
#include "item.h"
#include "cell.h"
#include "human.h"
// can I forward declare Item/Cell here?

class Spawner {
public: 
	// start, end will specify the range [start, end)
	int getRandInt(int start, int end); 

	// Factory Method that returns a specific
	// Potion/Gold type (subclass). 
	// ** Note: The conditions (intervals) for creating
	// a specific type of Potion/Gold for a random
	// number or a value from the file map to the same
	// int so we can just reuse this function.
	// ** Potions are generated for [0, 5], and 
	// ** Gold for [6, 9].
	std::shared_ptr<Item> createItem(int row, int col, int randInt); 

	// Returns a shared_ptr to the type of Cell
	// that is associated with char c. 
	// e.g. c = - will return a Wall 
	// Exns: Throws InvalidCellType if c is not valid 
	std::shared_ptr<Cell> createCell(int row, int col, char c); 

	std::shared_ptr<Human> createEnemy(int row, int col, int randInt);

	std::shared_ptr<Human> createEnemyFromFile(int row, int col, char c);
};

#endif
