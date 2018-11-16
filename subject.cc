#include "subject.h"
#include "info.h"
using namespace std; 

void Subject::attach(shared_ptr<Observer> o) {
	observers.emplace_back(o); 
}

void Subject::notifyObservers() {
	for(auto &o:observers) { 
		o->notify(*this); 
	}
}

Subject::~Subject() {}

bool Subject::getExists() {
	return exists; 
}

void Subject::setExists(bool doesExist) {
	exists = doesExist; 
}
