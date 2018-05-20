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
	printf("Welcome ! What is your name ?\n--> ");
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
    P->money = 10;
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

    while(choice!='1' && choice!='2')
    {
        printf("\033[1mWhat do you want to do ? : \033[0m\n");
        printf("1 : Fight\n2 : Shop\n--> ");
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
        printf("1 : Magic Potion (%s%d)\n2 : Health Potion (%s%d)\n3 : Back\n--> ", CURRENCY, MAGIC_POTION_PRICE, CURRENCY, HP_POTION_PRICE);
        scanf("%c",&choice);
        if(choice != '\n') getchar();
    }

    return choice-'0';
}

int main(int argc, char const *argv[])
{
    /*
    printf("----------------------------------------------------------\n");
    printf("DISCLAIMER :\n\n");
    printf("This release is still in developement.\n");
    printf("To play on a stable version, please checkout the Version 1.0\n\n");
    printf("WORK IN PROGRESS : \n\n");
    printf("The balancing is not done yet.\n");
    printf("----------------------------------------------------------\n\n");
    getchar();
    */

    display_help();

    // Ask the user if he wants the compact version of the game.
    char choice;
    do{
        printf("\033[1mDisclaimer :\033[0m\n\n");
        printf("Do you want to run the game in compact version ?\n");
        printf("(In compact version, the monster image is not displayed. Useful if you have a small screen).\n");
        printf("Yes(y) / No(n) : ");
        scanf("%c",&choice);
        if(choice != '\n') getchar();
        system("clear");
    } while(choice != 'y' && choice != 'n');
    if(choice == 'y') compactVersion = 1;
    else compactVersion = 0;

    // Setting up the game.
	pplayer P;
	int playerAlive = 1;
    srand(time(NULL));

    statesMain state = STATE_MAIN_CHOICE;
    int action;

	P = malloc(sizeof(player));

	init_game(P);

    // Game start.
    while(playerAlive)
    {
        if(P->money < MAGIC_POTION_PRICE && P->money < HP_POTION_PRICE && P->potionHP + P->potionMagic == 0) state = STATE_FIGHT;

        switch(state){
            case STATE_MAIN_CHOICE:
                system("clear");
                display_header(P,0);
                display_inventory(P);
                action = main_choice();
                switch(action){
                    case 1:
                        state = STATE_FIGHT;
                        break;
                    case 2:
                        state = STATE_SHOP;
                        break;
                }
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
                display_inventory(P);
                action = shop_choice();
                switch(action){
                    case 1:
                        state = STATE_BUY_MAGIC;
                        break;
                    case 2:
                        state = STATE_BUY_HP;
                        break;
                    case 3:
                        state = STATE_MAIN_CHOICE;
                        break;
                }
                break;

            case STATE_BUY_HP:
                state = STATE_SHOP;
                if(P->money >= HP_POTION_PRICE){
                    P->money -= HP_POTION_PRICE;
                    P->potionHP += 1;
                    system("clear");
                    display_header(P,0);
                	display_inventory(P);
                    printf("You bought a Health Potion.\n");
                } else {
                    printf("\nYou don't have enough money to buy this.\n");
                }
                getchar();
                break;

            case STATE_BUY_MAGIC:
                state = STATE_SHOP;
                if(P->money >= MAGIC_POTION_PRICE){
                    P->money -= MAGIC_POTION_PRICE;
                    P->potionMagic += 1;
                    system("clear");
                    display_header(P,0);
                	display_inventory(P);
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