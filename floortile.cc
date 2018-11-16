#include "floortile.h"
#include "info.h"
using namespace std; 

FloorTile::FloorTile(int x, int y, char sc, bool canMove): 
Cell{x, y, sc, canMove}, subj{nullptr} {}

void FloorTile::addSubject(shared_ptr<Subject> toAdd) {
	subj = toAdd; 
	notifyObservers();
}

void FloorTile::detachSubject() {
	subj = nullptr; 
	notifyObservers();
}

Info FloorTile::getInfo() const {
	// This is how TextDisplay knows what to print 
	if (subj && subj->getExists()) { 
		// If the Subject is a Player, player still exists
		// if it moves off. 
		// So need to check that subject's coordinates 
		// are the same as my own. 
		Info subjInfo = subj->getInfo(); 
		Info myInfo = Cell::getInfo(); 
		if (subjInfo.x == myInfo.x && subjInfo.y == myInfo.y) {
			return subjInfo; 
		} else {
			return myInfo; 
		}
	}
	return Cell::getInfo(); 
}

bool FloorTile::isOpen() const {
	if(subj && subj->getExists()) {
		return false;
	} 
	return true; 
}

shared_ptr<Subject> FloorTile::getSubject() {
	return subj; 
}

bool FloorTile::canMoveTo() const {
	if (subj && subj->getExists()) {
		Info subjInfo = subj->getInfo(); 
		// If the Subject is Gold or Stair, can move onto the tile 
		if (subjInfo.sc == 'G' || subjInfo.sc == '/') return true; 
		return false; 
	}
	return true;
}
