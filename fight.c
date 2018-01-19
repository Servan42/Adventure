#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fight.h"

//Return a random number between [a;b];
int alea(int a, int b){
    return (rand()%(b-a+1)+a);
}

int fight(pplayer P){
	display_header(P);
	return 1;
}