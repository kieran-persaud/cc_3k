#ifndef OBSERVER_H
#define OBSERVER_H 
class Subject; 

class Observer {
public:
	// TODO: in q3 it forward-declared Cell? Idk why...
	virtual void notify(Subject &whoNotified) = 0;
	//virtual SubscriptionType subType() const = 0;
	virtual ~Observer() = default;
};

#endif 
