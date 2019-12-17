#include "stdafx.h"
#include "stone.h"


Stone::Stone(void)
{
	X = 0;
	Y = 0;

	fall[SPEED] = SPEED_STONE;
	fall[DELAY] = SPEED_STONE;

	destroyed = false;

	debug = 12;
}

Stone::Stone(int _speed)
{
	X = 5;
	Y = 4;

	fall[SPEED] = _speed;
	fall[DELAY] = SPEED_STONE;

	destroyed = false;
}

void Stone::move(Level* _l_ptr, int _v)
{
	if (_v == RIGHT)//TODO: sa redenumesc _v in directie si _l_ptr in level_ptr sau mai bine in ptr_level
	{
		// Only if right is empty
		if (_l_ptr->map[X + 1][Y][0] == EMPTY)
		{
			// index umkopieren= index copy
			int i = _l_ptr->map[X][Y][1];
			_l_ptr->map[X][Y][1] = NULL;

			_l_ptr->map[X][Y][0] = EMPTY;
			_l_ptr->draw(X, Y, EMPTY);
			X++;
			_l_ptr->map[X][Y][0] = STONE;
			_l_ptr->map[X][Y][1] = i;
			draw();
		}
	}
	else if (_v == LEFT)
	{
		// Only if left is empty
		if (_l_ptr->map[X - 1][Y][0] == EMPTY)
		{
			// index copy
			int i = _l_ptr->map[X][Y][1];
			_l_ptr->map[X][Y][1] = NULL;

			_l_ptr->map[X][Y][0] = EMPTY;
			_l_ptr->draw(X, Y, EMPTY);
			// If there is a stone on the right, stone must be redrawn
			if (_l_ptr->map[X + 1][Y][0] == STONE)
				_l_ptr->draw(X + 1, Y, STONE);
			else if (_l_ptr->map[X + 1][Y][0] == PLAYER)
				_l_ptr->draw(X + 1, Y, PLAYER);
			else if (_l_ptr->map[X + 1][Y][0] == DIAMOND)
				_l_ptr->draw(X + 1, Y, DIAMOND);
			X--;
			_l_ptr->map[X][Y][0] = STONE;
			_l_ptr->map[X][Y][1] = i;
			draw();
		}
	}
	else if (_v == DOWN)
	{
		if (_l_ptr->map[X][Y + 1][0] == EMPTY)
		{
			// index copy
			int i = _l_ptr->map[X][Y][1];
			_l_ptr->map[X][Y][1] = NULL;

			_l_ptr->map[X][Y][0] = EMPTY;
			_l_ptr->draw(X, Y, EMPTY);
			//If there is a stone on the right, stone must be redrawn
			if (_l_ptr->map[X + 1][Y][0] == STONE)
				_l_ptr->draw(X + 1, Y, STONE);
			else if (_l_ptr->map[X + 1][Y][0] == PLAYER)
				_l_ptr->draw(X + 1, Y, PLAYER);
			else if (_l_ptr->map[X + 1][Y][0] == DIAMOND)
				_l_ptr->draw(X + 1, Y, DIAMOND);

			if (_l_ptr->map[X][Y + 2][0] != EMPTY)
				//PlaySound(TEXT("stone.wav"), NULL, SND_ASYNC);

			Y++;
			_l_ptr->map[X][Y][0] = STONE;
			_l_ptr->map[X][Y][1] = i;
			draw();
		}
	}
	else if (_v == UP)
	{
		if (_l_ptr->map[X][Y - 1][0] == EMPTY)
		{
			// index copy
			int i = _l_ptr->map[X][Y][1];
			_l_ptr->map[X][Y][1] = NULL;

			_l_ptr->map[X][Y][0] = EMPTY;
			_l_ptr->draw(X, Y, EMPTY);
			Y--;
			_l_ptr->map[X][Y][0] = STONE;
			_l_ptr->map[X][Y][1] = i;
			draw();
		}
	}
}

void Stone::gravity(Level* _l_ptr)
{
	if (getDelay() == 0)
	{
		if (_l_ptr->map[X][Y+1][0] == EMPTY)
		{
			move(_l_ptr, DOWN);
		}
		else if (_l_ptr->map[X-1][Y][0] == EMPTY && _l_ptr->map[X-1][Y+1][0] == EMPTY
			&& (_l_ptr->map[X][Y+1][0] == STONE || _l_ptr->map[X][Y+1][0] == WALL || _l_ptr->map[X][Y+1][0] == DIAMOND))
		{
			move(_l_ptr, LEFT);
		}
		else if (_l_ptr->map[X+1][Y][0] == EMPTY && _l_ptr->map[X+1][Y+1][0] == EMPTY
			&& (_l_ptr->map[X][Y+1][0] == STONE || _l_ptr->map[X][Y+1][0] == WALL || _l_ptr->map[X][Y+1][0] == DIAMOND))
		{
			move(_l_ptr, RIGHT);
		}
	}
	slowdown();
}

void Stone::slowdown(void)
{
	if (fall[DELAY] > 0)
		fall[DELAY]--;
	else
		fall[DELAY] = fall[SPEED];
}

void Stone::draw(void)
{
	COORD point;
	point.X = X;
	point.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
	setColor(black, 3); //11
	std::cout << (char)STONE;
}

// Debug
//void Stone::draw(Level* _l_ptr)
//{
//	COORD point;
//	point.X = X;
//	point.Y = Y;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
//	setColor(black, 3); //15
//	//std::cout << (char)STONE;
//	std::cout << _l_ptr->map[X][Y][1];
//}


