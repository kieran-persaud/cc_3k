#ifndef DRAGONHOARD_H
#define DRAGONHOARD_H
#include "gold.h"
#include <memory>
#include "human.h"
//class Dragon; 
class Shade; 

class DragonHoard: public Gold {
	std::shared_ptr<Human> dragon; 

public:
	DragonHoard(int x=0, int y=0); 
	// TODO: Add method to add a dragon
	// can only pick up if dragon is dead 
	void attachDragon(std::shared_ptr<Human> theDragon) override; 
	void getPickedUp(Shade &shade) override; 
	void getAttacked(Shade &shade) override; 
};

#endif 
