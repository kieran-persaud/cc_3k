#ifndef CELL_H
#define CELL_H
#include <vector>
#include <memory> 
#include "subject.h"
class Info;

class Cell: public Subject {
	int x;
	int y; 
	char sc;
	// I think this should only be on floor tiles
	//unique_ptr<Subject> subj; 
	// Coordinates (x,y): 
	bool canMove;	

public:
	// TODO: method for returning info on the cell 
	// Note: This is virtual so that when we call
	// FloorTile's getInfo() it can return
	// the Subject's info, if it has a Subject. 
	virtual Info getInfo() const;

	Cell(int x, int y, char sc, bool canMove); 

	virtual ~Cell(); 

	// Next few functions are virtual
	// so they will call FloorTile/Door/Passage's versions 
	virtual void addSubject(std::shared_ptr<Subject> toAdd); 

	virtual void detachSubject(); 

	// This is used when spawning - 
	// returns whether or not we can spawn on the Cell. 
	virtual bool isOpen() const; 

	virtual void setOpen(bool isOpen); 

	// This returns if we can move onto the Cell.
	// It's different from spawning, because
	// if a Cell has anything on it, we can't spawn on it.
	// But if a Cell has Gold or Stair on it, Player
	// can move to it. 
	virtual bool canMoveTo() const; 

	virtual std::shared_ptr<Subject> getSubject(); 

	// TODO Do I need this 
};

#endif
