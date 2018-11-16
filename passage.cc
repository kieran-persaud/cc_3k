#include "passage.h"
#include "info.h"
using namespace std; 

Passage::Passage(int x, int y, char sc, bool canMove): 
Cell{x, y, sc, canMove}, subj{nullptr} {}

void Passage::addSubject(std::shared_ptr<Subject> toAdd) {
	subj = toAdd; 
	notifyObservers();
}

void Passage::detachSubject() {
	subj = nullptr; 
	notifyObservers();
}

shared_ptr<Subject> Passage::getSubject() {
	return subj; 
}

Info Passage::getInfo() const {
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

bool Passage::isOpen() const {
	if(subj && subj->getExists()) {
		return false;
	} 
	return true; 
}
