#include "../headers/Game.h"
#include <cstdlib>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

Game::Game(int argc, char* argv[]){
	if(argc !=2){
		std::cout<<"usage: "<<argv[0]<<" <number of maps>"<<std::endl;
		exit(0);
	}
	if(isInt(argv[1])){
		total_floors = atoi(argv[1]);
	}
	else{
		std::cout<<"usage: "<<argv[0]<<" <number of maps>"<<std::endl;
		exit(0);
	}
	current_floor = 1;
	loadFloor(current_floor);
	loadPlayer();
	loadSwans();
}

bool Game::isInt(char* in){
	for(int i=0; i<strlen(in); i++){
		if(in[i]>57 || in[i]<48)
			return false;
	}
	return true;
}

bool Game::checkRow(std::string in){
	for(int i=0; i<in.size(); i++){
		std::cout<<in[i]<<std::endl;
		if(in[i] != '#' && in[i] != 'D' && in[i] != 'L' && in[i] != 'S' && in[i] != 'K' && in[i] != 'A' && in[i] != 'E' && in[i] != 'X' && in[i] != ' ' && in[i] != 13){
			std::cout<<"invalid tile:" <<in[i]<<std::endl;
			return false;
		}
	}
	std::cout<<std::endl<<"Valid"<<std::endl;
	return true;
}

void Game::loadFloor(int lvl){
	std::stringstream file;
	std::string input;
	file<<"../maps/floor_"<<lvl<<".txt";
	map.open(file.str().c_str(), std::ifstream::in);
	if(!map.is_open()){
		std::cout<<"This file could not be opened!"<<std::endl;
	}
	else{
		std::getline(map, input);
		floor.updateSize(input);
		location size = floor.getSize();

		for(int i=0; i<size.r; i++){
			input = "";
			std::getline(map, input);
			if(checkRow(input)){
				floor.updateRow(input, i);
			}
			else{
				std::cout<<"The map contains invalid characters. Please edit the map file and restart the program."<<std::endl;
				exit(0);
			}
		}

		floor.updateArray();
		
		map.close();
	}

}

void Game::loadPlayer(){
	location start;
	location size = floor.getSize();
	for(int i=0; i<size.r; i++){
		for(int j=0; j<size.c; j++){
			if(floor.getTile(i, j) == 'E'){
				start.r = i;
				start.c = j;
			}
		}
	}
	player.reset();
	player.setTileBelow('E');
	player.setStart(start);
	player.setPos(start);
}

//Finds all 'S' characters on the floor and replaces them with swan actors.
void Game::loadSwans(){
	location start, size;
	size = floor.getSize();
	int k=0;
	for(int i=0; i<size.r; i++){
		for(int j=0; j<size.c; j++){
			if(floor.getTile(i, j) == 'S'){
				k++;
			}
		}
	}
	numSwans = k;
	swans = new Swan[numSwans];
	k=0;
	
	for(int i=0; i<size.r; i++){
		for(int j=0; j<size.c; j++){
			if(floor.getTile(i, j) == 'S'){
				start.r = i;
				start.c = j;
				swans[k].setStart(start);
				swans[k].setPos(start);
				k++;
			}
		}
	}
}

