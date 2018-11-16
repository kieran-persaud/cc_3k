#ifndef WALL_H
#define WALL_H
#include "cell.h"

class Wall: public Cell {
public:
	Wall(int x, int y, char sc, bool canMove=false); 
};

#endif 
