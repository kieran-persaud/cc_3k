#include "character.h"

using namespace std;

int Character::getHp() const { return hp; }

int Character::getAtk() const { return atk; }

int Character::getDef() const { return def; }

void Character::setHp(const int newHp){ hp = newHp; }

void Character::setAtk(const int newAtk){ atk = newAtk; }

void Character::setDef(const int newDef){ def = newDef; }

int Character::getX() const { return x; }

int Character::getY() const { return y; }

void Character::setX(const int newX){ x = newX; }

void Character::setY(const int newY){ y = newY; }

Character::Character(int x, int y, int hp, int atk, int def) : 
	x{x}, y{y}, hp{hp}, atk{atk}, def{def} {}

Character::~Character(){}

void Character::die(){ setExists(false); }

void Character::attack(Character &victim){
	victim.attackedBy(*this);
}

void Character::attackedBy(Character &aggressor){
	float n = 100.00;
        float def = static_cast<float>(getDef());
        float atk = static_cast<float>(aggressor.getAtk());

        int damage = ceil((n/(n + def)) * atk );

	setHp(getHp() - damage);
	
	if(getHp() <= 0){
		die();
	}
}

void Character::move(const int xChange, const int yChange){
	setX(getX() + xChange);
	setY(getY() + yChange);
}
