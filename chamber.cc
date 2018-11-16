#include "chamber.h"
#include "cell.h"
using namespace std; 

Chamber::Chamber(): numTiles{0} {}

void Chamber::addCell(shared_ptr<Cell> toAdd) { 
	theChamber.emplace_back(toAdd);
	++numTiles;  
}

int Chamber::getNumTiles() {
	return numTiles; 
}

shared_ptr<Cell> Chamber::getTile(int tileNum) { 
	return theChamber[tileNum];
}
