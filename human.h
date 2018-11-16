#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include "character.h"
class Info; 

class Human: public Character{
	static bool canMove;
	char sc;
public:
	Human( const int x=0, const int y=0, const char sc='H',
		const int hp=140, const int atk=20, const int def=20 );
	virtual ~Human(); 
	virtual void move( const int xChange, const int yChange ) override;
	Info getInfo() const override;
	static void toggleMove();
	static bool getCanMove();
};

#endif
