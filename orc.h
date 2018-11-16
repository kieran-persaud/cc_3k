#ifndef ORC_H
#define ORC_H

#include "human.h"

class Orc final: public Human{
public:
	Orc( const int x=0, const int y=0, const char sc='O',
		int hp=180, const int atk=30, const int def=25 );
};

#endif
