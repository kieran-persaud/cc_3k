#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>
#include "observer.h"
#include "cell.h"
#include "info.h"

class Cell;

class TextDisplay: public Observer {
	std::vector<std::vector<char>> theDisplay;
	const int rows;
	const int cols;

	//stats
	std::string race;
	int gold;
	int curFloor;
	int hp;
	int atk;
	int def;
	std::string action;

public:
	TextDisplay(int rows=25, int cols=79);
	~TextDisplay();	
	void updateStats(std::string race, int gold, int curFloor, int hp, int atk, int def);
	void updateAction(std::string action);
	void notify(Subject &whoNotified) override;
	friend std::ostream &operator<<(std::ostream &out, TextDisplay &std);
};

#endif
