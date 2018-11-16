#ifndef INVALID_TYPE
#define INVALID_TYPE
#include <string>

class InvalidType {
	// the invalid character user tried
	// to input to initialize a Cell
	char c;
public: 
	InvalidType(char c); 
	std::string what(); 
};

#endif
