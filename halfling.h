#ifndef HALFLING_H
#define HALFLING_H

//#include <ctime> //For random number gen
#include <cstdlib>
#include "human.h"


class Halfling final: public Human{
	static bool aggroed;
public:
	Halfling( const int x=0, const int y=0, const char sc='L',
		int hp=100, const int atk=15, const int def=20 );
	void attackedBy( Character &aggressor ) override; //50% chance to dodge
};

#endif
