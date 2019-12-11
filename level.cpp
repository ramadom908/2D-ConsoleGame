#include "stdafx.h"
#include "level.h"
#include <time.h>

Level::Level(void)
{
	debug = 12;
}

void Level::draw(int _x, int _y, int _value)
{
	point.X = _x;
	point.Y = _y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);

	switch (_value)
	{
	case ROCK:
	{
		setColor(black, 3);
	} break;
	case SAND:
	{
		//setColor(black, 6);
		setColor(black, 8);
	} break;
	case WALL:
	{
		setColor(8, black);
	} break;
	case EMPTY:
	{
		setColor(0, black);
	} break;
	case STONE:
	{
		setColor(black, 3); //11
	} break;
	case PLAYER:
	{
		setColor(black, 14);
	} break;
	case ENEMY:
	{
		setColor(12, 14);
	} break;
	case DIAMOND:
	{
		setColor(black, 11);
	} break;
	}
	std::cout << (char)_value;
}

void Level::load()
{
	srand(time(NULL));

	// Fill the playing field
	//codul de mai jos umple ecranul cu piatra pe margini si
	//in interiorul zonei de joaca(play field) cu nisip
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++)
		{
			map[x][y][1] = -1;

			if (((x > 1 && y > 2) && (x < MAX_X - 2 && y < MAX_Y - 2)))
			{
				int value = rand() % 9 + 1;

				if (value < 7) map[x][y][0] = SAND;
				else if (value < 8) map[x][y][0] = SAND;
				else if (value < 9) map[x][y][0] = SAND;
				else // daca las else-ul asta aici umple toata zona cu nisip, 
				{	 // daca il comentez baga niste locuri goale
					map[x][y][0] = SAND;

				}
			}//TODO: for debug map =x ,  inca nu merge, pentru ca la afisare se afiseaza char
			else map[x][y][0] = ROCK;

		}
	}
	// Middle, empty box
