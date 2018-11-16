#ifndef CHAMBER_H
#define CHAMBER_H
#include <vector>
#include <memory>
#include "cell.h"

class Chamber { 
	int numTiles; 
	std::vector<std::shared_ptr<Cell>> theChamber; 

public:
	Chamber(); 

	// Adds the Cell from Floor to the Chamber
	void addCell(std::shared_ptr<Cell>); 

	// returns the number of Floortiles the chamber contains
	int getNumTiles();

	std::shared_ptr<Cell> getTile(int tileNum);  
}; 

#endif
