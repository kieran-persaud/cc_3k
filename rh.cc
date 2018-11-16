#include "rh.h"
#include "shade.h" 

bool RH::known = false; 

bool RH::isKnown() {
	return RH::known; 
}

void RH::setKnown(bool isKnown) {
	RH::known = isKnown; 
} 

RH::RH(int x, int y, std::string stat, int value): 
Potion{x, y, stat, value} {}

void RH::getDrunk(Shade &character) {
	setKnown(true); 
	Potion::getDrunk(character); 
} 

std::string RH::getDescription(){
	if(isKnown()){ return "RH"; } 
	else { return "Unknown Potion"; }
}
