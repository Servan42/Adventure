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
    P->magicMax = 5;
    P->magic = P->magicMax;
    P->shieldMax = P->hpMax;
    P->shield = 0;
    P->lvl = 1;
    P->xp = 0;
    P->xpStage = 10;
    P->money = 1000;
    P->potionHP = 0;
    P->potionMagic = 0;
}

/**
* @fn int main_choice()
* @brief Asks the player which action he wants to do.
* @return Number referencing the action.
*/
int main_choice(){
    char choice=0;

    while(choice!='1' && choice!='2' && choice!='3')
    {
        printf("\033[1mWhat do you want to do ? : \033[0m\n");
        printf("1 : Fight\n2 : Shop\n3 : Show Inventory\n--> ");
        scanf("%c",&choice);
        if(choice != '\n') getchar();
    }

    return choice-'0';
}

/**
* @fn int shop_choice()
* @brief Asks the player which action he wants to do.
* @return Number referencing the action.
*/
int shop_choice(){
    char choice=0;

    while(choice!='1' && choice!='2' && choice!='3')
    {
        printf("\033[1mWhat do you want to buy ? : \033[0m\n");
        printf("1 : Health Potion ($20)\n2 : Magic Potion ($20)\n3 : Back\n--> ");
        scanf("%c",&choice);
        if(choice != '\n') getchar();
    }

    return choice-'0';
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

    statesMain state = STATE_MAIN_CHOICE;
    int action;

	P = malloc(sizeof(player));

	init_game(P);

    while(playerAlive)
    {
        if(P->money < 20 && P->potionHP + P->potionMagic == 0) state = STATE_FIGHT;

        switch(state){
            case STATE_MAIN_CHOICE:
                system("clear");
                display_header(P,0);
                action = main_choice();
                switch(action){
                    case 1:
                        state = STATE_FIGHT;
                        break;
                    case 2:
                        state = STATE_SHOP;
                        break;
                    case 3:
                        state = STATE_SHOW_INVENTORY;
                        break;
                }
                break;

            case STATE_SHOW_INVENTORY:
                system("clear");
                display_header(P,0);
                printf("Money : $%d\n", P->money);
                printf("Health potion(s) : %d\n",P->potionHP);
                printf("Magic potion(s) : %d\n",P->potionMagic);
                getchar();
                state = STATE_MAIN_CHOICE;
                break;

            case STATE_FIGHT:
                playerAlive = fight(P);
                state = STATE_MAIN_CHOICE;
                break;

            case STATE_GAME_OVER:
                state = STATE_MAIN_CHOICE;
                break;

            case STATE_SHOP:
                system("clear");
                display_header(P,0);
                action = shop_choice();
                switch(action){
                    case 1:
                        state = STATE_BUY_HP;
                        break;
                    case 2:
                        state = STATE_BUY_MAGIC;
                        break;
                    case 3:
                        state = STATE_MAIN_CHOICE;
                        break;
                }
                break;

            case STATE_BUY_HP:
                state = STATE_SHOP;
                if(P->money >= 20){
                    P->money -= 20;
                    P->potionHP += 1;
                    system("clear");
                    display_header(P,0);
                    printf("You bought a Health Potion.\n");
                } else {
                    printf("\nYou don't have enough money to buy this.\n");
                }
                getchar();
                break;

            case STATE_BUY_MAGIC:
                state = STATE_SHOP;
                if(P->money >= 20){
                    P->money -= 20;
                    P->potionMagic += 1;
                    system("clear");
                    display_header(P,0);
                    printf("You bought a Magic Potion.\n");
                } else {
                    printf("\nYou don't have enough money to buy this.\n");
                }
                getchar();
                break;
        }

    }

	return 0;
}