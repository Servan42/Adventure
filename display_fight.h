#ifndef _DISPLAY_FIGHT_H
#define _DISPLAY_FIGHT_H

#include "global.h"
#include "fight.h"

void display_header(pplayer P, int lifeChangePlayer);
void display_monster(pmonster M, pplayer P, int lifeChangeMonster);
double my_round(double a);
void display_bar_player(pplayer P, int bar);
void display_bar_monster(pmonster M);
void display_appears();
void display_you_lose();
void display_run();
void display_victory(int lvlEarned, int xpEarned);
void display_monster_ascii(int nMonster);
void display_text(int text_id);


#endif