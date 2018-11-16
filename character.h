#ifndef CHARACTER_H
#define CHARACTER_H

#include <math.h>
#include "subject.h"

class Character: public Subject {
	int x, y;
	int hp, atk, def;

	
protected:
	void setHp( const int newHp );
	void setAtk( const int newAtk );
	void setDef( const int newDef );
	int getX() const;
	int getY() const;
	void setX( const int newX );
	void setY( const int newY );

public:
	Character( int x=0, int y=0, int hp=0, int atk=0, int def=0 );
	virtual ~Character();
	int getHp() const;
	int getAtk() const;
	int getDef() const;
	void die();
	virtual void attack( Character &victim );
	virtual void attackedBy( Character &aggressor );
	virtual void move( const int xChange, const int yChange );
};

#endif
