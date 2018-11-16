#include "ph.h"

bool PH::known = false; 

bool PH::isKnown() {
	return PH::known; 
}

void PH::setKnown(bool isKnown) {
	PH::known = isKnown; 
} 

PH::PH(int x, int y, std::string stat, int value): Potion{x, y, stat, value} {}

void PH::getDrunk(Shade &character) {
	setKnown(true); 
	Potion::getDrunk(character); 
} 

std::string PH::getDescription(){
	if(isKnown()){ return "PH"; } 
	else { return "Unknown Potion"; }
}
