#ifndef PH_H
#define PH_H
#include "potion.h" 
#include <string>
class Shade; 

class PH: public Potion {
	static bool known; 
public: 
	// lose up to 10 hp 
	PH(int x=0, int y=0, std::string stat="hp", int value=-5);

	static bool isKnown(); 

	static void setKnown(bool isKnown);

	void getDrunk(Shade &character) override;

	std::string getDescription() override;
};

#endif
