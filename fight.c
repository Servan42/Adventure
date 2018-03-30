/**
* @file fight.c
* @brief Functional core of the programm.
* @author CHARLOT Servan
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fight.h"
#include "display_fight.h"

/**
* @fn int alea(int a, int b)
* @brief Return a random number between [a;b].
* @param a Lower bound. Inclusive
* @param b Upper bound. Inclusive
* @return Random number between a and b.
*/
int alea(int a, int b){
    return (rand()%(b-a+1)+a);
}

/**
* @fn void init_monster(pmonster M, pplayer P)
* @brief Initiate the monster attributes.
* @param M Pointer on the monster structure.
* @param P Pointer on the player structure.
*/
void init_monster(pmonster M, pplayer P){
	M->ascii = alea(1,5);

	if (P->lvl <= 4)
		M->lvl = alea(1, P->lvl+4);
	else
		M->lvl = alea(P->lvl-4, P->lvl+4);

	M->hpMax = alea(5*M->lvl, 50*M->lvl);
	M->hp = M->hpMax;
}

/**
* @fn int action_choice()
* @brief Asks the player which action he wants to do.
* @return Number referencing the action.
*/
int action_choice(){
    char choice=0;

    while(choice!='1' && choice!='2' && choice!='3')
    {
        printf("\n\033[1mWhat do you want to do ? : \033[0m\n");
        printf("1 : Attack\n2 : Spell\n3 : Flee\n--> ");
        scanf("%c",&choice);
		if(choice != '\n') getchar();
    }

    return choice-'0';
}

/**
* @fn int spell_choice()
* @brief Asks the player which action he wants to do.
* @return Number referencing the action.
*/
int spell_choice(){
    char choice=0;

    while(choice!='1' && choice!='2' && choice!='3' && choice!='4')
    {
        printf("\n\033[1mWhich spell do you want to cast ? : \033[0m\n");
        printf("1 : Fireball\n2 : Heal\n3 : Shield\n4 : Back\n--> ");
        scanf("%c",&choice);
        if(choice != '\n') getchar();
    }

    return choice-'0';
}

/**
* @fn void xp(pplayer P, pmonster M, int *number_of_level_earned, int *number_of_xp_earned)
* @brief Gives experience to the player when he kills a monster.
* @param P Pointer on the player structure.
* @param M Pointer on the monster structure.
* @param[out] number_of_level_earned At the end of the function, contains the number of levels the player earned.
* @param[out] number_of_xp_earned At the end of the function, contains of xp points the player earned.
*/
void xp(pplayer P, pmonster M, int *number_of_level_earned, int *number_of_xp_earned){
    *number_of_level_earned = 0;
    *number_of_xp_earned = (10 * M->lvl * M->lvl * P->lvl);
    P->xpTotal = P->xpTotal + *number_of_xp_earned;
    P->xp += *number_of_xp_earned;
    // Level up each time a level is passed.
    // Reports remaining the experience on the next level.
    while(P->xp >= P->xpStage){
        P->xp -= P->xpStage;
        P->xpStage *= 2;
        (P->lvl)++;
        (*number_of_level_earned)++;
        P->hpMax = 50 * P->lvl;
        P->shieldMax = P->hpMax;
        P->hp = P->hpMax;
        P->magic = P->magicMax;
    }
}

void monster_attack(pplayer P, pmonster M, int *damagesToPlayer){
    // Monster's attack
    *damagesToPlayer=alea(1*M->lvl,10*M->lvl);
    if(P->shield > 0){
        P->shield = P->shield - *damagesToPlayer;
        if(P->shield < 0){
            *damagesToPlayer = abs(P->shield);
            P->shield = 0;
            P->hp=P->hp-*damagesToPlayer;
            if(P->hp < 0) P->hp = 0;
        } 
    } else {        
        P->hp=P->hp-*damagesToPlayer;
        if(P->hp < 0) P->hp = 0;
    }
}

