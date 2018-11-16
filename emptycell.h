#ifndef EMPTY_CELL_H
#define EMPTY_CELL_H
#include "cell.h"

class EmptyCell: public Cell { 
public:
	EmptyCell(int x, int y, char sc=32, bool canMove=false); 
};

#endif