//This function ensures that only valid commands are passed to the game loop.
char Game::getInput(){
	char input;
	
	while(true){
		refreshPage();
		std::cin>>input;
		input = toupper(input);
		if(input == 'W')
			return 'W';
		else if(input == 'A')
			return 'A';
		else if(input == 'S')
			return 'S';
		else if(input == 'D')
			return 'D';
		else if(input == 'E')
			return 'E';
		else if(input == 'U')
			return 'U';
		else if(input == 'Q'){
			std::cout<<"Thanks for playing!"<<std::endl;
			exit(0);
		}
		else{
			std::cout<<"Invalid input. Please try again: ";
		}
	}
}
//Check to see if the next move is a valid position for the actor to move to.
bool Game::invalidMove(char input){
	location deltaPos, next, pos, floorSize;
	pos = player.getPos();
	floorSize = floor.getSize();
	
	//get the next tile from the input
	deltaPos.r = 0;
	deltaPos.c = 0;
	next = pos;

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
	else{
		return false;
	}
	//change the current postion based of directional input
	next.r += deltaPos.r;
	next.c += deltaPos.c;
	char nextTile = floor.getTile(next.r, next.c);
	
	//Check if next tile is valid
	if(nextTile == '#'){
		return true;
	}
	if(nextTile == 'D' && player.getKeys()<1){
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

void Game::printVictory(){
	for(int i=0; i<60; i++){
		std::cout<<std::endl;
	}
	std::cout<<"   _____                            _         _       _   _                 _ "<<std::endl;
	std::cout<<"  / ____|                          | |       | |     | | (_)               | |"<<std::endl;
	std::cout<<" | |     ___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_ _  ___  _ __  ___| |"<<std::endl;
	std::cout<<" | |    / _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \\| '_ \\/ __| |"<<std::endl;
	std::cout<<" | |___| (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | \\__ \\_|"<<std::endl;
	std::cout<<"  \\_____\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|___(_)"<<std::endl;
	std::cout<<"                     __/ |                                                    "<<std::endl;
	std::cout<<"                   _|___/ __          __          __         _                "<<std::endl;
	std::cout<<"                   \\ \\   / /          \\ \\        / /        | |               "<<std::endl;
	std::cout<<"                    \\ \\_/ /__  _   _   \\ \\  /\\  / /__  _ __ | |               "<<std::endl;
	std::cout<<"                     \\   / _ \\| | | |   \\ \\/  \\/ / _ \\| '_ \\| |               "<<std::endl;
	std::cout<<"                      | | (_) | |_| |    \\  /\\  / (_) | | | |_|               "<<std::endl;
	std::cout<<"                      |_|\\___/ \\__,_|     \\/  \\/ \\___/|_| |_(_)               "<<std::endl;


}

//Function call to reprint the map and stats page after an update
void Game::refreshPage(){
	refreshSwans();
	floor.print();

	std::cout<<"Apples: "<<player.getApples()<<"      Keys:"<<player.getKeys()<<std::endl<<"Invincibility Timer: ";
	if(timer == -1)
		std::cout<<" No Apple Eaten "<<std::endl;
	else
		std::cout<<15-timer<<std::endl;

	
	std::cout<<"Enter action: ";
}

//This function is just to insure that the only 'S' chars
//on the floor are where an actual swan is.
void Game::refreshSwans(){
	location size = floor.getSize();
	bool valid = true;
	for(int i=0; i<size.r; i++){
		for(int j=0; j<size.c; j++){
			if(floor.getTile(i, j) == 'S'){
				floor.setTile(i, j, ' ');
			}
		}
	}
	for(int i=0; i<numSwans; i++){
		location swanPos = swans[i].getPos();
		floor.setTile(swanPos.r, swanPos.c, 'S');
	}
}

void Game::play(){
	char input;
	location size = floor.getSize();
	timer = -1;

	//MAIN GAME LOOP
	while(true){
		//Make sure the next move is a valid one, other wise reprompt
		do{
			input = getInput();
		}while(invalidMove(input));

		//invulnerabilty logic
		if(timer>-1){
			timer++;
		}
		if(timer>15){
			player.disableInvuln();
			timer = -1;
		}

		//Different input cases
		//eat an apple
		if(input == 'E'){
			if(player.getApples()>0){
				player.enableInvuln();
				timer = 0;
				player.eatApple();
				for(int i=0; i<numSwans; i++){
					swans[i].move(floor);
				}
			}
		}
		//try to go up either an L or X
		if(input == 'U'){
			if(player.getTileBelow() == 'L'){
				current_floor++;
				//If total num of floors is reached end game.
				if(current_floor > total_floors){
					printVictory();
					std::cout<<std::endl<<"*Max number of levels reached"<<std::endl;
					exit(0);
				}
				//reset game objects
				timer = -1;
				floor.clearArray();
				//reload new game objects for next level
				loadFloor(current_floor);
				loadPlayer();
				loadSwans();
			}
			if(player.getTileBelow() == 'X'){
				printVictory();
				std::cout<<std::endl<<std::endl;
				exit(0);
			}
		}
		//If the input is not one of these special inputs
		//then it is a direction, pass it to player.move
		else{
			for(int i=0; i<numSwans; i++){
				swans[i].move(floor);
			}
			player.move(floor, input);
		}
	}
}
