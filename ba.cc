#include "ba.h"
#include <string> 
#include "shade.h"

// ~~~*** Static Fields/Methods ***~~~
bool BA::known = false; 

bool BA::isKnown() {
	return BA::known; 
}

void BA::setKnown(bool isKnown) { 
	BA::known = isKnown;
}

// ~~~*** End Static Fields/Methods ***~~~


BA::BA(int x, int y, std::string stat, int value): Potion{x, y, stat, value} {}

void BA::getDrunk(Shade &character) {
	setKnown(true); 
	Potion::getDrunk(character); 
}

std::string BA::getDescription(){
	if(isKnown()){ return "BA"; } 
	else { return "Unknown Potion"; }
}
