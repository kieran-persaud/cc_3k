#include "cell.h"
#include "info.h"
using namespace std; 

Cell::Cell(int x, int y, char sc, bool canMove): 
x{x}, y{y}, sc{sc}, canMove{canMove} {}

Cell::~Cell() {}

void Cell::addSubject(shared_ptr<Subject> toAdd) {}

void Cell::detachSubject() {}

void Cell::setOpen(bool isOpen) {}

Info Cell::getInfo() const {
	Info info = Info{x, y, sc}; 
	return info;
}

bool Cell::isOpen() const { return false; }

bool Cell::canMoveTo() const {
	return canMove; 
}

shared_ptr<Subject> Cell::getSubject() {
	return nullptr; 
}