/*	for (int y=9; y<17; y++)
		for (int x=16; x<34; x++)
		{
			map[x][y][0] = EMPTY;
			map[x+30][y][0] = EMPTY;
		}*/

		// int a[2][3] = { { 11, 12, 13 }, { 21, 22, 23 } }
		// const int MAX_X = 80;
		// const int MAX_Y = 25;
	int temp[76/*76*/][20] = { { SAND,SAND,SAND,SAND,DIAMOND,DIAMOND,WALL,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND },
							{ SAND,SAND,SAND,SAND,STONE,STONE,WALL,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND,SAND },
							{ SAND,SAND,SAND,SAND,SAND,STONE,WALL,SAND,SAND,WALL,SAND,SAND,WALL,WALL,WALL,WALL,WALL,WALL,SAND,SAND },
							{ SAND,SAND,SAND,EMPTY,DIAMOND,STONE,WALL,SAND,SAND,WALL,STONE,SAND,WALL,EMPTY,DIAMOND,DIAMOND,DIAMOND,WALL,SAND,SAND },
							{ SAND,SAND,SAND,SAND,SAND,DIAMOND,WALL,SAND,SAND,WALL,SAND,SAND,WALL,EMPTY,EMPTY,STONE,DIAMOND,WALL,SAND,SAND },
							{ STONE,SAND,SAND,SAND,SAND,STONE,WALL,SAND,SAND,WALL,SAND,SAND,WALL,EMPTY,EMPTY,EMPTY,STONE,WALL,SAND,SAND },
							{ SAND,SAND,SAND,WALL,SAND,SAND,WALL,SAND,SAND,WALL,SAND,STONE,WALL,EMPTY,EMPTY,EMPTY,EMPTY,WALL,SAND,SAND },
							{ SAND,SAND,SAND,WALL,SAND,SAND,WALL,SAND,SAND,WALL,SAND,STONE,WALL,EMPTY,EMPTY,EMPTY,EMPTY,WALL,SAND,SAND },
							{ SAND,EMPTY,STONE,WALL,SAND,SAND,WALL,SAND,SAND,WALL,SAND,SAND,WALL,EMPTY,EMPTY,EMPTY,EMPTY,WALL,SAND,SAND },
							{ SAND,SAND,DIAMOND,WALL,SAND,SAND,WALL,SAND,SAND,WALL,SAND,SAND,WALL,EMPTY,EMPTY,EMPTY,EMPTY,WALL,SAND,SAND },
		//======================================================================================================
		{ SAND,SAND,SAND,WALL,SAND,SAND/**/,WALL/**/,SAND,SAND,WALL,SAND,SAND,WALL,/**/EMPTY/**/,EMPTY,EMPTY,EMPTY,WALL,SAND,SAND },
		{ SAND,SAND,SAND,WALL,SAND,SAND/**/,WALL/**/,SAND,SAND,WALL,SAND,SAND,WALL,/**/ENEMY/**/,EMPTY,EMPTY,EMPTY,WALL,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,WALL,SAND,SAND,WALL,/**/WALL/**/,WALL,STONE,SAND,WALL,SAND,SAND },
		{ SAND,SAND,SAND,SAND,EMPTY,SAND/**/,WALL/**/,SAND,SAND,WALL,SAND,SAND,SAND,/**/SAND/**/,STONE,SAND,SAND,WALL,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,WALL,STONE,SAND,SAND,/**/SAND/**/,SAND,SAND,EMPTY,WALL,SAND,SAND },
		{ STONE,SAND,STONE,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,WALL,WALL,WALL,WALL,/**/WALL/**/,WALL,WALL,WALL,WALL,SAND,SAND },
		{ STONE,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/SAND/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ STONE,STONE,SAND,SAND,SAND,STONE/**/,WALL/**/,STONE,SAND,SAND,SAND,SAND,SAND,/**/SAND/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ WALL,WALL,WALL,STONE,WALL,WALL/**/,WALL/**/,WALL,WALL,WALL,WALL,WALL,WALL,/**/WALL/**/,WALL,WALL,STONE,WALL,WALL,WALL },
		{ STONE,SAND,SAND,SAND,STONE,STONE/**/,WALL/**/,STONE,STONE,STONE,SAND,SAND,EMPTY,/**/WALL/**/,SAND,STONE,STONE,SAND,SAND,SAND },
		//======================================================================================================
		{ SAND,SAND,SAND,SAND,SAND,DIAMOND/**/,WALL/**/,STONE,STONE,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,DIAMOND,EMPTY,EMPTY,SAND,SAND },
		{ SAND,SAND,WALL,SAND,SAND,SAND/**/,WALL/**/,STONE,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,STONE,SAND },
		{ SAND,SAND,WALL,SAND,STONE,SAND/**/,WALL/**/,STONE,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ STONE,SAND,WALL,SAND,EMPTY,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,WALL,SAND,SAND,SAND },
		{ SAND,SAND,WALL,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,WALL,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,ENEMY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,SAND,SAND,WALL,SAND,SAND,SAND },
		{ SAND,SAND,SAND,WALL,SAND,SAND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,STONE,SAND,WALL,SAND,SAND,SAND },
		{ SAND,SAND,SAND,WALL,SAND,SAND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,SAND,SAND,WALL,SAND,SAND,SAND },
		{ SAND,SAND,SAND,WALL,SAND,SAND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,SAND,SAND,WALL,STONE,SAND,SAND },
		{ SAND,SAND,STONE,WALL,SAND,SAND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,SAND,SAND,WALL,SAND,SAND,SAND },
		// ======================================================================================================
		{ SAND,SAND,EMPTY,STONE,SAND,DIAMOND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,DIAMOND,SAND,WALL,WALL,WALL,SAND },
		{ SAND,SAND,SAND,STONE,WALL,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,STONE,SAND,WALL,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,WALL,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,STONE,SAND,SAND,SAND,EMPTY,SAND },
		{ SAND,SAND,SAND,SAND,WALL,SAND/**/,WALL/**/,SAND,SAND,EMPTY,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,EMPTY,SAND,SAND,WALL,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,STONE,STONE,STONE,SAND,SAND,SAND },
		{ SAND,STONE,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,STONE,/**/WALL/**/,STONE,SAND,STONE,SAND,SAND,SAND },
		{ STONE,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,STONE,STONE,/**/WALL/**/,STONE,STONE,STONE,STONE,SAND,SAND },
		{ WALL,WALL,WALL,SAND,WALL,WALL/**/,WALL/**/,WALL,WALL,WALL,WALL,WALL,WALL,/**/WALL/**/,WALL,WALL,SAND,WALL,WALL,WALL },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,STONE,SAND,SAND,SAND,SAND,STONE },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,STONE,SAND,/**/WALL/**/,EMPTY,SAND,SAND,SAND,SAND,STONE },
		// =============================================================================================================================
		{ SAND,SAND,SAND,SAND,SAND,DIAMOND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,DIAMOND,SAND,SAND,WALL,SAND,SAND },
		//{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,STONE,SAND,SAND,SAND,STONE },
		{ SAND,WALL,WALL,WALL,WALL,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,STONE,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,SAND,STONE,WALL,WALL,WALL,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,STONE,SAND,WALL,SAND,SAND,SAND },
		{ SAND,SAND,STONE,SAND,SAND,SAND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,STONE,SAND,SAND,SAND,STONE,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,STONE },
		// =============================================================================================================================
		//{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,STONE },
		{ SAND,SAND,SAND,SAND,EMPTY,DIAMOND/**/,WALL/**/,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,ENEMY,/**/WALL/**/,DIAMOND,SAND,SAND,SAND,SAND,STONE },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,STONE,SAND,SAND,SAND,SAND,STONE },
		{ SAND,WALL,WALL,WALL,WALL,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,EMPTY,STONE,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,STONE,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,STONE,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,STONE,STONE,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,STONE,STONE,SAND,SAND,SAND/**/,WALL/**/,SAND,STONE,SAND,SAND,SAND,STONE,/**/WALL/**/,SAND,SAND,WALL,SAND,SAND,SAND },
		{ SAND,EMPTY,SAND,SAND,SAND,SAND/**/,WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,STONE,WALL,SAND,SAND,SAND },
		{ WALL,WALL,WALL,SAND,WALL,WALL/**/,WALL/**/,WALL,WALL,WALL,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ STONE,STONE,SAND,SAND,SAND,STONE/**/,STONE/**/,SAND,SAND,SAND,SAND,SAND,STONE,/**/WALL/**/,SAND,SAND,SAND,SAND,STONE,WALL },
		// ===========================================================================================================================
		{ STONE,SAND,SAND,SAND,SAND,DIAMOND/**/,SAND/**/,SAND,SAND,SAND,SAND,SAND,STONE,/**/WALL/**/,DIAMOND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,STONE/**/,SAND/**/,SAND,SAND,SAND,SAND,SAND,STONE,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,SAND/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,STONE,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,SAND/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,EMPTY,SAND,SAND,SAND,SAND },
		{ SAND,SAND,EMPTY,EMPTY,EMPTY,EMPTY/**/,EMPTY/**/,EMPTY,EMPTY,EMPTY,ENEMY,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,STONE,SAND },
		{ SAND,SAND,EMPTY,EMPTY,EMPTY,EMPTY/**/,EMPTY/**/,EMPTY,EMPTY,EMPTY,EMPTY,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,STONE,WALL,SAND },
		{ SAND,SAND,EMPTY,EMPTY,EMPTY,EMPTY/**/,EMPTY/**/,EMPTY,EMPTY,EMPTY,EMPTY,SAND,SAND,/**/WALL/**/,STONE,SAND,SAND,SAND,WALL,SAND },
		{ SAND,SAND,EMPTY,EMPTY,EMPTY,EMPTY/**/,EMPTY/**/,EMPTY,EMPTY,EMPTY,EMPTY,SAND,SAND,/**/WALL/**/,STONE,STONE,SAND,SAND,SAND,SAND },
		{ SAND,SAND,EMPTY,EMPTY,EMPTY,EMPTY/**/,EMPTY/**/,EMPTY,EMPTY,EMPTY,EMPTY,SAND,SAND,/**/WALL/**/,STONE,STONE,SAND,SAND,SAND,SAND },
		{ SAND,SAND,EMPTY,EMPTY,EMPTY,EMPTY/**/,EMPTY/**/,EMPTY,EMPTY,EMPTY,EMPTY,SAND,SAND,/**/WALL/**/,SAND,SAND,STONE,SAND,SAND,SAND },
		// ========================================================================================================================
		// { SAND,SAND,SAND,SAND,SAND,SAND/**/,SAND/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,SAND,EMPTY,EMPTY,EMPTY,EMPTY/**/,EMPTY/**/,EMPTY,EMPTY,EMPTY,EMPTY,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ SAND,SAND,EMPTY,EMPTY,EMPTY,EMPTY/**/,EMPTY/**/,EMPTY,EMPTY,EMPTY,EMPTY,SAND,SAND,/**/WALL/**/,SAND,SAND,STONE,STONE,SAND,SAND },
		{ SAND,SAND,ENEMY,EMPTY,EMPTY,EMPTY/**/,EMPTY/**/,EMPTY,EMPTY,EMPTY,EMPTY,SAND,SAND,/**/WALL/**/,SAND,SAND,WALL,WALL,EMPTY,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,SAND/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,WALL,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,SAND/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,SAND,SAND,SAND,SAND,SAND,SAND },
		{ STONE,SAND,SAND,SAND,SAND,SAND/**/,SAND/**/,SAND,SAND,SAND,SAND,SAND,SAND,/**/WALL/**/,STONE,SAND,SAND,SAND,SAND,SAND },
		{ SAND,STONE,SAND,SAND,SAND,SAND/**/,SAND/**/,SAND,SAND,SAND,SAND,SAND,STONE,/**/WALL/**/,STONE,SAND,SAND,SAND,SAND,SAND },
		{ SAND,SAND,SAND,SAND,SAND,SAND/**/,SAND/**/,SAND,STONE,SAND,SAND,STONE,STONE,/**/WALL/**/,EMPTY,STONE,SAND,SAND,SAND,STONE } };

	for (int y = 0; y < 20; y++)
		for (int x = 0; x < 76; x++)
		{
			map[x + 2][y + 3][0] = temp[x][y];
		}

	// Adaug aici jucatorul, player, la marginea cu nisipul
	map[2][3][0] = PLAYER;
	/*	map[3][3][0] = SAND;
		map[3][4][0] = SAND;
		map[2][4][0] = SAND;

		map[16][9][0] = ENEMY;
		map[63][16][0] = ENEMY;

		map[15][9][0] = STONE;
		map[14][9][0] = DIAMOND;
		map[15][8][0] = DIAMOND;
		map[14][10][0] = STONE;
		map[15][10][0] = STONE;*/
}

