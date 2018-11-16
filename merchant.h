#ifndef MERCHANT_H
#define MERCHANT_H

#include "human.h"

class Merchant final: public Human{
	static bool aggroed;
public:
	Merchant( const int x=0, const int y=0, const char sc='M',
		int hp=30, const int atk=70, const int def=5 );
	void attack( Character &victim ) override; //Only attacks if aggro
	void attackedBy( Character &aggressor ) override; //Becomes Aggro
};

#endif
