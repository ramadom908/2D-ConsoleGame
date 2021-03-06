
#include "stdafx.h"
#include "game.h"
//#include "detonate.h"
#include <iostream>




Game::Game(void)
{
	//MAX_STONE = 0;
	color = 0;
	curr_diamond = 0;
}

void Game::debug(void)
{
	level.load();
	level.drawMap();
	/*	//std::cout << level.map[0][y][1];
		for (int y=0; y<MAX_Y; y++)
			for (int x=0; x<MAX_X; x++)
			{
				if (level.map[x][y][1] >= 0)
				std::cout << level.map[x][y][1];
			}*/
			//explosion(76,21);

		/*	for (int i=0; i<stoneVec.size(); i++)
			{

				stoneVec[i]->draw();
				stoneVec[i]->debug++;
			}*/
	level.debug++;
}

void Game::explosion(int _x, int _y)
{
	expl_ptr = new Detonate;
	expl_ptr->init(_x, _y);
	explVec.push_back(expl_ptr);
}

void Game::loadObjects(Level *level_ptr, Player * player_ptr) {


	//int i_stone=0; // initializare obiecte// stone enemy diamant?
	//parcurg toata harta si unde gasesc obiecte le initializez memorie
	//TODO:TASK sa vad cum se face parcurgerea asta pe coordonate ;a harta asta
	//TODO:TASK sa vad care-i treaba cu alocarea cu new
	//TODO:TASK sa vad care-i treaba cu vector class
	for (int y = 0; y < MAX_Y; y++)
		for (int x = 0; x < MAX_X; x++)
		{
			if (level_ptr->map[x][y][0] == STONE)
			{
				stone_ptr = new Stone; // e ca si cum fac o noua variabila  stone doar ca e pe heap
				stone_ptr->setX(x);  // x,y sunt coordonatele unde gasesc o piatra in map, astfel ca le setez si in variabila nou creata
				stone_ptr->setY(y);  //
				stoneVec.push_back(stone_ptr);//TODO: ??? pun piatra intr-un vector de pietre, ca sa le pot manipula mai incolo?
				level_ptr->map[x][y][1] = stoneVec.size() - 1;// pozitia asta este initializata peste tot cu -1
			}											 // aici setez pozitia asta cu dimensiunea vectorului de
														 //pietre -1 inca nu stiu de ce..., probabil pt parcurgere de la 0 in vectorul de pietre si sa le tin cont unde sunt
				//TODO: TASK sa vad de ce stetez ma sus cu dimensiune -1 si nu cu dimensiune
				// cel mai probabil ca sa incep de la 0 cu parcurgerea pe undeva
			else if (level_ptr->map[x][y][0] == ENEMY)
			{// la fel ca la stone
				enemy_ptr = new Enemy;
				enemy_ptr->setX(x);
				enemy_ptr->setY(y);
				enemyVec.push_back(enemy_ptr);
				level_ptr->map[x][y][1] = enemyVec.size() - 1;
			}
			else if (level_ptr->map[x][y][0] == DIAMOND)
			{//la fel ca la stone
				dia_ptr = new Diamond;
				dia_ptr->setX(x);
				dia_ptr->setY(y);
				diaVec.push_back(dia_ptr);
				level_ptr->map[x][y][1] = diaVec.size() - 1;
			}
			else if (level_ptr->map[x][y][0] == PLAYER)
			{//initializare player cu coordonatele din in.txt
				player_ptr->setX(x);
				player_ptr->setY(y);
			}
		}

	//MAX_STONE = i;
	//std::cout << i;
	


}




// initializare obiecte, stone,enemy, diamond
void Game::init(Player* _player_ptr)
{
	player_ptr = _player_ptr;

	color = 0;
	curr_diamond = 0;

	level.load();
	level.drawMap();

	loadObjects(&level, _player_ptr);

	// initializare level_ptr de la player
	_player_ptr->init(&level);

	setColor(black, 7);
	centerText(1, " Lives", diaVec.size() - curr_diamond, " Diamonds", 49, " Time", 109, " Points", 1);
}