void Level::drawMap(void)
{
	for (int y = 0; y < MAX_Y; y++)
		for (int x = 0; x < MAX_X; x++)
		{
			point.X = x;
			point.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);

			switch (map[x][y][0])
			{
			case ROCK:
			{
				setColor(black, 3); //3
			} break;
			case SAND:
			{
				setColor(black, 8);
			} break;
			case WALL:
			{
				setColor(8, black);
			} break;
			case EMPTY:
			{
				setColor(0, black);
			} break;
			case STONE:
			{
				setColor(black, 3); //15
			} break;
			case PLAYER:
			{
				setColor(black, 14);
			} break;
			case DIAMOND:
			{
				setColor(black, 11);
			} break;
			}// comentariile astea ar fi fost sa-mi deseneze numere pe ecran dar aparent nu merge , 
			//if (((x > 1 && y > 2) && (x < MAX_X - 2 && y < MAX_Y - 2)))
				std::cout << (char)map[x][y][0];			
			//else
			//	std::cout << map[x][y][0]<<" ";
		}


	// TODO: de scos liniile astea 2 de mai jos, sunt pt debug mode
	std::cout << "ding ming"<<std::endl;
	std::cout << "ding ming" << std::endl;
	// functia de mai jos reseteaza pozitia imaginii de sus de tot am impresia, 
	//ideea e ca daca tot scriu se face scroll la imagine in sus cum e si normal 
	//reseteaza pozitia cursorului, daca fac scroll in jos din butonul din dreapta sus o sa vad
	point.X = 0;
	point.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);

}

void Level::setColor(int colorBack, int colorFore)
{
	int back = 0;
	if (colorBack & 1) back |= BACKGROUND_BLUE;
	if (colorBack & 2) back |= BACKGROUND_GREEN;
	if (colorBack & 4) back |= BACKGROUND_RED;
	if (colorBack & 8) back |= BACKGROUND_INTENSITY;

	int fore = 0;
	if (colorFore & 1) fore |= FOREGROUND_BLUE;
	if (colorFore & 2) fore |= FOREGROUND_GREEN;
	if (colorFore & 4) fore |= FOREGROUND_RED;
	if (colorFore & 8) fore |= FOREGROUND_INTENSITY;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), back | fore);
}