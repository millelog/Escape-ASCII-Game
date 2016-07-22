#include "../headers/Actor.h"

Actor::Actor(){
	below = ' ';
}

Actor::Actor(location start){
	pos = start;
}
char Actor::getTileBelow(){
	return below;
}

location Actor::getStart(){
	return start;
}

void Actor::setStart(location st){
	start = st;
}

void Actor::setTileBelow(char ch){
	below = ch;
}

void Actor::setPos(location in){
	pos = in;
}

location Actor::getPos(){
	return pos;
}

