/*
* @author CHARLOT Servan
*/

#ifndef _MAIN_H
#define _MAIN_H

#include "fight.h"
#include "display_fight.h"
#include "global.h"

int main_choice();
int shop_choice();


/**
* @enum states
* @brief States used in the main automaton
*/
typedef enum {
	STATE_MAIN_CHOICE,
	STATE_SHOW_INVENTORY,
	STATE_FIGHT,
	STATE_GAME_OVER,
	STATE_SHOP,
	STATE_BUY_HP,
	STATE_BUY_MAGIC
} statesMain;

void init_game(pplayer P);

#endif