// Control Enemy
void Game::ai(void)
{

#define X  enemyVec[i]->getX()
#define Y  enemyVec[i]->getY()

	for (int i = 0; i < enemyVec.size(); i++)
	{
		// Enemy is not broken yet?
		if (!enemyVec[i]->getState())
		{   // if left, over, right or under player, enemy explodes
			if (level.map[X - 1][Y][0] == PLAYER ||
				level.map[X][Y - 1][0] == PLAYER ||
				level.map[X + 1][Y][0] == PLAYER ||
				level.map[X][Y + 1][0] == PLAYER)
			{
				//PlaySound(TEXT("explosion-02.wav"), NULL, SND_ASYNC);
				enemyVec[i]->setState(true);
				explosion(X, Y);
			}
			// if Enemy burns, enemy explodes enemy, enemy explodes u. dies
			else if (level.map[X][Y][0] == FIRE)
			{
				//PlaySound(TEXT("explosion-02.wav"), NULL, SND_ASYNC);
				enemyVec[i]->setState(true);
				explosion(X, Y);
			}
			// if there is a stone over Enemy, Enemy explodes u. dies
			else if (level.map[X][Y - 1][0] == STONE)
			{
				//PlaySound(TEXT("explosion-02.wav"), NULL, SND_ASYNC);
				enemyVec[i]->setState(true);
				explosion(X, Y);
			}
			else
			{
				if (enemyVec[i]->getDelay() == 0)
				{
					if (enemyVec[i]->getWay() == RIGHT)
					{
						if (level.map[X][Y - 1][0] != EMPTY && level.map[X + 1][Y][0] == EMPTY)
						{
							enemyVec[i]->setWay(RIGHT);
							enemyVec[i]->move(&level, RIGHT);
						}
						else if (level.map[X - 1][Y - 1][0] != EMPTY && level.map[X][Y - 1][0] == EMPTY)
						{
							enemyVec[i]->setWay(UP);
							enemyVec[i]->move(&level, UP);
						}
						else if (level.map[X][Y - 1][0] != EMPTY && level.map[X + 1][Y][0] != EMPTY
							&& level.map[X][Y + 1][0] == EMPTY)
						{
							enemyVec[i]->setWay(DOWN);
							enemyVec[i]->move(&level, DOWN);
						}
						else if (level.map[X][Y - 1][0] != EMPTY && level.map[X + 1][Y][0] != EMPTY
							&& level.map[X][Y + 1][0] != EMPTY && level.map[X - 1][Y][0] == EMPTY)
						{
							enemyVec[i]->setWay(LEFT);
							enemyVec[i]->move(&level, LEFT);
						}
						else enemyVec[i]->setWay(DOWN);
					}
					else if (enemyVec[i]->getWay() == DOWN)
					{
						if (level.map[X + 1][Y][0] != EMPTY && level.map[X][Y + 1][0] == EMPTY)
						{
							enemyVec[i]->setWay(DOWN);
							enemyVec[i]->move(&level, DOWN);
						}
						else if (level.map[X + 1][Y - 1][0] != EMPTY && level.map[X + 1][Y][0] == EMPTY)
						{
							enemyVec[i]->setWay(RIGHT);
							enemyVec[i]->move(&level, RIGHT);
						}
						else if (level.map[X + 1][Y][0] != EMPTY && level.map[X][Y + 1][0] != EMPTY
							&& level.map[X - 1][Y][0] == EMPTY)
						{
							enemyVec[i]->setWay(LEFT);
							enemyVec[i]->move(&level, LEFT);
						}
						else if (level.map[X + 1][Y][0] != EMPTY && level.map[X][Y + 1][0] != EMPTY
							&& level.map[X - 1][Y][0] != EMPTY && level.map[X][Y - 1][0] == EMPTY)
						{
							enemyVec[i]->setWay(UP);
							enemyVec[i]->move(&level, UP);
						}
						else enemyVec[i]->setWay(LEFT);
					}
					else if (enemyVec[i]->getWay() == LEFT)
					{
						if (level.map[X][Y + 1][0] != EMPTY && level.map[X - 1][Y][0] == EMPTY)
						{
							enemyVec[i]->setWay(LEFT);
							enemyVec[i]->move(&level, LEFT);
						}
						else if (level.map[X + 1][Y + 1][0] != EMPTY && level.map[X][Y + 1][0] == EMPTY)
						{
							enemyVec[i]->setWay(DOWN);
							enemyVec[i]->move(&level, DOWN);
						}
						else if (level.map[X][Y + 1][0] != EMPTY && level.map[X - 1][Y][0] != EMPTY
							&& level.map[X][Y - 1][0] == EMPTY)
						{
							enemyVec[i]->setWay(UP);
							enemyVec[i]->move(&level, UP);
						}
						else if (level.map[X][Y + 1][0] != EMPTY && level.map[X - 1][Y][0] != EMPTY
							&& level.map[X][Y - 1][0] != EMPTY && level.map[X + 1][Y][0] == EMPTY)
						{
							enemyVec[i]->setWay(RIGHT);
							enemyVec[i]->move(&level, RIGHT);
						}
						else enemyVec[i]->setWay(UP);
					}
					else if (enemyVec[i]->getWay() == UP)
					{
						if (level.map[X - 1][Y][0] != EMPTY && level.map[X][Y - 1][0] == EMPTY)
						{
							enemyVec[i]->setWay(UP);
							enemyVec[i]->move(&level, UP);
						}
						else if (level.map[X - 1][Y + 1][0] != EMPTY && level.map[X - 1][Y][0] == EMPTY)
						{
							enemyVec[i]->setWay(LEFT);
							enemyVec[i]->move(&level, LEFT);
						}
						else if (level.map[X - 1][Y][0] != EMPTY && level.map[X][Y - 1][0] != EMPTY
							&& level.map[X + 1][Y][0] == EMPTY)
						{
							enemyVec[i]->setWay(RIGHT);
							enemyVec[i]->move(&level, RIGHT);
						}
						else if (level.map[X - 1][Y][0] != EMPTY && level.map[X][Y - 1][0] != EMPTY
							&& level.map[X + 1][Y][0] != EMPTY && level.map[X][Y + 1][0] == EMPTY)
						{
							enemyVec[i]->setWay(DOWN);
							enemyVec[i]->move(&level, DOWN);
						}
						else enemyVec[i]->setWay(RIGHT);
					}
				}
				enemyVec[i]->slowdown();
				enemyVec[i]->draw();
			}
		}
	}
#undef X
#undef Y
}





