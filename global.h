#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <math.h>

typedef struct _player {
	int hp;
	unsigned int hpMax;
	unsigned int lvl;
	double xpTotal;
	double xp;
	double xpStage;
	char playerName[100];
	} player, *pplayer;

#define CC 95
#define EC 5
#define FUITE 25

#endif