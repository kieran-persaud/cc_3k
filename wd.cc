#include "wd.h"
#include "shade.h"

bool WD::known = false; 

bool WD::isKnown() {
	return WD::known; 
}

void WD::setKnown(bool isKnown) {
	WD::known = isKnown; 
} 

WD::WD(int x, int y, std::string stat, int value): Potion{x, y, stat, value} {}

void WD::getDrunk(Shade &character) {
	setKnown(true); 
	Potion::getDrunk(character); 
} 

std::string WD::getDescription(){
	if(isKnown()){ return "WD"; } 
	else { return "Unknown Potion"; }
}