// Stone Control cred ca ar trebuii rescrisa ca e prea stupida functia... merge prin tot vectorul de stone nenecesar
void Game::stoneGravity(void)
{
	// am pus define-urile astea aici ca sa fie mai usor de citit coordonatele
#define X  stoneVec[i]->getX()
#define Y  stoneVec[i]->getY()

// Stone  procesiing for gravity
	for (int i = 0; i < stoneVec.size(); i++)
	{		
		// is not stone broken yet?
		if (!stoneVec[i]->getState())
		{
			if (level.map[X][Y][0] == FIRE)
			{
				stoneVec[i]->setState(true);
			}
			else
			{	// stone falls
				if (stoneVec[i]->getDelay() == 0)
				{
					if (level.map[X][Y + 1][0] == EMPTY)
					{
						stoneVec[i]->move(&level, DOWN);
						stoneVec[i]->stoneDir = 'd';// aici resetez directia asta de fiecare data cand o piatra merge in jos

						if (level.map[X][Y + 1][0] == PLAYER)
						{
							// Stone collides with player
							//PlaySound(TEXT("explosion-02.wav"), NULL, SND_ASYNC);
							explosion(player_ptr->getX(), player_ptr->getY());
						}
						else if (level.map[X][Y + 1][0] == ENEMY)
						{
							//std::cout << "Stone collides with Enemy!";
							//PlaySound(TEXT("explosion-02.wav"), NULL, SND_ASYNC);
							explosion(enemyVec[level.map[X][Y + 1][1]]->getX(), enemyVec[level.map[X][Y + 1][1]]->getY());
						}
					}
					else if (level.map[X - 1][Y][0] == EMPTY &&
						(level.map[X - 1][Y + 1][0] == EMPTY ||
							level.map[X - 1][Y + 1][0] == STONE) && stoneVec[i]->stoneDir != 'r'     /*&& (level.map[X + 1][stoneVec[i]->getY()][0] != SAND && level.map[X + 1][stoneVec[i]->getY()][0] != WALL)*/
						/*&& (level.map[X][stoneVec[i]->getY() + 1][0] == STONE ||
						level.map[X][stoneVec[i]->getY() + 1][0] == WALL ||
						level.map[X][stoneVec[i]->getY() + 1][0] == DIAMOND)*/)
					{
						stoneVec[i]->move(&level, LEFT);
						stoneVec[i]->stoneDir = 'l'; // asta e pus aici temporar ca sa tin sub control directia de alunecat a pietrei 
					}
					else if (level.map[X + 1][Y][0] == EMPTY &&
						(level.map[X + 1][Y + 1][0] == EMPTY ||
							level.map[X + 1][Y + 1][0] == STONE) && stoneVec[i]->stoneDir != 'l'
						/*&& (level.map[stoneVec[i]->getX()][stoneVec[i]->getY() + 1][0] == STONE ||
						level.map[stoneVec[i]->getX()][stoneVec[i]->getY() + 1][0] == WALL ||
						level.map[stoneVec[i]->getX()][stoneVec[i]->getY() + 1][0] == DIAMOND)*/)
					{
						stoneVec[i]->move(&level, RIGHT);
						stoneVec[i]->stoneDir = 'r';
					}
				}
				stoneVec[i]->slowdown();
			}
		}


	}
#undef X
#undef Y
}


