#ifndef DOOR_H
#define DOOR_H
#include <memory>
#include "cell.h"
#include "subject.h" 
class Info; 

class Door: public Cell {
	std::shared_ptr<Subject> subj;
public:
	Door(int x, int y, char sc='+', bool canMove=true);
	void addSubject(std::shared_ptr<Subject> toAdd) override; 
	void detachSubject() override;
	bool isOpen() const override;
	std::shared_ptr<Subject> getSubject() override; 
	Info getInfo() const override; 
};

#endif 