/**
* @fn void attack(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster)
* @brief Computes all the life changes happening when the player trades damages with the monster. 
* @param P Pointer on the player structure.
* @param M Pointer on the monster structure.
* @param[out] text_id Reference to the text that must be displayed by the UI.
* @param[out] lifeChangePlayer Ends up containing by how many the player's life changed.
* @param[out] lifeChangePlayer Ends up containing by how many the monster's life changed.
*/
void attack(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster){
    int critical, damagesToPlayer,damagesToMonster;
    critical = alea(0,101);

    if(critical>=CC){
    	// Player does a critical hit
        *text_id = 2;
        
		// Player's attack
        damagesToMonster=alea(1*P->lvl,10*P->lvl)*2;
        M->hp=M->hp-damagesToMonster;
        if(M->hp < 0) M->hp = 0;

        *lifeChangeMonster = 0-damagesToMonster;
    } else if (critical<=EC){
        // Player miss
    	*text_id = 3;
        *lifeChangeMonster = 0;
    } else {
        // Normal damage trade.
    	*text_id = 1;
        // Player's attack
        damagesToMonster=alea(1*P->lvl,10*P->lvl);
        M->hp=M->hp-damagesToMonster;
        if(M->hp < 0) M->hp = 0;

        *lifeChangeMonster = 0-damagesToMonster;
    }

    // Monster's attack
    monster_attack(P, M, &damagesToPlayer);
    if(P->shield > 0) *text_id = 11 + (*text_id - 1);

    *lifeChangePlayer = 0-damagesToPlayer;
}

/**
* @fn void heal(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster)
* @brief Computes all the life changes happening when the player tries to heal himself. 
* @param P Pointer on the player structure.
* @param M Pointer on the monster structure.
* @param[out] text_id Reference to the text that must be displayed by the UI.
* @param[out] lifeChangePlayer Ends up containing by how many the player's life changed.
* @param[out] lifeChangePlayer Ends up containing by how many the monster's life changed.
*/
void heal(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster){
    int heal,damagesToPlayer;

    // Healing process
    heal = alea(5*P->lvl,10*P->lvl);
    P->hp=P->hp+heal;
    if (P->hp>=P->hpMax){
        heal=heal-(P->hp-P->hpMax);
        P->hp=P->hpMax;
    }
    // Monster's attack
    monster_attack(P, M, &damagesToPlayer);

    if(P->shield > 0){
        // Damages to the shield
        *text_id = 14;
        *lifeChangePlayer = 0-damagesToPlayer;
        // Max Heal
        *lifeChangeMonster = heal;

    } else {
        *text_id = 4;
        *lifeChangePlayer = heal-damagesToPlayer;
        *lifeChangeMonster = 0;
    }
}

/**
* @fn void run(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster)
* @brief Decide whether the player is able to run away or not.
* @param P Pointer on the player structure.
* @param M Pointer on the monster structure.
* @param[out] text_id Reference to the text that must be displayed by the UI.
* @param[out] lifeChangePlayer Ends up containing by how many the player's life changed.
* @param[out] lifeChangePlayer Ends up containing by how many the monster's life changed.
* @return 1 if the players succeed to run away, 0 otherwise.
*/
int run(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster){
    int fui,damagesToPlayer;

    fui=alea(0,101);

    if(fui > FUITE) {
        // Flee successful
        M->hp = 0;
        *lifeChangePlayer = 0;
        *lifeChangeMonster = 0;
        system("clear");
        display_header(P,*lifeChangePlayer);
        display_run();
        getchar();
        return 1;

    } else {
        // Fails to flee
    	*text_id = 5;
        // Monster's attack
        monster_attack(P, M, &damagesToPlayer);

        *lifeChangePlayer = 0-damagesToPlayer;
        *lifeChangeMonster = 0;
        return 0;
    }
}

/**
* @fn void fireball(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster)
* @brief Computes all the life changes happening when the player casts a fireball. 
* @param P Pointer on the player structure.
* @param M Pointer on the monster structure.
* @param[out] text_id Reference to the text that must be displayed by the UI.
* @param[out] lifeChangePlayer Ends up containing by how many the player's life changed.
* @param[out] lifeChangePlayer Ends up containing by how many the monster's life changed.
*/
void fireball(pplayer P, pmonster M, int *text_id, int *lifeChangePlayer, int *lifeChangeMonster){
    int damagesToMonster;

    *text_id = 9;

    // Player's attack
    damagesToMonster=2*alea(1*P->lvl,10*P->lvl);
    M->hp=M->hp-damagesToMonster;
    if(M->hp < 0) M->hp = 0;

    *lifeChangeMonster = 0-damagesToMonster;
}

