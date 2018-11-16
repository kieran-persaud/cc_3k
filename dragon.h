#ifndef DRAGON_H
#define DRAGON_H

#include "human.h"

class Dragon final: public Human{
public:
	Dragon( const int x=0, const int y=0, const char sc='D',
		int hp=150, const int atk=20, const int def=20 );
	void move( const int xChange, const int yChange) override; //don't move
};

#endif
