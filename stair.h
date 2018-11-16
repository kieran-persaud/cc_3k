#ifndef STAIR_H
#define STAIR_H
#include "subject.h"
class Info; 

class Stair: public Subject {
	int x, y;
	char sc;
public: 
	Stair(int x=0, int y=0, char sc='\\'); 
	~Stair(); 
	Info getInfo() const override; 
};

#endif
