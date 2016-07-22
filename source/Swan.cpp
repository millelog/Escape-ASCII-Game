#include "../headers/Swan.h"
#include <cstdlib>

Swan::Swan(){

}

bool Swan::invalidMove(location next, Floor floor){
	location floorSize = floor.getSize();
	char nextTile = floor.getTile(next.r, next.c);
	if(nextTile == '#'){
		return true;
	}
	if(nextTile == 'D'){
		return true;
	}
	if(nextTile == 'E'){
		return true;
	}
	if(next.r<0 || next.c<0 || next.r>floorSize.r || next.c>floorSize.c){
		return true;
	}
	return false;
}

void Swan::move(Floor& floor){
	location deltaPos, current, next;
	int input;
	current = getPos();
	
	do{
		deltaPos.r = 0;
		deltaPos.c = 0;
		next = current;
		input = rand()%4;
		if(input == 0){
			deltaPos.r--;
		}
		else if(input == 1){
			deltaPos.c--;
		}
		else if(input == 2){
			deltaPos.r++;
		}
		else if(input == 3){
			deltaPos.c++;
		}

		next.r += deltaPos.r;
		next.c += deltaPos.c;
	}while(invalidMove(next, floor));

	floor.setTile(current.r, current.c, getTileBelow());
	if(getTileBelow() == 'P')
		floor.setTile(current.r, current.c, ' ');
	setTileBelow(floor.getTile(next.r, next.c));

	setPos(next);
	floor.setTile(next.r, next.c, 'S');
}