#ifndef GOLD_H
#define GOLD_H
#include "item.h"
#include <memory> 
#include "human.h"
class Shade;

class Gold: public Item {
	int amount;

public:
	Gold(int amount, int x=0, int y=0, char sc='G'); 

	virtual ~Gold() = 0; 

	virtual void getPickedUp(Shade &shade);

	virtual void getAttacked(Shade &shade); 

	virtual void attachDragon(std::shared_ptr<Human> theDragon); 

	int getAmount(); 
};

#endif 
