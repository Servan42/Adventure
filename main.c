#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

void init_game(pplayer P){
	printf("Bienvenue ! Quel est ton nom aventurier ?\n-->");
    scanf("%s",P->playerName);
#if TERMINAL_CLEAR
    system("clear");
#endif

    P->hp=50;
    P->hpMax=50;
    P->lvl=1;
    P->xp=0;
    P->xpStage=10;
}

int main(int argc, char const *argv[])
{
	pplayer P;
	int gameover = 0;

	P = malloc(sizeof(player));

	init_game(P);

    while(gameover!=1)
    {
        gameover = fight(P);
    }

	return 0;
}