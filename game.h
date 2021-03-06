#ifndef GAME_H
#define GAME_H

#include "stdafx.h"
#include "level.h"
#include "player.h"
#include "stone.h"
#include "enemy.h"
#include "detonate.h"
#include "diamond.h"

class Game
{
public:
	Game(void);
	~Game();

	void init(Player* _p_ptr);

	void move(int direction);

	void update(void);
	void debug(void);
	void updateGravity(void);
	void updateExplosion(void);
	void updatePlayerState(void);
	void stoneGravity(void);
	void diamondGravity(void);

	void ai(void);
	
	void explosion(int _x, int _y);

	void loadObjects(Level *level_ptr, Player * player_ptr);

	void centerText(const char *message, int ypos);
	void centerText(int _l, const char *text1, int _d, const char *text2, int _t, const char *text3, int _p, const char *text4, int ypos);
	void gotoxy(int _x, int _y);

	void cursorHide();


	Player* player_ptr;

	Level level;

	//     // Iterator (Run through): 
	//     vector<int>::iterator i;
	int color;

	void restart(void);

private:
	Stone* stone_ptr;
	std::vector<Stone*> stoneVec;

	Diamond* dia_ptr;
	std::vector<Diamond*> diaVec;

	Enemy* enemy_ptr;
	std::vector<Enemy*> enemyVec;

	//int MAX_STONE;
	Detonate* expl_ptr;
	std::vector<Detonate*> explVec;

	int curr_diamond;
};

#endif
