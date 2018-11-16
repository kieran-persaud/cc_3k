#ifndef ELF_H
#define ELF_H

#include "human.h"

class Elf final: public Human{
public:
	Elf( const int x=0, const int y=0, const char sc='E',
		int hp=140, const int atk=30, const int def=10 );
};

#endif
