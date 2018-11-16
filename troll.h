#ifndef TROLL_H
#define TROLL_H

#include <string>
#include "shade.h"

class Troll final: public Shade{
	void gainLife();
public:
	Troll( const int x=0, const int y=0, const int hp=120,
		const int atk=25, const int def=15, const std::string race="Troll" );
	void attack( Character &victim ) override; //Gain 5 hp per turn
	void move( const int xChange, const int yChange ) override; //Gain 5 hp per turn
	void consumePotion( std::string stat, const int val ) override; //Gain 5 hp per turn
	void resetStats() override;
};

#endif
