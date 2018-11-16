#ifndef ITEM_H
#define ITEM_H
#include "subject.h"
class Info; 

class Item: public Subject {
	int x;
	int y;
	char sc;

public:
	Item(char sc, int x=0, int y=0); 

	Info getInfo() const override; 
	
	void setCoords(int x, int y); 

	virtual ~Item() = 0;
};

#endif 
