#include "stair.h"
#include "info.h"
using namespace std;

Stair::Stair(int x, int y, char sc): x{x}, y{y}, sc{sc} {}

Stair::~Stair() {}

Info Stair::getInfo() const {
	Info myInfo = Info{x, y, sc}; 
	return myInfo; 
}