/**
* @fn int fight(pplayer P)
* @brief Main loop for the fight against a monster.
*        Contains the automaton of the fight.
* @param P Pointer on the player structure.
* @return 1 if the player is still alive, 0 otherwise.
*/
int fight(pplayer P){
    int action, lifeChangePlayer = 0, lifeChangeMonster = 0, text_id = 0;
    int monsterAlive = 1, playerAlive = 1;
    int lvlEarned = 0, xpEarned = 0;
    int fui = 0;
    int damagesToPlayer;
    // The "console" are the 4 lines displayed under the monster pane.
    // This array containe for each 4 line the 3 following values : 
    // [i][0] = text_id, [i][1] = lifeChangePlayer, [i][2] = lifeChangeMonster
    int buffConsole[4][3];
    pmonster M;

    // Initiation stuff
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
        // Fight automaton.
        switch(state){
            case STATE_CHOICE:
                // Asking the player what he wants to do.
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
                        state = STATE_SPELL;
                        break;
                    case 3:
                        state = STATE_RUN;
                        break;
                }
                break;

            case STATE_ATTACK:
                // PLayer chooses to attack
                attack(P, M, &text_id, &lifeChangePlayer, &lifeChangeMonster);
                if(P->hp == 0){
                    state = STATE_DEFEAT;
                } else if(M->hp == 0){
                    state = STATE_VICTORY;
                } else {
                    state = STATE_CHOICE;
                }
                break;

            case STATE_SPELL:
                // Players chooses to cast a spell
                system("clear");
                display_header(P,lifeChangePlayer);
                display_monster(M,P, lifeChangeMonster);
                if(P->magic == 0){
                    text_id = 6;
                    state = STATE_CHOICE;
                } else {
                    text_id = 7;
                    display_console(buffConsole ,text_id, lifeChangePlayer, lifeChangeMonster);
                    action = spell_choice();
                    switch(action){
                        case 1:
                            (P->magic)--;
                            state = STATE_FIREBALL;
                            break;
                        case 2:
                            (P->magic)--;
                            state = STATE_HEAL;
                            break;
                        case 3:
                            (P->magic)--;
                            state = STATE_SHIELD;
                            break;
                        case 4:
                            text_id = 8;
                            state = STATE_CHOICE;
                            break;
                    }
                }
                break;

            case STATE_FIREBALL:
                // The player choses to cast a fireball
                fireball(P, M, &text_id, &lifeChangePlayer, &lifeChangeMonster);
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
                // Keeping the heal max value in a line that is going to get erased
                // in the buffer. Dirty but optimised.
                buffConsole[0][0] = lifeChangeMonster;
                // Putting it again at it's normal value.
                lifeChangeMonster = 0;
                if(P->hp == 0){
                    state = STATE_DEFEAT;
                } else {
                    state = STATE_CHOICE;
                }
                break;

            case STATE_SHIELD:
                text_id = 10;
                P->shield = P->shieldMax;
                monster_attack(P, M, &damagesToPlayer);
                lifeChangePlayer = 0-damagesToPlayer;
                state = STATE_CHOICE;
                break;

            case STATE_RUN:
                // Player chooses to try to run away
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
                // Flee successful
                monsterAlive = 0;
                break;

            case STATE_VICTORY:
                // Monster is dead
                monsterAlive = 0;          
                xp(P, M, &lvlEarned, &xpEarned);
                lifeChangePlayer = 0;
                system("clear");
                display_header(P,lifeChangePlayer);
                display_victory(lvlEarned,xpEarned);
                getchar();
                break;

            case STATE_DEFEAT:
                // Player is dead
                playerAlive = 0;
                system("clear");
                display_header(P,lifeChangePlayer);
                display_you_lose();
                break;
        }
    }

    return playerAlive;
}