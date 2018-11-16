#ifndef DWARF_H
#define DWARF_H

#include "human.h"

class Dwarf final: public Human{
public:
	Dwarf( const int x=0, const int y=0, const char sc='W',
		int hp=100, const int atk=20, const int def=30 );
};

#endif
