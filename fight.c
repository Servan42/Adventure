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
        printf("\n\033[1mWhat do you want to do ? : \033[0m\n");
        printf("1 : Attack\n2 : Heal\n3 : Flee\n--> ");
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
    int action, lifeChangePlayer = 0, lifeChangeMonster = 0, text_id = 0;
    int monsterAlive = 1, playerAlive = 1;
    int lvlEarned = 0, xpEarned = 0;
    int fui = 0;
    int buffConsole[4][3];
    pmonster M;

    states state = STATE_CHOICE;
    
    M = malloc(sizeof(monster));
    init_monster(M, P);
    for(int i = 0; i < 4; i++){
        buffConsole[i][0] = -1;
        for(int j = 1; j < 3; j++){
            buffConsole[i][j] = 0;
        }
    }

    // One-time introduction (one per monster)
    system("clear");
    display_header(P,lifeChangePlayer);
    display_appears();
    getchar();

    while(monsterAlive && playerAlive){
        switch(state){
            case STATE_CHOICE:
                system("clear");
                display_header(P,lifeChangePlayer);
                display_monster(M,P, lifeChangeMonster);
                display_console(buffConsole ,text_id, lifeChangePlayer, lifeChangeMonster);
                action = action_choice();
                switch(action){
                    case 1:
                        state = STATE_ATTACK;
                        break;
                    case 2:
                        state = STATE_HEAL;
                        break;
                    case 3:
                        state = STATE_RUN;
                        break;
                }
                break;
            case STATE_ATTACK:
                attack(P, M, &text_id, &lifeChangePlayer, &lifeChangeMonster);
                if(P->hp == 0){
                    state = STATE_DEFEAT;
                } else if(M->hp == 0){
                    state = STATE_VICTORY;
                } else {
                    state = STATE_CHOICE;
                }
                break;
            case STATE_HEAL:
                heal(P, M, &text_id, &lifeChangePlayer, &lifeChangeMonster);
                if(P->hp == 0){
                    state = STATE_DEFEAT;
                } else {
                    state = STATE_CHOICE;
                }
                break;
            case STATE_RUN:
                fui = run(P, M, &text_id, &lifeChangePlayer, &lifeChangeMonster);
                if(P->hp == 0){
                    state = STATE_DEFEAT;
                } else if(fui == 0){
                    state = STATE_CHOICE;
                } else {
                    state = STATE_RUN_SUCCESS;
                }
                break;
            case STATE_RUN_SUCCESS:
                monsterAlive = 0;
                break;
            case STATE_VICTORY:
                monsterAlive = 0;          
                xp(P, M, &lvlEarned, &xpEarned);
                lifeChangePlayer = 0;
                system("clear");
                display_header(P,lifeChangePlayer);
                display_victory(lvlEarned,xpEarned);
                getchar();
                break;
            case STATE_DEFEAT:
                playerAlive = 0;
                system("clear");
                display_header(P,lifeChangePlayer);
                display_you_lose();
                break;
        }
    }

    return playerAlive;
}