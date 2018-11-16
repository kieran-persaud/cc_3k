#ifndef DROW_H
#define DROW_H

#include <string>
#include "shade.h"

class Drow final: public Shade{
public:
	Drow( const int x=0, const int y=0, const int hp=150,
		const int atk=25, const int def=15, const std::string race="Drow");
	void attackedBy( Character &aggressor ) override; //Don't get hit twice by elves
	void consumePotion( std::string stat, const int val ) override; //x1.5 modifier
	void resetStats() override;
};

#endif
