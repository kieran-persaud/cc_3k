#include "info.h"
#include "goblin.h"

using namespace std;

Goblin::Goblin(const int x, const int y, 
	const int hp, const int atk, const int def, const std::string race) :
	Shade{x, y, hp, atk, def, race} {}

void Goblin::attack(Character &victim){
	victim.attackedBy(*this);
	loot(victim);
	if(victim.getHp() <= 0){ //if goblin killed victim
		pickUpGold(5);
        }
}

void Goblin::attackedBy(Character &aggressor){
	Info i = aggressor.getInfo();
	float n = 100.00;
        float def = static_cast<float>(getDef());
        float atk = static_cast<float>(aggressor.getAtk());

        int damage = ceil((n/(n + def)) * atk );

	if(i.sc == 'E'){ //Take 2 attacks from elves
	        setHp(getHp() - (2 * damage));
	} else if (i.sc == 'O'){ //Take 1.5 damage from Orcs
	        setHp(getHp() - (1.5 * damage));
	} else {
	        setHp(getHp() - damage);
	}

	if(getHp() <= 0){
		die();
	}
}

void Goblin::resetStats(){
	setAtk(15);
	setDef(20);
}
