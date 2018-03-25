#ifndef _FIGHT_H
#define _FIGHT_H

#include "global.h"

typedef struct _monster {
	int hp;
	unsigned int hpMax;
	unsigned int lvl;
	int ascii;
} monster, *pmonster;

int alea(int a, int b);
void init_monster(pmonster M, pplayer P);
int action_choice();
void xp(pplayer P, pmonster M, int *number_of_level_earned, int *number_of_xp_earned);
void attack(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster);
void heal(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster);
int run(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster);
int fight(pplayer P);

#endif