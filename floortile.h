#ifndef FLOOR_TILE_H
#define FLOOR_TILE_H
#include <memory> 
#include "cell.h"
#include "subject.h"
class Info;

class FloorTile: public Cell {
	std::shared_ptr<Subject> subj;
	bool open = true; 
public:
	FloorTile(int x, int y, char sc='.', bool canMove=true); 
	void addSubject(std::shared_ptr<Subject> subj) override; 
	void detachSubject() override; 
	Info getInfo() const override; 
	bool isOpen() const override; 
	bool canMoveTo() const override; 
	std::shared_ptr<Subject> getSubject() override; 
};

#endif 
