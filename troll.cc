#include "troll.h"

using namespace std;

Troll::Troll(const int x, const int y, 
	const int hp, const int atk, const int def, const string race) :
	Shade{x, y, hp, atk, def, race} {}

void Troll::gainLife(){
	setHp(getHp() + 5);
	if(getHp() >= getMaxHp()){
			setHp(getMaxHp());
	}
}

void Troll::attack(Character &victim){
	victim.attackedBy(*this);
	loot(victim);
	gainLife();
}

void Troll::move(const int xChange, const int yChange){
	setX(getX() + xChange);
	setY(getY() + yChange);
	gainLife();
}

void Troll::consumePotion(string stat, const int val){
	if(stat == "hp"){
		setHp(getHp() + val);
		if(getHp() <= 0){
			die();
		} else if (getHp() > getMaxHp()){
			setHp(getMaxHp());
		}
	} else if (stat == "atk") {
		setAtk(getAtk() + val);
		if(getAtk() <= 0){
			setAtk(0);
		}
	} else {
		setDef(getDef() + val);
		if(getDef() <= 0){
			setDef(0);
		}
	}
	gainLife();
}

void Troll::resetStats(){
	setAtk(25);
	setDef(15);
}
