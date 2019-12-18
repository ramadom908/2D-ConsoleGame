#ifndef STONE_H
#define STONE_H

#include "baseRock.h"
#include "level.h"

class Stone: public BaseRock
{
public:

	void move(Level * _l_ptr, int _v);
	void draw(void);


	int debug;
	char stoneDir = 'd';


};

#endif