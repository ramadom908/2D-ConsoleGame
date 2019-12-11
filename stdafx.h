// stdafx.h : Include file for standard system include files
// or frequently used project-specific include files
// which can only be changed at irregular intervals
//
#ifndef STDAFX_H
#define STDAFX_H

#pragma once

#include "targetver.h"

#define UP 10000
#define RIGHT 10001
#define DOWN 10002
#define LEFT 10003

#define ADD 10004

const int SPEED = 0;
const int DELAY = 1;

const int SPEED_PLAYER = 1;
const int SPEED_ENEMY = 3;
const int SPEED_STONE = 2;
const int SPEED_FIRE = 1;

const int MAX_X = 80;
const int MAX_Y = 25;

const int MAX_EMEMY = 8;

#define EMPTY 32
#define SAND 176 //219
#define ROCK 64 //206 //188 '@'  se pot defini si valori hexadecimale  gen:   0x263A  dar trebe afisata corespunzator
#define WALL 206 //197 //177 
#define STONE 111//207//15 //184 'o'
#define PLAYER 1
#define ENEMY 2 //186 //2    
#define DIAMOND 30 //4 'triungi'
#define FIRE 0

const int KEY_UP = 0x48;
const int KEY_DOWN = 0x50;
const int KEY_LEFT = 0x4b;
const int KEY_RIGHT = 0x4d;
const int KEY_ESCAPE = 0x1b;
const int KEY_RETURN = 0x0d;

const int CONSOLE_WIDTH = 80;
const int CONSOLE_HEIGHT = 40;

#include <cstdio>
#include <conio.h>
#include <tchar.h>
#include <windows.h>
#include <WinCon.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <dos.h> 
#include <Mmsystem.h> 

enum color
{
	black,
	darkblue,
	darkgreen,
	darkcyan,
	darkred,
	darkpurple,
	darkgray,
	darkwhite,
	gray,
	blue,
	green,
	cyan,
	red,
	purple,
	yellow,
	white
};


// TODO: Refer here to additional headers that the program requires.
#endif
