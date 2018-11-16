#include "merchant.h"

using namespace std;

bool Merchant::aggroed = false;

Merchant::Merchant(const int x, const int y, const char sc, const int hp, const int atk, const int def) :
	Human{x, y, sc, hp, atk ,def} {}

void Merchant::attack(Character &victim){
	if(aggroed){
		victim.attackedBy(*this);
	}
}

void Merchant::attackedBy(Character &aggressor){
	aggroed = true;

	float n = 100.00;
        float def = static_cast<float>(getDef());
        float atk = static_cast<float>(aggressor.getAtk());

        int damage = ceil((n/(n + def)) * atk );

        setHp(getHp() - damage);

	if(getHp() <= 0){
		die();
	}
}
