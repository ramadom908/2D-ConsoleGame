#ifndef LEVEL_H
#define LEVEL_H

#include "stdafx.h"

class Level
{
public:
	Level(void);

	void load();
	void drawMap(void);

	void setColor(int colorBack, int colorFore);

	void draw(int _x, int _y, int _value);

	//variabile 
	int map[MAX_X][MAX_Y][2]; // asta este harta jocului

	int debug;

private:
	COORD point;

};

#endif