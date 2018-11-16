#ifndef VAMPIRE_H
#define VAMPIRE_H

#include <string>
#include "shade.h"

class Vampire final: public Shade{
public:
	Vampire( const int x=0, const int y=0, const int hp=50,
		const int atk=25, const int def=25, const std::string race="Vampire" );
	void consumePotion( std::string stat, const int val ) override; //No hp Cap
	void attack( Character &victim ) override; //Gain 5 hp on successful hit
};

#endif
