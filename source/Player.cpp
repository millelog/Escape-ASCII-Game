#include "../headers/Player.h"
#include <iostream>

//You fall off the map if you go to the left
//Swans only interesct in the bottom right corner of adjacency

Player::Player(){
	keys = 0;
	apples = 0;
	invulnerable = false;
}

void Player::reset(){
	keys = 0;
	apples = 0;
	invulnerable = false;
}

void Player::enableInvuln(){
	invulnerable = true;
}

void Player::disableInvuln(){
	invulnerable = false;
}

int Player::getApples(){
	return apples;
}

void Player::eatApple(){
	apples--;
}

bool Player::getInvuln(){
	return invulnerable;
}
bool Player::addKey(){
	if(keys<3){
		keys++;
		return true;
	}
	return false;
}

bool Player::addApple(){
	if(apples<2){
		apples++;
		return true;
	}
	return false;
}

//Updates any behavior that are based upon the tile that the player is currently on
void Player::checkCurrentTile(location pos, Floor& floor){
	char currTile = getTileBelow();
	if(currTile == 'K'){
		if(keys<3){
			keys++;
			setTileBelow(' ');
		}
	}
	if(currTile == 'D'){
		keys--;
		setTileBelow(' ');
	}
	if(currTile == 'A'){
		if(apples<2){
			apples++;
			setTileBelow(' ');
		}
	}
	if(currTile == 'S'){
		setTileBelow(' ');
	}
	for(int i=-1; i<2; i++){
		for(int j=-1; j<2; j++){
			if(floor.getTile(pos.r+i, pos.c+j) == 'S' && !invulnerable){
				floor.setTile(pos.r, pos.c, getTileBelow());
				setPos(getStart());
				setTileBelow('E');
			}
		}
	}
}

int Player::getKeys(){
	return keys;
}

void Player::move(Floor &floor, char input){
	location deltaPos, current, next;
	
	current = getPos();
	deltaPos.r = 0;
	deltaPos.c = 0;
	next = current;

	if(input == 'W'){
		deltaPos.r--;
	}
	else if(input == 'A'){
		deltaPos.c--;
	}
	else if(input == 'S'){
		deltaPos.r++;
	}
	else if(input == 'D'){
		deltaPos.c++;
	}

	next.r += deltaPos.r;
	next.c += deltaPos.c;

	floor.setTile(current.r, current.c, getTileBelow());
	setTileBelow(floor.getTile(next.r, next.c));

	setPos(next);
	floor.setTile(next.r, next.c, 'P');
	checkCurrentTile(next, floor);
}