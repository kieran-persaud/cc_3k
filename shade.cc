#include "info.h"
#include "shade.h"
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

Shade::Shade(const int x, const int y, 
	const int hp, const int atk, const int def, const string race) :
	Character{x, y, hp, atk, def}, gold{0}, maxHp{hp}, race{race} {}

void Shade::loot(Character &victim){
	Info i = victim.getInfo();
	if (i.sc != 'H' && i.sc != 'D' && i.sc != 'M'){
		if(victim.getHp() <= 0){
                	srand(time(NULL));
                	int randNum = rand()% 2 + 1;

                	if(randNum == 1){ pickUpGold(1); }
                	else { pickUpGold(2); }
        	}
	}
}

int Shade::getMaxHp(){ return maxHp; }

int Shade::getGold(){ return gold; }

string Shade::getRace(){ return race; }

void Shade::setCoords( const int x, const int y ){
	setX(x);
	setY(y);
}

void Shade::attack(Character &victim){
	victim.attackedBy(*this);
	loot(victim);
}

void Shade::attackedBy(Character &aggressor){
	Info i = aggressor.getInfo();
	float n = 100.00;
	float def = static_cast<float>(getDef());
	float atk = static_cast<float>(aggressor.getAtk());
	
	int damage = ceil((n/(n + def)) * atk );

	if (i.sc == 'E'){ //Take 2 attacks from elves
        	setHp(getHp() - (2 * damage));	
	} else {
	        setHp(getHp() - damage);
	}

	if(getHp() <= 0){
		die();
	}
}

void Shade::consumePotion(string stat, const int val){
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
}

void Shade::pickUpGold(const int val){ gold += val; }

void Shade::resetStats(){
	setAtk(25);
	setDef(25);
}

Info Shade::getInfo() const{
	Info i{getX(),getY(),sc};
	return i;
}
