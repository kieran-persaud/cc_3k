#ifndef PASSAGE_H
#define PASSAGE_H
#include <memory> 
#include "cell.h"
#include "subject.h"
class Info; 

class Passage: public Cell {
	std::shared_ptr<Subject> subj;
public:
	Passage(int x, int y, char sc='#', bool canMove=true);
	void addSubject(std::shared_ptr<Subject> toAdd) override;
	void detachSubject() override; 
	bool isOpen() const override;
	std::shared_ptr<Subject> getSubject() override; 
	Info getInfo() const override; 
};

#endif 
