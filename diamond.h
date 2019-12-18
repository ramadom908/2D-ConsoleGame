#ifndef DIAMOND_H
#define DIAMOND_H

#include "baseRock.h"
#include "level.h"

class Diamond :public BaseRock
{
public:
	
	void move(Level* _l_ptr, int _v);
	void draw(void);

	int color;
};

#endif
