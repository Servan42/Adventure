#ifndef _FIGHT_H
#define _FIGHT_H

#include "global.h"

typedef struct _monster {
	int hp;
	unsigned int hpMax;
	unsigned int lvl;
	int ascii;
} monster, *pmonster;

#define STATE_CHOICE 0
#define STATE_ATTACK 1
#define STATE_HEAL 2
#define STATE_RUN 3
#define STATE_VICTORY 4
#define STATE_DEFEAT 5
#define STATE_RUN_SUCCESS 6

int alea(int a, int b);
void init_monster(pmonster M, pplayer P);
int action_choice();
void xp(pplayer P, pmonster M, int *number_of_level_earned, int *number_of_xp_earned);
void attack(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster);
void heal(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster);
int run(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster);
int fight(pplayer P);

#endif