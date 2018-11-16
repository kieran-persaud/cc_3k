#ifndef GOBLIN_H
#define GOBLIN_H

#include <string>
#include "shade.h"

class Goblin final: public Shade{
public:
	Goblin( const int x=0, const int y=0, const int hp=110,
		const int atk=15, const int def=20, const std::string race="Goblin" );
	void attack( Character &victim ) override; //Get 5 gold per kill
	void attackedBy( Character &agressor ) override; //50% more damage from Orcs
	void resetStats() override;
};

#endif
