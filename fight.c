#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fight.h"
#include "display_fight.h"

//Return a random number between [a;b];
int alea(int a, int b){
    return (rand()%(b-a+1)+a);
}

void init_monster(pmonster M, pplayer P){
	M->ascii = alea(1,5);

	if (P->lvl <= 4)
		M->lvl = alea(1, P->lvl+4);
	else
		M->lvl = alea(P->lvl-4, P->lvl+4);

	M->hpMax = alea(5*M->lvl, 50*M->lvl);
	M->hp = M->hpMax;
}

int fight(pplayer P){
	// Init the new monster
	pmonster M;
	M = malloc(sizeof(monster));
	init_monster(M, P);
	
	// One-time introduction (one per monster)
	display_header(P);
	display_appears();
	getchar();
	system("clear");

	// Fight loop

	while(M->hp > 0){
		display_header(P);
		display_monster(M->ascii);
		
		break;	
	}

	return 1;
}