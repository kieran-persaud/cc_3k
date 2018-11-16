#include "door.h"
#include "info.h"
using namespace std;

Door::Door(int x, int y, char sc, bool canMove): Cell{x, y, sc, canMove}, subj{nullptr} {}

void Door::addSubject(std::shared_ptr<Subject> toAdd) {
	subj = toAdd; 
	notifyObservers();
}

void Door::detachSubject() {
	subj = nullptr; 
	notifyObservers();
}

shared_ptr<Subject> Door::getSubject() {
	return subj; 
}

Info Door::getInfo() const {
	if (subj && subj->getExists()) { 
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

bool Door::isOpen() const {
	if(subj && subj->getExists()) {
		return false;
	} 
	return true; 
}
