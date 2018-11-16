#include "wa.h"
#include "shade.h"

bool WA::known = false; 

bool WA::isKnown() {
	return WA::known; 
}

void WA::setKnown(bool isKnown) {
	WA::known = isKnown; 
} 

WA::WA(int x, int y, std::string stat, int value): Potion{x, y, stat, value} {}

void WA::getDrunk(Shade &character) {
	setKnown(true); 
	Potion::getDrunk(character); 
} 

std::string WA::getDescription(){
	if(isKnown()){ return "WA"; } 
	else { return "Unknown Potion"; }
}
