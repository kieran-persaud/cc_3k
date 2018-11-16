#include "potion.h"
#include "shade.h"

Potion::Potion(int x, int y, std::string stat, int value, char sc): 
Item{sc, x, y}, stat{stat}, value{value} {}

void Potion::getDrunk(Shade &character) {
	character.consumePotion(stat, value);
	setExists(false);  
}

Potion::~Potion() {}
