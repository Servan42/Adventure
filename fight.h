/*
* @author CHARLOT Servan
*/

#ifndef _FIGHT_H
#define _FIGHT_H

#include "global.h"

/**
* @struct _monster fight.h monster
* @brief Monster attributes.
*/
typedef struct _monster {
	int hp; /*!< Current health points */
	unsigned int hpMax; /*!< Maximum number of health points */
	unsigned int lvl; /*!< Current level */
	int ascii; /*!< Number referencing an ASCII drawing in display_fight.h : display_monster_ascii(...)*/
} monster, *pmonster;

/**
* @enum states
* @brief States used in the automatons
*/
typedef enum {
	STATE_CHOICE,
	STATE_ATTACK,
	STATE_HEAL,
	STATE_RUN,
	STATE_VICTORY,
	STATE_DEFEAT,
	STATE_RUN_SUCCESS
} states;

int alea(int a, int b);
void init_monster(pmonster M, pplayer P);
int action_choice();
void xp(pplayer P, pmonster M, int *number_of_level_earned, int *number_of_xp_earned);
void attack(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster);
void heal(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster);
int run(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster);
int fight(pplayer P);

#endif