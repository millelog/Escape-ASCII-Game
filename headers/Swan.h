#ifndef SWAN_H
#define SWAN_H
#include "Actor.h"

class Swan : public Actor{
public:
	Swan();
	bool invalidMove(location, Floor);
	void move(Floor&);
};

#endif