#ifndef _GLOBAL_H
#define _GLOBAL_H

#define TERMINAL_CLEAR 1 // OS Sensistive

typedef struct _player {
	int hp;
	int hpMax;
   	int lvl;
    int xp;
    int xpStage;
	char playerName[100];
	} player, *pplayer;

#endif