#include "drow.h"

using namespace std;

Drow::Drow(const int x, const int y, 
	const int hp, const int atk, const int def, const string race) :
	Shade{x, y, hp, atk, def, race} {}

void Drow::attackedBy(Character &aggressor){
	float n = 100.00;
        float def = static_cast<float>(getDef());
        float atk = static_cast<float>(aggressor.getAtk());

        int damage = ceil((n/(n + def)) * atk );

	setHp(getHp() - damage);

	if(getHp() <= 0){
		die();
	}
}

void Drow::consumePotion(string stat, const int val){
	int adjVal = val * 1.5;

	if(stat == "hp"){
		setHp(getHp() + adjVal);
		if(getHp() <= 0){
			die();
		} else if (getHp() > getMaxHp()){
			setHp(getMaxHp());
		}
	} else if (stat == "atk") {
		setAtk(getAtk() + adjVal);
		if(getAtk() <= 0){
			setAtk(0);
		}
	} else {
		setDef(getDef() + adjVal);
		if(getDef() <= 0){
			setDef(0);
		}
	}
}

void Drow::resetStats(){
	setAtk(25);
	setDef(15);
}
