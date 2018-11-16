#ifndef BD_H
#define BD_H
#include "potion.h"
#include <string>
class Shade; 

class BD: public Potion {
	static bool known; 
public:
	// increase def by 5 
	BD(int x=0, int y=0, std::string stat="def", int value=5); 

	static bool isKnown(); 

	static void setKnown(bool isKnown); 

	void getDrunk(Shade &character) override;

	std::string getDescription() override;
};

#endif
