#include "floor.h"
#include <fstream> 
#include <iostream>
#include "spawner.h"
//#include "character.h"
#include "invalidtype.h"
#include "stair.h"
#include "dragonhoard.h"
#include <cstdlib>
using namespace std; 

Floor::Floor(int rows, int cols): 
rows{rows}, cols{cols}, td(make_shared<TextDisplay>()) {}

void Floor::makeFloor(Spawner &spawner, int floorNum, 
	shared_ptr<Shade> player, std::string floorFile) {
	cout << "making floor" << endl;
	srand(time(NULL)); 
	generateDefaultFloor(spawner); 
	makeChambers();	
	if (floorFile == "defaultfloor.txt") {
		spawnEverything(spawner, player); 
	} else {
		// initialize stair, players, 
		// potions/gold, enemies from file 
		generateFloorFromFile(spawner, floorNum, player, floorFile);
		connectDragons(); 
	}
}

// ~~~~~~~~~~~~~~~******~~~~~~~~~~~~~~~
//               Begin:
// Helper functions for makeFloor() 
// ~~~~~~~~~~~~~~~******~~~~~~~~~~~~~~~

void Floor::spawnEverything(Spawner &spawner, shared_ptr<Shade> player) {
	cout << "Spawning everything" << endl;
	int chamberNumber = spawnPlayer(spawner, player); 
	spawnStair(spawner, chamberNumber);
	spawnItems(spawner); 
	spawnEnemies(spawner);
	spawnDragons(spawner);
}

int Floor::spawnPlayer(Spawner &spawner, shared_ptr<Shade> player) {
	int whichChamber = spawner.getRandInt(0, 5); 
	Chamber chosenChamber = chambers.at(whichChamber); 
	// Pick a tile in the chamber
	shared_ptr<Cell> chosenTile;
	int numTiles = chosenChamber.getNumTiles();
	while(true) {
		int whichTile = spawner.getRandInt(0, numTiles);
		chosenTile = chosenChamber.getTile(whichTile);
	// Check that the floortile is free
		if (chosenTile->isOpen()) break; 
	} 
	player->setCoords(chosenTile->getInfo().x, chosenTile->getInfo().y);
	cout << "set player's coords to " << chosenTile->getInfo().x << " " << chosenTile->getInfo().y << endl;
	chosenTile->addSubject(player); 
	return whichChamber; 
}

shared_ptr<Cell> Floor::getFreeCell(int row, int col) { 
	if (getCell(row-1, col-1)->isOpen() && 
		getCell(row-1, col-1)->canMoveTo() && 
		(getCell(row-1, col-1)->getInfo()).sc != '+') {
		return getCell(row-1, col-1); 
	} 
	else if (getCell(row-1, col)->isOpen() && 
		getCell(row-1, col)->canMoveTo() && 
		(getCell(row-1, col)->getInfo()).sc != '+') {
		return getCell(row-1, col);
	} 
	else if (getCell(row-1, col+1)->isOpen() && 
		getCell(row-1, col+1)->canMoveTo() && 
		(getCell(row-1, col+1)->getInfo()).sc != '+') {
		return getCell(row-1, col+1);
	}
	else if (getCell(row, col+1)->isOpen() && 
		getCell(row, col+1)->canMoveTo() && 
		(getCell(row, col+1)->getInfo()).sc != '+') {
		return getCell(row, col+1);
	} 
	else if (getCell(row+1, col+1)->isOpen() && 
		getCell(row+1, col+1)->canMoveTo() && 
		(getCell(row+1, col+1)->getInfo()).sc != '+') {
		return getCell(row+1, col+1);
	} 
	else if (getCell(row+1, col)->isOpen() && 
		getCell(row+1, col)->canMoveTo() && 
		(getCell(row+1, col)->getInfo()).sc != '+') {
		return getCell(row+1, col);
	} 
	else if (getCell(row+1, col-1)->isOpen() && 
		getCell(row+1, col-1)->canMoveTo() && 
		(getCell(row+1, col-1)->getInfo()).sc != '+') {
		return getCell(row+1, col-1);
	} 
	else if (getCell(row, col-1)->isOpen() && 
		getCell(row, col-1)->canMoveTo() && 
		(getCell(row, col-1)->getInfo()).sc != '+') {
		return getCell(row, col-1);
	}
	return nullptr;
}

