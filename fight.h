#ifndef _FIGHT_H
#define _FIGHT_H

#include "global.h"

typedef struct _monster {
	unsigned int hp;
	unsigned int hpMax;
	unsigned int lvl;
	int ascii;
} monster, *pmonster;

int alea(int a, int b);
void init_monster(pmonster M, pplayer P);
int fight(pplayer P);

#endif