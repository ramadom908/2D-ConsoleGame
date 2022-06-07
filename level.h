#ifndef LEVEL_H
#define LEVEL_H

#include "stdafx.h"

//std::ifstream cin1("in.txt");
//
//std::ofstream cout1("out.txt");

class Level
{
public:
	Level(void);

	void load();
	void drawMap(void);

	

	void draw(int _x, int _y, int _value);

	//variabile 
	int map[MAX_X][MAX_Y][2]; // asta este harta jocului

	int mapTranspusa[MAX_X][MAX_Y];

	int mapCitita[MAX_Y][MAX_X];


	//std::ifstream cin1;
	//std::ofstream cout1;


	int debug;

private:
	//Defines the coordinates of a character cell in a console screen buffer. 
	//The origin of the coordinate system (0,0) is at the top, left cell of the buffer.
	COORD point;
	
};

#endif