vector<shared_ptr<Cell>> Floor::getAllFreeCells(int row, int col) {
	vector<shared_ptr<Cell>> v; 
	if (getCell(row-1, col-1)->isOpen() && 
		getCell(row-1, col-1)->canMoveTo() && 
		(getCell(row-1, col-1)->getInfo()).sc != '+') {
		v.emplace_back(getCell(row-1, col-1));
	} 
	if (getCell(row-1, col)->isOpen() && 
		getCell(row-1, col)->canMoveTo() && 
		(getCell(row-1, col)->getInfo()).sc != '+') {
		v.emplace_back(getCell(row-1, col));
	} 
	if (getCell(row-1, col+1)->isOpen() && 
		getCell(row-1, col+1)->canMoveTo() && 
		(getCell(row-1, col+1)->getInfo()).sc != '+') {
		v.emplace_back(getCell(row-1, col+1));
	}
	if (getCell(row, col+1)->isOpen() && 
		getCell(row, col+1)->canMoveTo() && 
		(getCell(row, col+1)->getInfo()).sc != '+') {
		v.emplace_back(getCell(row, col+1));
	} 
	if (getCell(row+1, col+1)->isOpen() && 
		getCell(row+1, col+1)->canMoveTo() && 
		(getCell(row+1, col+1)->getInfo()).sc != '+') {
		v.emplace_back(getCell(row+1, col+1));
	} 
	if (getCell(row+1, col)->isOpen() && 
		getCell(row+1, col)->canMoveTo() && 
		(getCell(row+1, col)->getInfo()).sc != '+') {
		v.emplace_back(getCell(row+1, col));
	} 
	if (getCell(row+1, col-1)->isOpen() && 
		getCell(row+1, col-1)->canMoveTo() && 
		(getCell(row+1, col-1)->getInfo()).sc != '+') {
		v.emplace_back(getCell(row+1, col-1));
	} 
	if (getCell(row, col-1)->isOpen() && 
		getCell(row, col-1)->canMoveTo() && 
		(getCell(row, col-1)->getInfo()).sc != '+') {
		v.emplace_back(getCell(row, col-1));
	}
	return v; 
}

void Floor::spawnDragons(Spawner &spawner) {
	cout << "calling spawndragons()" << endl;
	for(auto &hoard:dragHoards) {
		// Get the coordinates of the hoard
		// Spawn a dragon on a free tile around the hoard 
		cout << "trying to spawn dragon" << endl;
		Info hoardInfo = hoard->getInfo(); 
		cout << "Got hoardinfo" << endl;
		int row = hoardInfo.x;
		int col = hoardInfo.y;
		cout << "ici" << endl;
		auto freeCell = getFreeCell(row, col);
		cout << "possibilite" << endl; 
		if (!freeCell) continue;
		Info freeCellInfo = freeCell->getInfo();
		auto dragon = spawner.createEnemyFromFile(freeCellInfo.x, freeCellInfo.y, 'D');
		freeCell->addSubject(dragon);
		cout << "Added dragon" << endl; 
		std::shared_ptr<DragonHoard> theHoard =
			dynamic_pointer_cast<DragonHoard>(hoard);
		theHoard->attachDragon(dragon); 
		cout << "attached dragon" << endl;
		cout << "dragon's coords are : " << dragon->getInfo().x << dragon->getInfo().y << endl;
	}
}

