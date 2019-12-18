//#include "stdafx.h"
#include "baseRock.h"


BaseRock::BaseRock(void)
{
	X = 0;
	Y = 0;

	fall[SPEED] = SPEED_STONE;
	fall[DELAY] = SPEED_STONE;

	destroyed = false;

	color = 254;
}

BaseRock::BaseRock(int _speed)
{
	X = 5;
	Y = 4;

	fall[SPEED] = _speed;
	fall[DELAY] = SPEED_STONE;

	destroyed = false;

	color = 32;
}

void BaseRock::move(Level* _l_ptr, int _v) {

	moveBase(_l_ptr, _v, STONE);
}

void BaseRock::moveBase(Level* _l_ptr, int _v, int ROCKNAME)
{
	if (_v == RIGHT)
	{
		// Only if right is empty
		if (_l_ptr->map[X + 1][Y][0] == EMPTY)
		{
			// index
			int i = _l_ptr->map[X][Y][1];
			_l_ptr->map[X][Y][1] = NULL;

			_l_ptr->map[X][Y][0] = EMPTY;
			_l_ptr->draw(X, Y, EMPTY);
			X++;
			_l_ptr->map[X][Y][0] = ROCKNAME;
			_l_ptr->map[X][Y][1] = i;
			draw();

		}
	}
	else if (_v == LEFT)
	{
		// Only if left is empty
		if (_l_ptr->map[X - 1][Y][0] == EMPTY)
		{
			// index 
			int i = _l_ptr->map[X][Y][1];
			_l_ptr->map[X][Y][1] = NULL;

			_l_ptr->map[X][Y][0] = EMPTY;
			_l_ptr->draw(X, Y, EMPTY);
			// If there is a stone on the right, stone must be redrawn
			/*if (_l_ptr->map[X + 1][Y][0] == STONE)
				_l_ptr->draw(X + 1, Y, STONE);
			else if (_l_ptr->map[X + 1][Y][0] == PLAYER)
				_l_ptr->draw(X + 1, Y, PLAYER);
			else if (_l_ptr->map[X + 1][Y][0] == ROCKNAME)
				_l_ptr->draw(X + 1, Y, ROCKNAME);*/

			X--;
			_l_ptr->map[X][Y][0] = ROCKNAME;
			_l_ptr->map[X][Y][1] = i;
			draw();
		}
	}
	else if (_v == DOWN)
	{
		if (_l_ptr->map[X][Y + 1][0] == EMPTY)
		{
			// index umkopieren
			int i = _l_ptr->map[X][Y][1];
			_l_ptr->map[X][Y][1] = NULL;

			_l_ptr->map[X][Y][0] = EMPTY;
			_l_ptr->draw(X, Y, EMPTY);
			// If there is a stone on the right, stone must be redrawn
			/*if (_l_ptr->map[X + 1][Y][0] == STONE)
				_l_ptr->draw(X + 1, Y, STONE);
			else if (_l_ptr->map[X + 1][Y][0] == PLAYER)
				_l_ptr->draw(X + 1, Y, PLAYER);
			else if (_l_ptr->map[X + 1][Y][0] == ROCKNAME)
				_l_ptr->draw(X + 1, Y, ROCKNAME);*/

			Y++;
			_l_ptr->map[X][Y][0] = ROCKNAME;
			_l_ptr->map[X][Y][1] = i;
			draw();
		}
	}
	else if (_v == UP)
	{
		if (_l_ptr->map[X][Y - 1][0] == EMPTY)
		{
			// index umkopieren
			int i = _l_ptr->map[X][Y][1];
			_l_ptr->map[X][Y][1] = NULL;

			_l_ptr->map[X][Y][0] = EMPTY;
			_l_ptr->draw(X, Y, EMPTY);
			Y--;
			_l_ptr->map[X][Y][0] = ROCKNAME;
			_l_ptr->map[X][Y][1] = i;
			draw();
		}
	}
}


void BaseRock::slowdown(void)
{
	if (fall[DELAY] > 0)
		fall[DELAY]--;
	else
		fall[DELAY] = fall[SPEED];
}

 void BaseRock::draw(void)
{
	 // drawbase(11, DIAMOND); // to be overloaded

	//COORD point;
	//point.X = X;
	//point.Y = Y;
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
	//setColor(black, 3); //11
	//std::cout << (char)DIAMOND;

}

// setColor(black, 11);
void BaseRock::drawbase(colorEnum color, int nrCuloare, int ROCKNAME)
{
	COORD point;
	point.X = X;
	point.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
	setColor(black, nrCuloare); //11
	std::cout << (char)ROCKNAME;
}

