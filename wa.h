#ifndef WA_H
#define WA_H
#include "potion.h" 
#include <string>
class Shade; 

class WA: public Potion {
	static bool known; 

public:
	// decrease atk by 5 
	WA(int x=0, int y=0, std::string stat="atk", int value=-5); 

	static bool isKnown(); 

	static void setKnown(bool isKnown);

	void getDrunk(Shade &character) override;

	std::string getDescription() override;
};

#endif
