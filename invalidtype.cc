#include "invalidtype.h"
#include <sstream> 
using namespace std; 

InvalidType::InvalidType(char c): c{c} {}

string InvalidType::what() {
	char invalidChar = c; 
	std::string toString{1, invalidChar}; 
	string ret; 
	ostringstream ss;
	ss << toString << " does not correspond to a type."; 
	ret = ss.str(); 
	return ret; 
}
