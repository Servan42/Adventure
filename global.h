#ifndef _GLOBAL_H
#define _GLOBAL_H

typedef struct _player {
	unsigned int hp;
	unsigned int hpMax;
	unsigned int lvl;
	double xp;
	double xpStage;
	char playerName[100];
	} player, *pplayer;

#endif