void Game::diamondGravity(void){
// am pus define-urile astea aici ca sa fie mai usor de citit coordonatele
#define X  diaVec[i]->getX()
#define Y  diaVec[i]->getY()

	for (int i = 0; i < diaVec.size(); i++){
		///////////////////////////////////////////////
		// Diamond
		// Diamond is not broken yet?
		// if i< diaVect.size... procesam si diamentele in acelasi for

		
		if (!diaVec[i]->getState())
		{
			if (level.map[X][Y][0] == FIRE)
			{
				diaVec[i]->setState(true);
			}
			else if (level.map[X][Y][0] == PLAYER)
			{
				int abc = level.map[X][Y][1]; // asta e pus temporar ca sa-l compar cu i din diaVec[i]
				diaVec[i]->setState(true);
				curr_diamond++;
				setColor(black, 7);
				centerText(1, " Lives", diaVec.size() - curr_diamond, " Diamonds", 49, " Time", 109, " Points", 1);
			}
			else
			{	// Diamond falls
				if (diaVec[i]->getDelay() == 0)
				{
					if (level.map[X][Y + 1][0] == EMPTY)
					{
						diaVec[i]->move(&level, DOWN);
						//X = diaVec[i]->getX();//update  X after move
						//Y = diaVec[i]->getY();//update  Y after move

						if (level.map[X][Y + 1][0] == PLAYER )
						{
							//PlaySound(TEXT("explosion-02.wav"), NULL, SND_ASYNC);
							explosion(player_ptr->getX(), player_ptr->getY());// TODO: de verificat ce-i aici daca chiar declanseaza explozie
						}
						else if (level.map[X][Y + 1][0] == ENEMY)
						{
							//std::cout << "Stone collides with Enemy!";
							//PlaySound(TEXT("explosion-02.wav"), NULL, SND_ASYNC);
							explosion(enemyVec[level.map[X][Y + 1][1]]->getX(), enemyVec[level.map[X][Y + 1][1]]->getY());
						}
					}
					else if (level.map[X - 1][Y][0] == EMPTY && level.map[X - 1][Y + 1][0] == EMPTY
						/*&& (level.map[X][Y + 1][0] == STONE || level.map[X][Y + 1][0] == WALL || level.map[X][Y + 1][0] == DIAMOND)*/)
					{
						diaVec[i]->move(&level, LEFT);					
					}
					else if (level.map[X + 1][Y][0] == EMPTY && level.map[X + 1][Y + 1][0] == EMPTY
						/*&& (level.map[X][Y + 1][0] == STONE || level.map[X][Y + 1][0] == WALL || level.map[X][Y + 1][0] == DIAMOND)*/)
					{
						diaVec[i]->move(&level, RIGHT);
					}
				}
				diaVec[i]->slowdown();
			}
		}
		
	}
#undef X
#undef Y
}

