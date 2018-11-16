#ifndef SHADE_H
#define SHADE_H

#include <string>
#include "character.h"

struct Info;

class Shade: public Character{
	const char sc = '@';
	int gold;
	int maxHp;
	bool goToNextLevel;
	std::string race;

protected:
	int getMaxHp();
	void loot( Character &victim );

public:
	Shade( const int x=0, const int y=0, const int hp=125,
		const int atk=25, const int def=25, const std::string race="Shade" );
	int getGold();
	std::string getRace();
	void setCoords( const int x, const int y );
	virtual void attack( Character &victim ) override;
	virtual void attackedBy( Character &aggressor ) override;
	virtual void consumePotion( std::string stat, const int val ); //stats are hp, atk, def
	void pickUpGold( const int val );
	virtual void resetStats();
	Info getInfo() const override;
};

#endif
