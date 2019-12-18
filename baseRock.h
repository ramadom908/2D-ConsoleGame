#ifndef BaseRock_H
#define BaseRock_H

#include "level.h"

class BaseRock
{
public:
	BaseRock(void);
	BaseRock(int _speed);

	virtual void move(Level* _l_ptr, int _v);
	void moveBase(Level* _l_ptr, int _v, int ROCKNAME);
	//void gravity(Level* _l_ptr);

	int getX() { return X; }
	int getY() { return Y; }

	void setX(int _x) { X = _x; }
	void setY(int _y) { Y = _y; }

	int getSpeed() { return fall[SPEED]; }
	int getDelay() { return fall[DELAY]; }

	void setDelay(int v) { fall[DELAY] = v; }

	void slowdown();

	int getState() { return destroyed; }
	void setState(bool _v) { destroyed = _v; }

	virtual void draw(void);
    void drawbase(colorEnum color, int nrCuloare, int rock);
	//void draw(Level* _l_ptr);


	int color;

private:
	int X;
	int Y;
	bool destroyed;

	int fall[2];

};

#endif