#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "floor.h" 
#include "character.h"
#include "shade.h"
#include "spawner.h"

class GameController {
	std::unique_ptr<Floor> floor; //vector of cell pointers
	int curFloor; //start at 1
	std::shared_ptr<Shade> p; 
	Spawner spawner = Spawner();
	std::string file ="";
	bool gameOver = false;

	//helpers
	bool playerOnStairs(int x, int y);
	void checkBlock(int x, int y);
	void checkRadius();
	std::vector<int> parseDir(std::string dir);
	bool validDir(std::string dir);
	std::string getDirString(std::string dir);
	bool hasSubject(std::string dir);

public:
	GameController(std::string file);
	void startGame();
	void print();
	void printScore();

	//accessors and mutators;
	void setGameOver(bool);
	bool getGameOver();

	//command interpreters
	bool movePlayer(std::string dir);
	bool usePotion(std::string dir);
	bool attackEnemy(std::string dir);
	bool makePlayer(std::string race);
	void freezeEnemies();
};

#endif
