#include "human.h"
#include "info.h"

using namespace std;

bool Human::canMove = true;

Human::Human(const int x, const int y, const char sc, const int hp, const int atk, const int def) :
	Character{x, y, hp, atk, def}, sc{sc} {}

bool Human::getCanMove() {
	return canMove; 
}

Human::~Human() {}

void Human::move( const int xChange, const int yChange ){
	if(getCanMove()){
		setX(getX() + xChange);
		setY(getY() + yChange);
	}
}

Info Human::getInfo() const {
	Info i{getX(),getY(),sc};
	return i;
}

void Human::toggleMove(){ canMove = !canMove; }
