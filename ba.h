#ifndef BA_H
#define BA_H 
#include "potion.h"
#include <string>
class Shade; 

class BA: public Potion {
	static bool known; 
	
public:
	// increase ATK by 5
	BA(int x=0, int y=0, std::string stat="atk", int value=5); // pass in coordinates

	void getDrunk(Shade &character) override; 

	static bool isKnown(); 
	
	static void setKnown(bool isKnown); 

	std::string getDescription() override;
};

#endif
