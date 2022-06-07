#include "stdafx.h"
#include "player.h"


Player::Player(void)
{
	X = 2;
	Y = 3;

	walk[SPEED] = SPEED_PLAYER;
	walk[DELAY] = 0;

	destroyed = false;
}

//Player::Player(Level* _l_ptr, Stone* _s_ptr, int _speed)
Player::Player(int _speed)
{
	X = 2;
	Y = 3;

	walk[SPEED] = _speed;
	walk[DELAY] = 0;
	
	/*	level_ptr = _l_ptr;
		level_ptr->map[X][Y][0] = PLAYER;

		stone_ptr = _s_ptr;*/

	destroyed = false;
}

void Player::init(Level* _l_ptr)
{
	level_ptr = _l_ptr;
}

void Player::move(int _v)
{
	if (_v == RIGHT) // dreapta
	{
		//PlaySound(TEXT("walk2.wav"), NULL, SND_ASYNC);
		X++;
		draw();
	}
	else if (_v == LEFT)// stanga
	{
		//PlaySound(TEXT("walk2.wav"), NULL, SND_ASYNC);
		X--;
		draw();
	}
	else if (_v == DOWN) //jos
	{
		//PlaySound(TEXT("walk2.wav"), NULL, SND_ASYNC);
		Y++;
		draw();
	}
	else if (_v == UP) //sus
	{
		//PlaySound(TEXT("walk2.wav"), NULL, SND_ASYNC);
		Y--;
		draw();
	}
}




/*
void Player::move(int _v)
{
	if (_v == RECHTS)
	{
		// Only if there is sand or empty on the right
		if (level_ptr->map[X+1][Y][0] == SAND || level_ptr->map[X+1][Y][0] == EMPTY)
		{
			level_ptr->map[X][Y][0] = EMPTY;
			level_ptr->draw(X, Y, EMPTY);
			X++;
			level_ptr->map[X][Y][0] = PLAYER;
			draw();
		}
		// Player pushes stone
		else if (level_ptr->map[X+1][Y][0] == STONE && level_ptr->map[X+2][Y][0] == EMPTY)
		{
			stone_ptr->move(RECHTS);

	}
	else if (_v == LINKS)
	{
		// Only if left is sand or empty
		if (level_ptr->map[X-1][Y][0] == SAND || level_ptr->map[X-1][Y][0] == EMPTY)
		{
			level_ptr->map[X][Y][0] = EMPTY;
			level_ptr->draw(X, Y, EMPTY);
			// If there is a stone on the right, stone must be redrawn
			if (level_ptr->map[X+1][Y][0] == STONE)
				level_ptr->draw(X+1, Y, STONE);
			X--;
			level_ptr->map[X][Y][0] = PLAYER;
			draw();
		}
		else if (level_ptr->map[X-1][Y][0] == STONE && level_ptr->map[X-2][Y][0] == EMPTY)
		{
			stone_ptr->move(LINKS);
		}
	}
	else if (_v == RUNTER)
	{
		if (level_ptr->map[X][Y+1][0] == SAND || level_ptr->map[X][Y+1][0] == EMPTY)
		{
			level_ptr->map[X][Y][0] = EMPTY;
			level_ptr->draw(X, Y, EMPTY);
			// Wenn rechts ein stein liegt, stein muss neu gezeichnet werden
			if (level_ptr->map[X+1][Y][0] == STONE)
				level_ptr->draw(X+1, Y, STONE);

			Y++;
			level_ptr->map[X][Y][0] = PLAYER;
			draw();
		}
	}
	else if (_v == RAUF)
	{
		if (level_ptr->map[X][Y-1][0] == SAND || level_ptr->map[X][Y-1][0] == EMPTY)
		{
			level_ptr->map[X][Y][0] = EMPTY;
			level_ptr->draw(X, Y, EMPTY);
			// Wenn rechts ein stein liegt, stein muss neu gezeichnet werden
			if (level_ptr->map[X+1][Y][0] == STONE)
				level_ptr->draw(X+1, Y, STONE);
			Y--;
			level_ptr->map[X][Y][0] = PLAYER;
			draw();
		}
	}
}*/

void Player::slowdown(void)
{
	if (walk[DELAY] < walk[SPEED])
		walk[DELAY]++;
	else
		walk[DELAY] = 0;
}

void Player::draw(void)
{   //COORD
	//Defines the coordinates of a character cell in a console screen buffer. 
	//The origin of the coordinate system (0,0) is at the top, left cell of the buffer.
	COORD point;
	point.X = X;
	point.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);// setez cursorul la pozitia cu playerul
	setColor(black, 14);// setam culorile
	std::cout << (char)PLAYER;// si scriu caracterul pt player
}

