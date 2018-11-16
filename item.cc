#include "item.h"
#include "info.h"

Item::Item(char sc, int x, int y): x{x}, y{y}, sc{sc} {}

Item::~Item() {}

Info Item::getInfo() const {
	Info info = Info{x, y, sc}; 
	return info; 
}

void Item::setCoords(int xCoord, int yCoord) {
	x = xCoord; 
	y = yCoord; 
}
