#include "../headers/Floor.h"
#include <string>
#include <cstdlib>
#include <iostream>

Floor::Floor(){
	size.r = 0;
	size.c = 0;
}

Floor::~Floor(){
	if(size.r>0 || size.c>0){
		for(int i=0; i<size.r; i++){
			delete [] tiles[i];
		}
		delete [] tiles;
	}
	delete [] rows;
}

Floor::Floor(const Floor &f){
	size = f.getSize();
	tiles = new char*[size.r];
	for(int i=0; i<size.r; i++){
		tiles[i] = new char[size.c];
	}
	rows = new std::string[size.r];

	for(int i=0; i<size.r; i++){
		for(int j=0; j<size.c; j++){
			tiles[i][j] = f.getTile(i, j);
		}
		rows[i] = f.getRow(i);
	}
}

void Floor::updateArray(){
	//clearArray();
	
	for(int i=0; i<size.r; i++){
		for(int j=0; j<size.c; j++){
			tiles[i][j] = rows[i][j];
		}
	}
}

char** Floor::getBoard(){
	return tiles;
}

char Floor::getTile(int r, int c) const{
	return tiles[r][c];
}

void Floor::setTile(int r, int c, char ch){
	tiles[r][c] = ch;
	rows[r][c] = ch;
}

void Floor::updateRow(std::string in, int row){
	rows[row] = in;
}

std::string Floor::getRow(int r) const{
	return rows[r];
}

void Floor::clearArray(){
	if(size.r>0 || size.c>0){
		for(int i=0; i<size.r; i++){
			delete [] tiles[i];
		}
		delete [] tiles;
		delete [] rows;
	}
}

void Floor::updateSize(std::string in){
	bool first = false;
	if(size.r == 0 || size.c == 0)
		first = true;
	for(int i=0; i<in.size(); i++){
		if(in[i] == ' '){
			std::string row = in.substr(0,i);
			std::string col = in.substr(i+1, in.size());
			size.r = atoi(row.c_str());
			size.c = atoi(col.c_str());
		}
	}
	tiles = new char*[size.r];
	for(int i=0; i<size.r; i++){
		tiles[i] = new char[size.c];
	}
	rows = new std::string[size.r];
}

void Floor::print(){
	for(int i=0; i<60; i++){
		std::cout<<std::endl;
	}
	for(int i=0; i<size.r; i++){
		for(int j=0; j<size.c; j++){
			std::cout<<tiles[i][j];
		}
		std::cout<<std::endl;
	}

}

void Floor::printRows(){
	for(int i=0; i<size.r; i++){
		std::cout<<rows[i]<<std::endl;
	}
}

location Floor::getSize() const{
	return size;
}