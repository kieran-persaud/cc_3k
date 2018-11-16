#ifndef WD_H
#define WD_H
#include "potion.h" 
#include <string>
class Shade; 

class WD: public Potion {
	static bool known; 

public:
	// decrease def by 5
	WD(int x=0, int y=0, std::string stat="def", int value=-5);

	static bool isKnown(); 

	static void setKnown(bool isKnown);

	void getDrunk(Shade &character) override;

	std::string getDescription() override;
};

#endif
