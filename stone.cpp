#include "stdafx.h"
#include "stone.h"



void Stone::move(Level* _l_ptr, int _v)
{
	moveBase(_l_ptr, _v, STONE);
	/*if (_v == LEFT) {  // solutie ca sa ramana directia de miscare constanta apietrei dupa ce e impinsa de player
		stoneDir = 'l'; // ceva similar este si in game.cpp la liniile 513 si 487

	}
	else if (_v == RIGHT) {
		stoneDir = 'r';
	}*/
}

void Stone::draw(void)
{
	drawbase(3, STONE);
}