void Floor::connectDragons() {
	// Iterate over dragons and dragonhoards
	// Attach to each other if they are within
	// each other's radius. 
	for(auto &dragHoard:dragHoards) {
		for(auto it = dragons.begin(); it != dragons.end(); ++it) {
			// Convert the dragHoard to a DragonHoard type
			// (It's currently just an item)
			// Need to call attachDragon() from Gold...
			std::shared_ptr<DragonHoard> theHoard =
			dynamic_pointer_cast<DragonHoard>(dragHoard);
			// Check if the current dragon is within the
			// dragHoard's radius 
			Info hoardInfo = dragHoard->getInfo();
			int row = hoardInfo.x;
			int col = hoardInfo.y; 
			Info dragonInfo = (*it)->getInfo(); 
			int dRow = dragonInfo.x;
			int dCol = dragonInfo.y; 
			if ((dRow == row-1 || dRow == row || dRow == row+1) && 
				(dCol == col-1 || dCol == col || dCol == col+1)) {
				theHoard->attachDragon((*it)); 
				dragons.erase(it);
			}
		}
	}
}

void Floor::generateDefaultFloor(Spawner &spawner, string fileName) {
	// go see testfloor1.cc
	// read in each line and create the appropriate
	// type of Cell based on the character 
	int row = 0; 
	int boardRows = rows; 
	int boardCols = cols;
	ifstream file{fileName}; 
	string currLine; 

	while(row < boardRows && getline(file, currLine)) {
		char currChar; 
		
		// Initialize each row 
		// TODO: Do I need to do this if I resize?? 
		vector<shared_ptr<Cell>> v; 
		theFloor.emplace_back(v); 
		shared_ptr<Cell> newCell; 
		// Create the Cells column by column
		for(int col = 0; col < boardCols; ++col) { 
			currChar = currLine[col]; 
			// Creating cells will throw if the user entered
			// a file with an invalid char for the Cell type 
			try {
				newCell = spawner.createCell(row, col, currChar); 
			} catch (InvalidType &r) { 
				std::cout << r.what() << endl; 
				// TODO: better way to do this (exit)?
				std::exit(1); 
			}
			newCell->attach(td); 
			newCell->notifyObservers();
			theFloor.at(row).emplace_back(std::move(newCell)); 
		}
		// finish making the current row 
		++row; 
	}
}

void Floor::generateFloorFromFile(Spawner &spawner, int floorNum, 
	shared_ptr<Shade> player, string fileName) {
	int row = 0; 
	int boardRows = 25; 
	int boardCols = 79;
	int startRow = boardRows * (floorNum-1); 
	int endRow = boardRows + (boardRows * (floorNum-1)); 
	ifstream file{fileName}; 
	string currLine; 

	while(row < endRow && getline(file, currLine)) {
		if (row < startRow) continue; 
		for(int col = 0; col < boardCols; ++col) { 
			char currChar = currLine[col]; 
			shared_ptr<Cell> tileToSpawnOn = theFloor.at(row).at(col); 

		// Spawn Items, and store DragonHoards 
			if (currChar >= '0' && currChar <= '9') {
				int itemNum = currChar - '0'; 
				shared_ptr<Item> newItem = spawner.createItem(row, col, itemNum); 
				if (itemNum == 9) dragHoards.emplace_back(newItem);
				tileToSpawnOn->addSubject(newItem);
			}
		// Spawn enemies, and store dragons 
			else if (currChar >= 'A' && currChar <= 'Z') {
				auto newEnemy = spawner.createEnemyFromFile(row, col, currChar); 
				if (currChar == 'D') dragons.emplace_back(newEnemy); 
				tileToSpawnOn->addSubject(newEnemy); 
			}
		// Spawn stairs
			else if (currChar == '\\') {
				shared_ptr<Stair> stair = make_shared<Stair>(row, col); 
				stairInfo = stair->getInfo();
				tileToSpawnOn->addSubject(stair);
			}
		// Spawn player
			else if (currChar == '@') {
				Info tileInfo = tileToSpawnOn->getInfo(); 
				player->setCoords(tileInfo.x, tileInfo.y); 
				cout << "set player's coords to " << tileInfo.x << " " << tileInfo.y << endl; 
				tileToSpawnOn->addSubject(player); 
			}
		}
		++row; 
	}
}

void Floor::makeChambers() {
	chambers.resize(5); 
	//std::vector<std::vector<Chamber>> chambers; 
	for(int i = 1; i <= 5; ++i) { 
		Chamber &currChamber = chambers.at(i-1); 
		addCellsToChamber(currChamber, i); 
	}
}

