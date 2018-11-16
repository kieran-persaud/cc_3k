#include "bd.h"
#include "shade.h"

bool BD::known = false; 

bool BD::isKnown() {
	return BD::known; 
}

void BD::setKnown(bool isKnown) {
	BD::known = isKnown; 
}

BD::BD(int x, int y, std::string stat, int value): Potion{x, y, stat, value} {}

void BD::getDrunk(Shade &character) {
	setKnown(true); 
	Potion::getDrunk(character); 
} 

std::string BD::getDescription(){
	if(isKnown()){ return "BD"; } 
	return "Unknown Potion";
}
