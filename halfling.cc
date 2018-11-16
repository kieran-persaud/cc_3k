#include "halfling.h"

using namespace std;

Halfling::Halfling(const int x, const int y, const char sc, const int hp, const int atk, const int def) :
	Human{x, y, sc, hp, atk ,def} {}

void Halfling::attackedBy(Character &aggressor){
	srand(time(NULL));
	int randNum = rand()% 2 + 1;

	float n = 100.00;
        float def = static_cast<float>(getDef());
        float atk = static_cast<float>(aggressor.getAtk());

        int damage = ceil((n/(n + def)) * atk );

	if(randNum == 1){
		setHp(getHp() - damage);

		if(getHp() <= 0){
			die();
		}
	}
}