void Game::updateGravity(void) {
	stoneGravity();
	diamondGravity();
}

void Game::updateExplosion(void) {
	
	// if an explosion is ignited
	if (explVec.size() > 0)
	{
		for (int i = 0; i < explVec.size(); i++)
		{
			explVec[i]->firing(&level);
			// explosion from Vector delete after end, scot explozia din vector dupa ce termin animatia
			if (explVec[i]->getIndex() > 4)
				explVec.erase(explVec.begin() + i);
		}
	}
}

void Game::updatePlayerState(void) {

	//when player burns/explodes, player dies
	if (level.map[player_ptr->getX()][player_ptr->getY()][0] == FIRE)
	{
		player_ptr->setState(true);
		setColor(black, 7);
		centerText("                   GAME OVER                    ", 1);
	}
	// player wins
	else if (diaVec.size() - curr_diamond == 0)
	{
		player_ptr->setState(true);
		setColor(black, 7);
		centerText("                    YOU WIN!                    ", 1);
	}
}





void Game::update(void)
{
	
	updateExplosion();
	updatePlayerState();
	updateGravity();
	ai();

}

// Control player
void Game::move(int direction)
{

#define X  player_ptr->getX()
#define Y  player_ptr->getY()
	// is player dead?
	if (!player_ptr->getState())
	{
		if (direction == RIGHT)
		{
			// Only if right is Sand, Diamond or Empty
			if (level.map[X + 1][Y][0] == SAND || level.map[X + 1][Y][0] == EMPTY || level.map[X + 1][Y][0] == DIAMOND)
			{
				level.map[X][Y][0] = EMPTY;// goleste map-ul 
				level.draw(X, Y, EMPTY);	 // deseneaza ce-i in map adica gol

				player_ptr->move(RIGHT);// mut player pe noul loc si desenez pe ecran
				level.map[X][Y][0] = PLAYER;// bag player in map
			}
			// Player pushes stone
			else if (level.map[X + 1][Y][0] == STONE && level.map[X + 2][Y][0] == EMPTY)
			{
				// If push worked, new position should also be inserted in the map index
				int cont = level.map[X + 1][Y][1];
				//stoneVec[level.map[player_ptr->getX() + 1][player_ptr->getY()][1]]->move(&level, RIGHT);
				stoneVec[cont]->move(&level, RIGHT);
				stoneVec[cont]->stoneDir = 'r';
				//stoneVec[level.map[player_ptr->getX() + 1][player_ptr->getY()][1]]->stoneDir = 'r';
				
			}

		}
		else if (direction == LEFT)
		{
			// Only if left is sand or empty or dimond
			if (level.map[X - 1][Y][0] == SAND || level.map[X - 1][Y][0] == EMPTY || level.map[X - 1][Y][0] == DIAMOND)
			{
				level.map[X][Y][0] = EMPTY;
				level.draw(X, Y, EMPTY);

				
				player_ptr->move(LEFT);
				level.map[X][Y][0] = PLAYER;
				//draw();
			}
			// Player pushes stone left
			else if (level.map[X - 1][Y][0] == STONE && level.map[X - 2][Y][0] == EMPTY)
			{
				// If push worked, new position should also be inserted in the map index
				int cont = level.map[X - 1][Y][1];
				//stoneVec[level.map[player_ptr->getX() - 1][player_ptr->getY()][1]]->move(&level, LEFT);
				stoneVec[cont]->move(&level, LEFT);
				stoneVec[cont]->stoneDir = 'l'; // solutie ca sa ramana directia de miscare constanta apietrei dupa ce e impinsa de player
				//stoneVec[level.map[player_ptr->getX() + 1][player_ptr->getY()][1]]->stoneDir = 'l';
			}
		}
		else if (direction == DOWN)
		{
			if (level.map[X][Y + 1][0] == SAND || level.map[X][Y + 1][0] == EMPTY || level.map[X][Y + 1][0] == DIAMOND)
			{
				level.map[X][Y][0] = EMPTY;
				level.draw(X, Y, EMPTY);

				
				player_ptr->move(DOWN);
				level.map[X][Y][0] = PLAYER;
				//draw();
			}
		}
		else if (direction == UP)
		{
			if (level.map[X][Y - 1][0] == SAND || level.map[X][Y - 1][0] == EMPTY || level.map[X][Y - 1][0] == DIAMOND)
			{
				level.map[X][Y][0] = EMPTY;
				level.draw(X, Y, EMPTY);

				
				player_ptr->move(UP);
				level.map[X][Y][0] = PLAYER;
				//draw(); 			
			}
		}
	}

#undef X
#undef Y
}


