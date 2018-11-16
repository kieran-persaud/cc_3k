#include "dragon.h"

using namespace std;

Dragon::Dragon(const int x, const int y, const char sc, const int hp, const int atk, const int def) :
	Human{x, y, sc, hp, atk ,def} {}

void Dragon::move( const int xChange, const int yChange) {}
