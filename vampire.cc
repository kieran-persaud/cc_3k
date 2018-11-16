#include "info.h"
#include "vampire.h"

using namespace std;

Vampire::Vampire(const int x, const int y, 
	const int hp, const int atk, const int def, const string race) :
	Shade{x, y, hp, atk, def, race} {}

void Vampire::consumePotion(string stat, const int val){
	if(stat == "hp"){
		setHp(getHp() + val);
		if(getHp() <= 0){
			die();
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
}

void Vampire::attack(Character &victim){
	int vHp = victim.getHp();
	victim.attackedBy(*this);
	if(vHp != victim.getHp()){ //if hit was successful
		Info i = victim.getInfo();
		if(i.sc == 'W'){
			setHp(getHp() - 5);	
		} else {
			setHp(getHp() + 5);	
		}
	}
	loot(victim);
}
