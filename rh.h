#ifndef RH_H
#define RH_H
#include "potion.h" 
#include <string>
class Shade; 

class RH: public Potion {
	static bool known; 
public:
	// restore health by up to 10 
	RH(int x=0, int y=0, std::string stat="hp", int value=10);

	static bool isKnown(); 

	static void setKnown(bool isKnown);

	void getDrunk(Shade &character) override;

	std::string getDescription() override;
};

#endif
