#include "stdafx.h"
#include "diamond.h"



void Diamond::move(Level* _l_ptr, int _v)
{
	moveBase(_l_ptr, _v, DIAMOND);	
}

void Diamond::draw(void)
{	
	drawbase( 11, DIAMOND);
}




