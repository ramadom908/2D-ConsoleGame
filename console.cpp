// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "player.h"
//#include "enemy.h"
#include "level.h"
#include "stone.h"
#include "game.h"





DWORD LoopStartTime;



// Set cursor position
void gotoxy(int x, int y)
{
	COORD point;
	point.X = x;
	point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

// Clear image, not used        // functie de clearscreen?  nu e folosita?
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD bufferSize, charsWritten;

	COORD topleft = { 0, 0 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	bufferSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), bufferSize, topleft, &charsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, bufferSize, topleft, &charsWritten);
	SetConsoleCursorPosition(hConsole, topleft);
}



// Color for writing
void setColor(int colorBack, int colorFore)
{
	int back = 0;
	if (colorBack & 1) back = back | BACKGROUND_BLUE; // toate astea de mai jos se pot scrie asa
	if (colorBack & 2) back |= BACKGROUND_GREEN;	  //  bara verticala  |  este bitwise or
	if (colorBack & 4) back |= BACKGROUND_RED;
	if (colorBack & 8) back |= BACKGROUND_INTENSITY;

	int fore = 0;
	if (colorFore & 1) fore |= FOREGROUND_BLUE;
	if (colorFore & 2) fore |= FOREGROUND_GREEN;
	if (colorFore & 4) fore |= FOREGROUND_RED;
	if (colorFore & 8) fore |= FOREGROUND_INTENSITY;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), back | fore);
}


// Print text
void centerText(const char *message, int ypos)
{
	int len = strlen(message);
	if (len > 0)
	{
		int xpos = (CONSOLE_WIDTH - len) / 2;
		gotoxy(xpos, ypos);
		printf(message);
	}
}

void cursorHide(HANDLE *h)
{
	CONSOLE_CURSOR_INFO info;

	info.bVisible = 0;
	info.dwSize = 1;

	SetConsoleCursorInfo(h, &info);
}

int main()
{//comment
	HANDLE hwnd;//TODO:TASK sa vad ce face handle
	hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorHide(&hwnd);

	bool exit = false;

	Player player(SPEED_PLAYER); // viteza setata in stdafx


	//level.drawMap();

/*	Enemy enemy[2];
	enemy[0].init(&level, 16, 9, SPEED_ENEMY);
	enemy[1].init(&level, 63, 16, SPEED_ENEMY);*/
	setColor(black, 7);
	centerText(" 1 Lives |  0 Diamonds | 109 Time | 00032 Points ", 1);

	Game game;
	game.init(&player);

	player.draw();

	do
	{


		if (_kbhit())// daca e apasata o tasta, orice tasta
		{
			int key = _getch(); // presupun ca aici se preia care tasta am apasat
			if (key == KEY_ESCAPE) exit = true;

			if (player.getDelay() == 0)
			{

				if (!key || key == 0xe0)
					key = _getch();

				switch (key)
				{
				case KEY_LEFT: game.move(LEFT); break;
				case KEY_RIGHT: game.move(RIGHT); break;
				case KEY_UP: game.move(UP); break;
				case KEY_DOWN: game.move(DOWN); break;
				case KEY_RETURN: game.restart(); break;
				}
			}
			player.slowdown();
		}
		else player.setDelay(0);  // waiting is set to 0 if player changes direction (direct control)

		// ToDo: Here call of Enemies
//		enemy[0].KI();
//		enemy[1].KI();

		// ToDo: Player Show
//		enemy[0].draw();
//		enemy[1].draw();

		//player.draw();

		game.update();

		//clrscr();

		// ====================================================== 
		LoopStartTime = GetTickCount();
		while ((GetTickCount() - LoopStartTime) < 40);

	} while (!exit);

}