void Game::cursorHide()
{
	HANDLE hwnd;
	hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;

	info.bVisible = 0;
	info.dwSize = 1;

	SetConsoleCursorInfo(hwnd, &info);
}

void Game::centerText(const char *message, int ypos)
{
	int len = strlen(message);
	if (len > 0)
	{
		int xpos = (CONSOLE_WIDTH - len) / 2;
		gotoxy(xpos, ypos);
		printf(message);
	}
}

void Game::centerText(int _l, const char *text1, int _d, const char *text2, int _t, const char *text3, int _p, const char *text4, int ypos)
{
	gotoxy(15, ypos);
	std::cout << " " << _l << text1 << " |  ";

	if (_d < 10)
		gotoxy(27, ypos);
	else gotoxy(26, ypos);
	//printf("%i,%c",_l, text1);
	std::cout << _d << text2 << " |  ";

	gotoxy(39, ypos);
	std::cout << " " << _t << text3 << " |  ";

	gotoxy(49, ypos);
	std::cout << " " << _p << text4 << " ";

	cursorHide();
}

void Game::gotoxy(int _x, int _y)
{
	COORD point;
	point.X = _x;
	point.Y = _y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

Game::~Game()
{// aparent trebuie sa merg prin vectorii astia si sa sterg toti pointerii individual
	//https://stackoverflow.com/questions/30476159/deleting-an-array-of-pointers-vs-deleting-a-vector-of-pointers
	//TODO:TASk sa vad mai bine care-i treaba cu delete si cu vectorii astia, linkul de mai sus e util
	// eventual sa vad si cum verific daca memoria a fost eliberata corect
	for (int i = 0; i < stoneVec.size(); i++) {
		delete stoneVec[i];
	}
	delete[] expl_ptr;
	//delete[] stone_ptr;// 
	delete[] enemy_ptr;
	delete[] expl_ptr;
}


void Game::restart(void)
{
	//PlaySound(TEXT("test.wav"), NULL, SND_FILENAME);
	//PlaySound(TEXT("walk.wav"), NULL, SND_ASYNC);
}
