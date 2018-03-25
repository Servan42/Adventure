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

int action_choice(){
    char choice=0;

    while(choice!='1' && choice!='2' && choice!='3')
    {
        printf("\nQue faire ? : \n");
        printf("1 : Attaquer\n2 : Se soigner\n3 : Fuir\n--> ");
        scanf("%c",&choice);
		getchar();
    }

    return choice-'0';
}

void xp(pplayer P, pmonster M, int *number_of_level_earned, int *number_of_xp_earned){
    *number_of_level_earned = 0;
    *number_of_xp_earned = (10 * M->lvl * M->lvl * P->lvl);
    P->xpTotal = P->xpTotal + *number_of_xp_earned;
    P->xp += *number_of_xp_earned;
    while(P->xp >= P->xpStage){
        P->xp -= P->xpStage;
        P->xpStage *= 2;
        (P->lvl)++;
        P->hpMax = 50 * P->lvl;
        P->hp = P->hpMax;
        (*number_of_level_earned)++;
    }
}

void attack(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster){
    int critical, damagesToPlayer,damagesToMonster;
    critical = alea(0,101);

    if(critical>=CC){
    	*text_id = 2;
        
		// Attaque du joueur        
        damagesToMonster=alea(1*P->lvl,10*P->lvl)*2;
        M->hp=M->hp-damagesToMonster;
        if(M->hp < 0) M->hp = 0;

        // Attaque du monstre
        damagesToPlayer=alea(1*M->lvl,10*M->lvl);
        P->hp=P->hp-damagesToPlayer;
        if(P->hp < 0) P->hp = 0;

        *lifeChangePlayer = 0-damagesToPlayer;
        *lifeChangeMonster = 0-damagesToMonster;
    } else if (critical<=EC){
    	*text_id = 3;

        // Attaque du monstre 
        damagesToPlayer=alea(1*M->lvl,10*M->lvl);
        P->hp=P->hp-damagesToPlayer;
        if(P->hp < 0) P->hp = 0;

        *lifeChangePlayer = 0-damagesToPlayer;
        *lifeChangeMonster = 0;
    } else {
    	*text_id = 1;

    	// Attaque du monstre
        damagesToPlayer=alea(1*M->lvl,10*M->lvl);
        P->hp=P->hp-damagesToPlayer;
        if(P->hp < 0) P->hp = 0;

		// Attaque du joueur
        damagesToMonster=alea(1*P->lvl,10*P->lvl);
        M->hp=M->hp-damagesToMonster;
        if(M->hp < 0) M->hp = 0;

        *lifeChangePlayer = 0-damagesToPlayer;
        *lifeChangeMonster = 0-damagesToMonster;
    }


}

void heal(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster){
    int heal,damagesToPlayer;

    *text_id = 4;

    heal = alea(5*P->lvl,10*P->lvl);
    P->hp=P->hp+heal;
    if (P->hp>=P->hpMax){
        heal=heal-(P->hp-P->hpMax);
        P->hp=P->hpMax;
    }

    // Monster attack
    damagesToPlayer=alea(1*M->lvl,10*M->lvl);
    P->hp=P->hp-damagesToPlayer;
    if(P->hp < 0) P->hp = 0;

    *lifeChangePlayer = heal-damagesToPlayer;
    *lifeChangeMonster = 0;
}

int run(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster){
    int fui,damagesToPlayer;

    fui=alea(0,101);

    if(fui > FUITE)
    {
        M->hp = 0;
        *lifeChangePlayer = 0;
        *lifeChangeMonster = 0;
        system("clear");
        display_header(P,*lifeChangePlayer);
        display_run();
        getchar();
        return 1;

    }
    else
    {
    	*text_id = 5;
        damagesToPlayer=alea(1*M->lvl,10*M->lvl);
        P->hp=P->hp-damagesToPlayer;
        if(P->hp < 0) P->hp = 0;

        *lifeChangePlayer = 0-damagesToPlayer;
        *lifeChangeMonster = 0;
        return 0;
    }
}


int fight(pplayer P){
	// Init the new monster
	pmonster M;
	M = malloc(sizeof(monster));
	init_monster(M, P);
	int action, lifeChangePlayer = 0, lifeChangeMonster = 0, text_id = 0;
	int monsterAlive = 1, playerAlive = 1;
	int lvlEarned = 0, xpEarned = 0;
    int fui = 0;
	
	// One-time introduction (one per monster)
	system("clear");
	display_header(P,lifeChangePlayer);
	display_appears();
	getchar();
	system("clear");
	display_header(P,lifeChangePlayer);
	display_monster(M,P, lifeChangeMonster);
	display_text(text_id);

	// Fight loop
	while(monsterAlive && playerAlive){
		action = action_choice();
		switch(action){
			case 1:
				attack(P, M, &text_id, &lifeChangePlayer, &lifeChangeMonster);
				break;
			case 2:
				heal(P, M, &text_id, &lifeChangePlayer, &lifeChangeMonster);
				break;
			case 3:
				fui = run(P, M, &text_id, &lifeChangePlayer, &lifeChangeMonster);
				break;
		}

		if(P->hp == 0){
			// Défaite du joueur
			playerAlive = 0;
			system("clear");
			display_header(P,lifeChangePlayer);
			display_you_lose();
		}
		else if(M->hp == 0){
			// Monstre vaincu
			monsterAlive = 0;
			if(fui == 0){            
                xp(P, M, &lvlEarned, &xpEarned);
                lifeChangePlayer = 0;
    			system("clear");
    			display_header(P,lifeChangePlayer);
    			display_victory(lvlEarned,xpEarned);
    			getchar();
            }
		}
		else {
			// Combat en cours
            system("clear");
            display_header(P,lifeChangePlayer);
            display_monster(M,P, lifeChangeMonster);
            display_text(text_id);
        }
		text_id = -1;

	}

	return playerAlive;
}