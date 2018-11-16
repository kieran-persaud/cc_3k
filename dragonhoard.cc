#include "dragonhoard.h"
#include "shade.h" 

DragonHoard::DragonHoard(int x, int y): Gold{6, x, y} {}

void DragonHoard::getPickedUp(Shade &shade) {
	int amount = Gold::getAmount(); 
	if (!dragon->getExists()) { 
		shade.pickUpGold(amount);
		return;
	}
}

void DragonHoard::getAttacked(Shade &shade) {
	if (dragon && dragon->getExists()) dragon->attack(shade); 
}

void DragonHoard::attachDragon(std::shared_ptr<Human> theDragon) {
	dragon = theDragon; 
}
