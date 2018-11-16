#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory> 
#include "observer.h"
class Info; 

class Subject {
	// To check Potions, Gold, Characters  
	bool exists = true; 
	std::vector<std::shared_ptr<Observer>> observers;
public:
	void attach(std::shared_ptr<Observer> o);  
	void detachObserver(); 
	void clearObservers();
	void notifyObservers();
	virtual Info getInfo() const = 0;
	bool getExists(); 
	void setExists(bool doesExist); 
	virtual ~Subject() = 0;
};

#endif
