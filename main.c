/**
* @file main.c
* @author CHARLOT Servan
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

/**
* @fn void init_game(pplayer P)
* @brief Asks the name of the player and initiate his structure.
* @param P Pointer on the player structure.
*/
void init_game(pplayer P){
	printf("Welcome ! What is your name ?\n-->");
    scanf("%s",P->playerName);
    getchar();
    system("clear");

    P->hpMax = 50;
    P->hp = P->hpMax;
    P->magicMax = 100;
    P->magic = P->magicMax;
    P->shieldMax = P->hpMax;
    P->shield = 0;
    P->lvl = 1;
    P->xp = 0;
    P->xpStage = 10;
}

int main(int argc, char const *argv[])
{
    printf("----------------------------------------------------------\n");
    printf("DISCLAIMER :\n\n");
    printf("This release is still in developement.\n");
    printf("To play on a stable version, please checkout the Version 1.0\n\n");
    printf("WORK IN PROGRESS : \n\n");
    printf("The balancing is not done yet.\n");
    printf("There is no way to earn magic points.\n");
    printf("  -> A shop is going to be implemented in order to buy health and magic potions.\n");
    printf("----------------------------------------------------------\n\n");

	pplayer P;
	int playerAlive = 1;
    srand(time(NULL));

	P = malloc(sizeof(player));

	init_game(P);

    while(playerAlive)
    {
        playerAlive = fight(P);
    }

	return 0;
}