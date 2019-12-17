#include "stdafx.h"
#include "enemy.h"


Enemy::Enemy(void)
{
	X = 0;
	Y = 0;

	route[SPEED] = SPEED_ENEMY;
	route[DELAY] = SPEED_ENEMY;

	destroyed = false;

	color[0] = 12;
	color[1] = 14;

	debug = 205; //179;

	way = RIGHT;
}

Enemy::Enemy(int _speed)
{
	X = 5;
	Y = 4;

	route[SPEED] = _speed;
	route[DELAY] = SPEED_ENEMY;

	destroyed = false;

	color[0] = 12;
	color[1] = 14;

	debug = 30;

	way = RIGHT;
}

void Enemy::move(Level* _l_ptr, int _v)
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
			_l_ptr->map[X][Y][0] = ENEMY;
			_l_ptr->map[X][Y][1] = i;
			//draw();
		}
	}
	else if (_v == LEFT)
	{
		// Only if right is empty
		if (_l_ptr->map[X - 1][Y][0] == EMPTY)
		{
			// index 
			int i = _l_ptr->map[X][Y][1];
			_l_ptr->map[X][Y][1] = NULL;

			_l_ptr->map[X][Y][0] = EMPTY;
			_l_ptr->draw(X, Y, EMPTY);
			// If there is a stone on the right, stone must be redrawn
			if (_l_ptr->map[X + 1][Y][0] == STONE)
				_l_ptr->draw(X + 1, Y, STONE);
			else if (_l_ptr->map[X + 1][Y][0] == PLAYER)
				_l_ptr->draw(X + 1, Y, PLAYER);
			X--;
			_l_ptr->map[X][Y][0] = ENEMY;
			_l_ptr->map[X][Y][1] = i;
			//draw();
		}
	}
	else if (_v == DOWN)
	{
		if (_l_ptr->map[X][Y + 1][0] == EMPTY)
		{
			// index 
			int i = _l_ptr->map[X][Y][1];
			_l_ptr->map[X][Y][1] = NULL;

			_l_ptr->map[X][Y][0] = EMPTY;
			_l_ptr->draw(X, Y, EMPTY);
			// If there is a stone on the right, stone must be redrawn
			if (_l_ptr->map[X + 1][Y][0] == STONE)
				_l_ptr->draw(X + 1, Y, STONE);
			else if (_l_ptr->map[X + 1][Y][0] == PLAYER)
				_l_ptr->draw(X + 1, Y, PLAYER);

			Y++;
			_l_ptr->map[X][Y][0] = ENEMY;
			_l_ptr->map[X][Y][1] = i;
			//draw();
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
			// If there is a stone on the right, stone must be redrawn
			if (_l_ptr->map[X + 1][Y][0] == STONE)
				_l_ptr->draw(X + 1, Y, STONE);
			else if (_l_ptr->map[X + 1][Y][0] == PLAYER)
				_l_ptr->draw(X + 1, Y, PLAYER);

			Y--;
			_l_ptr->map[X][Y][0] = ENEMY;
			_l_ptr->map[X][Y][1] = i;
			//draw();
		}
	}
}

void Enemy::slowdown(void)
{
	if (route[DELAY] < route[SPEED])
		route[DELAY]++;
	else
		route[DELAY] = 0;
}

void Enemy::draw(void)
{
	COORD point;
	point.X = X;
	point.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);

	setColor(color[0], color[1]); //15

//	if (route[DELAY] == 0 || route[DELAY] == 2)
//	{
	int c = color[0];
	color[0] = color[1];
	color[1] = c;
	//	}
	std::cout << (char)ENEMY;
	//std::cout << (char)debug;
	//std::cout << (char)debug;
}

/*
179
186*/

// Debug
void Enemy::draw(Level* _l_ptr)
{
	COORD point;
	point.X = X;
	point.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
	setColor(12, 14); //15
	std::cout << _l_ptr->map[X][Y][1];
}


