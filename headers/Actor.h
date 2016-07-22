#ifndef ACTOR_H
#define ACTOR_H
#include "Floor.h"

class Actor{
	private:
		char below;
		location start;
		location pos;
	public:
		Actor();
		Actor(location);
		location getStart();
		void setStart(location);
		char getTileBelow();
		void setTileBelow(char);
		location getPos();
		void setPos(location);
		virtual void move(Floor&) {};
};
#endif