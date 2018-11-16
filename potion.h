#ifndef POTION_H
#define POTION_H
#include "item.h" 
#include <string>
class Shade;

class Potion: public Item {
	std::string stat;
	int value;

public:
	Potion(int x, int y, std::string stat, int value, char sc='P'); 

	virtual ~Potion() = 0; 

	virtual void getDrunk(Shade &shade);

	virtual std::string getDescription() = 0;
};

#endif