void Floor::addCellsToChamber(Chamber &chamber, int chamberNumber) {
	switch(chamberNumber) {
		case 1:
			for(int row = 3; row <= 6; ++row) {
				for(int col = 3; col <= 28; ++col) {
					shared_ptr<Cell> toAdd = theFloor.at(row).at(col); 
					// TODO: emplace_back() in chamber
					chamber.addCell(toAdd); 
				}
			}
			return;

		case 2:
			for(int row = 15; row <= 21; ++row) {
				for(int col = 4; col <= 24; ++col) {
					shared_ptr<Cell> toAdd = theFloor.at(row).at(col); 
					// TODO: emplace_back() in chamber
					chamber.addCell(toAdd); 
				}
			}
			return;

		case 3:
			for(int row = 10; row <= 12; ++row) {
				for(int col = 38; col <= 49; ++col) {
					shared_ptr<Cell> toAdd = theFloor.at(row).at(col); 
					// TODO: emplace_back() in chamber
					chamber.addCell(toAdd); 
				}
			}
			return;

		case 4:
		// The one on the far right, on top 
			for(int row = 3; row <= 6; ++row) {
				for(int col = 39; col <= 61; ++col) {
					shared_ptr<Cell> toAdd = theFloor.at(row).at(col); 
					// TODO: emplace_back() in chamber
					chamber.addCell(toAdd); 
				}
			}
			for(int col = 62; col <= 69; ++col) {
				shared_ptr<Cell> toAdd = theFloor.at(5).at(col); 
				// TODO: emplace_back() in chamber
				chamber.addCell(toAdd); 
			}
			for(int col = 62; col <= 72; ++col) {
				shared_ptr<Cell> toAdd = theFloor.at(6).at(col); 
				// TODO: emplace_back() in chamber
				chamber.addCell(toAdd); 
			}

			for(int row = 7; row <= 12; ++row) {
				for(int col = 61; col <= 75; ++col) {
					shared_ptr<Cell> toAdd = theFloor.at(row).at(col); 
					chamber.addCell(toAdd);
				}
			}
			return;

		case 5:
			for(int row = 16; row <= 18; ++row) {
				for(int col = 65; col <= 77; ++col) {
					shared_ptr<Cell> toAdd = theFloor.at(row).at(col); 
					// TODO: emplace_back() in chamber
					chamber.addCell(toAdd); 
				}
			}
			for(int row = 19; row <= 21; ++row) {
				for(int col = 37; col <= 75; ++col) {
					shared_ptr<Cell> toAdd = theFloor.at(row).at(col); 
					// TODO: emplace_back() in chamber
					chamber.addCell(toAdd); 
				}
			}
			return;
	}
}

shared_ptr<Cell> Floor::chooseTile(Spawner &spawner) {
	// Pick a chamber from which to choose the tile 
	int whichChamber = spawner.getRandInt(0, 5); 
	Chamber chosenChamber = chambers[whichChamber]; 

	// Pick a tile in the chamber
	shared_ptr<Cell> chosenTile;
	int numTiles = chosenChamber.getNumTiles();
	while(true) {
		int whichTile = spawner.getRandInt(0, numTiles);
		chosenTile = chosenChamber.getTile(whichTile);
	// Check that the floortile is free
		if (chosenTile->isOpen()) break; 
	}
	return chosenTile; 
}

void Floor::spawnStair(Spawner &spawner, int chamberNum) {
	// Pick chamber
	int whichChamber; 
	while (true) {
		whichChamber = spawner.getRandInt(0, 5); 
		if (whichChamber != chamberNum) break; 
	}

	Chamber chosenChamber = chambers[whichChamber]; 

	// Pick a tile in the chamber
	shared_ptr<Cell> chosenTile;
	int numTiles = chosenChamber.getNumTiles();
	while(true) {
		int whichTile = spawner.getRandInt(0, numTiles);
		chosenTile = chosenChamber.getTile(whichTile);
	// Check that the floortile is free
		if (chosenTile->isOpen()) break; 
	}
	shared_ptr<Stair> stair = make_shared<Stair>(chosenTile->getInfo().x, chosenTile->getInfo().y); 
	stairInfo = stair->getInfo();
	chosenTile->addSubject(stair); 
}

