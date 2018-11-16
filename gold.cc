#include "gold.h"
#include "shade.h" 

Gold::Gold(int amount, int x, int y, char sc): Item{sc, x, y}, amount{amount} {} 

Gold::~Gold() {}

void Gold::getPickedUp(Shade &shade) {
	shade.pickUpGold(amount); 
	setExists(false); 
}

void Gold::getAttacked(Shade &shade) {}

void Gold::attachDragon(std::shared_ptr<Human> theDragon) {
	
}

int Gold::getAmount() {
	return amount;
}
