#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
#include <string>
#include <memory>
#include "item.h"
#include "textdisplay.h" 
#include "cell.h"
#include "chamber.h"
#include "spawner.h"
#include "human.h"
#include "shade.h"
class fstream; 
class Spawner;
//class Character; 
class Stair; 

class Floor {
	int rows, cols; 
	// Factory factory; I think spawner belongs to Game?
	// TODO: I don't know when to use unique_ptr or shared_ptr..
	std::vector<std::vector<std::shared_ptr<Cell>>> theFloor; 
	std::shared_ptr<TextDisplay> td; 
	std::vector<std::shared_ptr<Item>> dragHoards;
	std::vector<std::shared_ptr<Human>> dragons;  
	// does this need to be a vector of Chamber*? .. 
	std::vector<Chamber> chambers = std::vector<Chamber>(5);
	Info stairInfo; 
	// ~~~***~~~
	// The next 3 (not including addCellstoChamber(),
	// which is a helper of makeChambers(),
	//  are helpers of makeFloor() 
	/// ~~~***~~~
	void generateDefaultFloor(Spawner &spawner, std::string floorFile="defaultfloor.txt"); 
	void generateFloorFromFile(Spawner &spawner, int floorNum, std::shared_ptr<Shade> player, std::string fileName);
	void makeChambers(); 
	void addCellsToChamber(Chamber &chamber, int chamberNumber); 
	// returns the chamber number the player was spawned in 
	int spawnPlayer(Spawner &spawner, std::shared_ptr<Shade> player);
	void spawnItems(Spawner &spawner); 
	void spawnStair(Spawner &spawner, int chamberNum); 
	void spawnEnemies(Spawner &spawner);
	void spawnDragons(Spawner &spawner);
	void connectDragons(); 
	std::vector<std::shared_ptr<Cell>> getAllFreeCells(int x, int y);
	void spawnEverything(Spawner &spawner, std::shared_ptr<Shade> player);
	std::shared_ptr<Cell> chooseTile(Spawner &spawner); 
	// Used when user does not provide a filename as a 
	// command-line argument 

public:
	Floor(int rows=25, int cols=79);

	void makeFloor(Spawner &spawner, int floorNum, 
		std::shared_ptr<Shade> player, std::string floorFile="defaultfloor.txt");

	std::shared_ptr<Cell> getCell(int x, int y); 

	Info getStairInfo(); 

	void passAction(std::string action); 

	void passStats(std::string race, int gold, int curFloor, 
		int hp, int atk, int def); 

	std::shared_ptr<Cell> getFreeCell(int row, int col);

	void moveEnemies();

	friend std::ostream &operator<<(std::ostream &out, const Floor &floor);
};

#endif