void Floor::spawnItems(Spawner &spawner) {
	for(int i = 0; i < 20; ++i) {
	// Pick a chamber 
		int whichChamber = spawner.getRandInt(0, 5); 
		Chamber chosenChamber = chambers[whichChamber]; 

	// Pick a tile in the chamber
		shared_ptr<Cell> chosenTile = chooseTile(spawner);
		Info tileInfo = chosenTile->getInfo();

		int itemNum;
		shared_ptr<Item> itemToAdd; 

		if (i < 10) { // make potions 
			itemNum = spawner.getRandInt(0, 6);
		}
		else { // make gold 
			itemNum = spawner.getRandInt(10, 18); 
		}

		// Create the item 
		itemToAdd = spawner.createItem(tileInfo.x, tileInfo.y, itemNum);  
		if (itemNum == 17) {
			cout << "spawned a dragon hoard at " << tileInfo.x << " " << tileInfo.y << endl;
			dragHoards.emplace_back(itemToAdd);
		}
		// Add item to the tile 
		chosenTile->addSubject(itemToAdd);
	}
}	

void Floor::spawnEnemies(Spawner &spawner) {
	for(int i = 0; i < 20; ++i) { 
		// Pick a tile 
		shared_ptr<Cell> chosenTile = chooseTile(spawner); 
		Info chosenTileInfo = chosenTile->getInfo(); 

		// Generate a random number between [0, 17) 
		// (probabilities out of 18)
		int randInt = spawner.getRandInt(0, 17); 
		// Make enemy 
		auto newEnemy = spawner.createEnemy(chosenTileInfo.x, chosenTileInfo.y, randInt);
		chosenTile->addSubject(newEnemy); 
	}
}

void Floor::moveEnemies() {
	// Iterate over the entire floor and 
	// add enemies to a vector, then call move on them 
	// (after checking where they can move to). 
	if (!(Human::getCanMove())) return; 
	vector<shared_ptr<Human>> enemies; 
	for(auto &row:theFloor) {
		for(auto &theCell:row) {
			char sc = (theCell->getInfo()).sc;
			if (sc == 'H' || sc == 'W' || sc == 'E' ||
				sc == 'O' || sc == 'M' || sc == 'D' || sc == 'L') 
				enemies.emplace_back(dynamic_pointer_cast<Human>(theCell->getSubject())); 

		}
	}
	for(auto &enemy:enemies) { 
		if (enemy->getInfo().sc == 'D') continue;
		int myX = enemy->getInfo().x; 
		int myY = enemy->getInfo().y; 
		getCell(myX, myY)->detachSubject(); 
		auto myFreeCells = getAllFreeCells(myX, myY);
		if(myFreeCells.size() == 0) continue;
		Spawner s = Spawner();
		auto chosenCell = myFreeCells.at(s.getRandInt(0, myFreeCells.size()));
		// May need to double check this 
		enemy->move((chosenCell->getInfo().x)-myX, (chosenCell->getInfo().y)-myY);
		//enemy->move(1,1);
		chosenCell->addSubject(enemy);
	}
}

// ~~~~~~~~~~~~~~~******~~~~~~~~~~~~~~~
//                 End:
//   Helper functions for makeFloor() 
// ~~~~~~~~~~~~~~~******~~~~~~~~~~~~~~~

Info Floor::getStairInfo() {
	return stairInfo; 
}

shared_ptr<Cell> Floor::getCell(int x, int y) {
	return theFloor.at(x).at(y); 
} 

void Floor::passAction(string action) {
	td->updateAction(action); 
}

void Floor::passStats(std::string race, int gold, int curFloor, 
	int hp, int atk, int def) {
	td->updateStats(race, gold, curFloor, 
	hp, atk, def);
}

std::ostream &operator<<(std::ostream &out, const Floor &floor) {
	out << *(floor.td); 
	return out; 
}
