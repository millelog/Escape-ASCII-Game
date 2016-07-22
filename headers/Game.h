#ifndef GAME_H
#define GAME_H
#include <fstream>
#include <iostream>
#include "Swan.h"
#include "Floor.h"
#include "Player.h"

class Game{
private:
	std::ifstream map;
	int total_floors, current_floor, timer, numSwans;
	Floor floor;
	Swan* swans;
	Player player;
public:
	Game(int, char*[]);
	void printVictory();
	void refreshPage();
	void loadFloor(int);
	void loadPlayer();
	void loadSwans();
	char getInput();
	bool isInt(char*);
	bool checkRow(std::string);
	bool invalidMove(char);
	void refreshSwans();
	void play();

};
#endif