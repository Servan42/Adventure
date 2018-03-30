/**
* @file display_fight.c
* @brief User interface of the programm.
* @author CHARLOT Servan
*/

#include <stdio.h>
#include <stdlib.h>
#include "display_fight.h"

/**
* @def HEALTH_BAR_PLAYER
* @brief Reference for the player's health bar
*/
#define HEALTH_BAR_PLAYER 1

/**
* @def XP_BAR
* @brief Reference for the experience bar
*/
#define XP_BAR 2

/**
* @def MAGIC_BAR
* @brief Reference for the magic bar
*/
#define MAGIC_BAR 3

/**
* @def SHIELD_BAR
* @brief Reference for the magic bar
*/
#define SHIELD_BAR 4


/**
* @fn void display_split()
* @brief Displays a bar that simulate a split between the pannels. 
*/
void display_split(){
	printf("\033[40;8m----------------------------------------------------------------------\033[0m\n");	
}

/**
* @fn void display_header(pplayer P, int lifeChangePlayer)
* @brief Displays the upper panel containing the following :
*		 Name, level, health, health bar, experience, experience bar.
* @param P Pointer on the player structure.
* @param lifeChangePlayer By how many the player's life changed.
*/
void display_header(pplayer P, int lifeChangePlayer){
	display_split();
	printf("\033[1m%s\033[0m | ",P->playerName);
	printf("\033[1mLevel :\033[0m \033[96m%d\033[0m\n", P->lvl);
	printf("\033[1mHealth :\033[0m %d/%d HP\n",P->hp,P->hpMax);
	
	display_bar_player(P, HEALTH_BAR_PLAYER);
	if(P->shield > 0){
		printf(" | \033[1mShield :\033[0m ");
		display_bar_player(P, SHIELD_BAR);
		if(lifeChangePlayer > 0){
	    	printf("\033[32m +%d\033[0m HP\n", lifeChangePlayer);
	    } else if(lifeChangePlayer < 0){
	    	printf("\033[31m %d\033[0m SP\n", lifeChangePlayer);
	    } else {
	    	printf("\n");
	    }
	} else {	
		if(lifeChangePlayer > 0){
	    	printf("\033[32m +%d\033[0m HP\n", lifeChangePlayer);
	    } else if(lifeChangePlayer < 0){
	    	printf("\033[31m %d\033[0m HP\n", lifeChangePlayer);
	    } else {
	    	printf("\n");
	    }
	}

	printf("\033[1mExperience :\033[0m %0.0lf/%0.0lf XP\n",P->xp,P->xpStage);
	display_bar_player(P, XP_BAR); printf("\n");

	printf("\033[1mMagic :\033[0m %d/%d MP\n",P->magic,P->magicMax);
	display_bar_player(P, MAGIC_BAR); printf("\n");

	display_split(); printf("\n");
}

/**
* @fn void display_monster(pmonster M, pplayer P, int lifeChangeMonster)
* @brief Displays the monster ascci, its level and its life.
* @param M Pointer on the monster structure.
* @param P Pointer on the player structure.
* @param lifeChangeMonster By how many the player's life changed.
*/
void display_monster(pmonster M, pplayer P, int lifeChangeMonster){
	display_monster_ascii(M->ascii);
	printf("\n");
    
    if((P->lvl + 1) == M->lvl){
        printf("\n\033[1mLevel :\033[0m \033[33m%d\033[0m\n",M->lvl);
	} else if(P->lvl < M->lvl){
        printf("\n\033[1mLevel :\033[0m \033[31m%d\033[0m\n",M->lvl);
    } else if(P->lvl == M->lvl){
        printf("\n\033[1mLevel :\033[0m \033[32m%d\033[0m\n",M->lvl);
	} else {
        printf("\n\033[1mLevel :\033[0m %d\n",M->lvl);
    }
	
	printf("\033[1mHealth :\033[0m %d/%d HP\n", M->hp, M->hpMax);
	
	display_bar_monster(M);
    if(lifeChangeMonster > 0){
    	printf("\033[32m +%d\033[0m HP\n", lifeChangeMonster);
    } else if(lifeChangeMonster < 0){
    	printf("\033[31m %d\033[0m HP\n", lifeChangeMonster);
    } else {
    	printf("\n");
    }


	printf("\n");
	display_split();
}

/**
* @fn double my_round(double a)
* @brief Round a double value. Choose to floor is the value is x.5
* @param a The value to round.
* @return the rounded value.
*/
double my_round(double a){
	int b = a - floor(a);
	if(b == 0.5) return floor(a);
	else return round(a);
}

/**
* @fn void display_bar_player(pplayer P, int bar)
* @brief Displays a 22 character long bar which dynamicaly moves (player).
* @param P Pointer on the player structure.
* @param bar Reference number for the bar to display (Health or xp. cf.macros)
*/
void display_bar_player(pplayer P, int bar){
	int i;
	switch(bar){
		case HEALTH_BAR_PLAYER:
			// Display the health bar
			printf("[");
			printf("\033[8m");
			if(P->hp < P->hpMax/3){
				printf("\033[41m");
			} else if(P->hp < 2*P->hpMax/3) {
				printf("\033[43m");
			} else {
				printf("\033[42m");
			}

			for(i = 0; i < round(((P->hp*100)/P->hpMax)/5); i++){
				printf("*");
			}
			printf("\033[0m");
			for(i = 0; i < my_round(20-((P->hp*100)/P->hpMax)/5); i++){
				printf(" ");
			}
			printf("]");
			break;
		case XP_BAR:
			// Display the experience bar
			printf("[\033[8m\033[45m");
			for(i = 0; i < round(((P->xp*100)/P->xpStage)/5); i++){
				printf("*");
			}
			printf("\033[0m");
			for(i = 0; i < my_round(20-((P->xp*100)/P->xpStage)/5); i++){
				printf(" ");
			}
			printf("]");
			break;
		case MAGIC_BAR:
			// Display the experience bar
			printf("[\033[8m\033[46m");
			for(i = 0; i < round(((P->magic*100)/P->magicMax)/5); i++){
				printf("*");
			}
			printf("\033[0m");
			for(i = 0; i < my_round(20-((P->magic*100)/P->magicMax)/5); i++){
				printf(" ");
			}
			printf("]");
			break;
		case SHIELD_BAR:
			// Display the shield bar
			printf("[\033[8m\033[7m");
			for(i = 0; i < round(((P->shield*100)/P->shieldMax)/5); i++){
				printf("*");
			}
			printf("\033[0m");
			for(i = 0; i < my_round(20-((P->shield*100)/P->shieldMax)/5); i++){
				printf(" ");
			}
			printf("]");
			break;
	}
}

/**
* @fn void display_bar_monster(pmonster M)
* @brief Displays a 22 character long bar which dynamicaly moves (monster).
* @param M Pointer on the monster structure.
*/
void display_bar_monster(pmonster M){
	int i;
	printf("[");
	printf("\033[8m");
	if(M->hp < M->hpMax/3){
		printf("\033[41m");
	} else if(M->hp < 2*M->hpMax/3) {
		printf("\033[43m");
	} else {
		printf("\033[42m");
	}
	
	for(i = 0; i < ((M->hp*100)/M->hpMax)/5; i++){
		printf("*");
	}
	printf("\033[0m");
	for(i = 0; i < 20-((M->hp*100)/M->hpMax)/5; i++){
		printf(" ");
	}
	printf("]");
}

/**
* @fn void display_appears()
* @brief Displays the "A MONSTER APPEARS" title.
*/
void display_appears(){
	printf("\t\t***************************\n");
	printf("\t\t*                         *\n");
	printf("\t\t*   A MONSTER APPEARS !   *\n");
	printf("\t\t*                         *\n");
	printf("\t\t***************************\n");
	printf("\n");
	display_split();

}

/**
* @fn void display_you_lose()
* @brief Displays the "YOU LOSE" title.
*/
void display_you_lose(){
	printf("\t\t***************************\n");
	printf("\t\t*                         *\n");
	printf("\t\t*        YOU LOSE !       *\n");
	printf("\t\t*                         *\n");
	printf("\t\t***************************\n");
	printf("\n");
	display_split();

}

/**
* @fn void display_run()
* @brief Displays the "YOU RUN AWAY" title.
*/
void display_run(){
	printf("\t\t***************************\n");
	printf("\t\t*                         *\n");
	printf("\t\t*      YOU RUN AWAY !     *\n");
	printf("\t\t*                         *\n");
	printf("\t\t***************************\n");
	printf("\n");
	display_split();

}

/**
* @fn void display_victory(int lvlEarned, int xpEarned)
* @brief Displays the "YOU WIN" title and the experience notifications.
* @param lvlEarned Number of levels earned by the player when he killed the monster.
* @param xpEarned Number of experience points earned by the player when he killed the monster.
*/
void display_victory(int lvlEarned, int xpEarned){
	printf("\t\t***************************\n");
	printf("\t\t*                         *\n");
	printf("\t\t*        YOU WIN !        *\n");
	printf("\t\t*                         *\n");
	printf("\t\t***************************\n");
	printf("\n");
	printf("\033[35m");
	printf("Vous earned %d experience points.\n", xpEarned);
	if(lvlEarned != 0){
		if(lvlEarned == 1) printf("Level up !\n");
		else printf("You earned %d levels !\n", lvlEarned);
	}
	printf("\033[0m\n");
	display_split();

}

/**
* @fn void display_console(int buffConsole[4][3], int text_id, int lifeChangePlayer, int lifeChangeMonster)
* @brief Displays the 4 lines of console/log in the pane under the monster.
* @param buffConsole Arrays that contains the informations to display. 4 lines with 3 information each : text_id, lifeChangePLayer, lifeChangeMonster.
* @param text_id Reference to the text that must be displayed in the console.
* @param lifeChangePlayer By how many the player's life changed.
* @param lifeChangeMonster By how many the monster's life changed.
*/
void display_console(int buffConsole[4][3], int text_id, int lifeChangePlayer, int lifeChangeMonster){
	int heal;
	if(text_id == 14){
		heal = buffConsole[0][0];
	}

	// Shift up the lines
	for(int i = 0; i < 3; i++){		
		for(int j = 0; j < 3; j++){
			buffConsole[i][j] = buffConsole[i+1][j];
		}
	}
	buffConsole[3][0] = text_id;
	buffConsole[3][1] = lifeChangePlayer;
	if(text_id == 14){
		buffConsole[3][2] = heal;
	} else {
		buffConsole[3][2] = lifeChangeMonster;
	}
	
	// Displays the lines.
	printf("\n");
	for(int i; i < 4; i++){
		display_text(buffConsole[i][0], buffConsole[i][1], buffConsole[i][2]);
	}
	printf("\n");
	display_split();
}

/**
* @fn void display_text(int text_id, int lifeChangePlayer, int lifeChangeMonster)
* @brief Display the line of text asked in text_id.
* @param text_id Reference to the text that must be displayed in the console.
* @param lifeChangePlayer By how many the player's life changed.
* @param lifeChangeMonster By how many the monster's life changed.
*/
void display_text(int text_id, int lifeChangePlayer, int lifeChangeMonster){
	switch(text_id){
		case 0:
			printf("A monster appears !\n");
			break;
		case 1:
			printf("You attack the monster !");
			printf(" Player : %d HP", lifeChangePlayer);
		    printf(" | Monster : %d HP\n", lifeChangeMonster);
			break;
		case 2:
			printf("You attack the monster ! \033[33mCritical hit !\033[0m");
			printf(" Player : %d HP", lifeChangePlayer);
		    printf(" | Monster : %d HP\n", lifeChangeMonster);
			break;
		case 3:
			printf("You attack the monster ! \033[31mYou miss !\033[0m");
			printf(" Player : %d HP\n", lifeChangePlayer);
			break;
		case 4:
			printf("You try to heal yourself !");
			printf(" Player : ");
			if(lifeChangePlayer >= 0){
		    	printf("+%d HP", lifeChangePlayer);
		    } else if(lifeChangePlayer < 0){
		    	printf("%d HP", lifeChangePlayer);
		    }
		    printf("\n");
			break;
		case 5:
        	printf("You fail to escape ! The monster catchs up with you and attacks you !\n");
        	break;
        case 6:
        	printf("You don't have enough magic points to cast a spell.\n");
        	break;
        case 7:
        	printf("You start to focus and rise you hands...\n");
        	break;
        case 8:
        	printf("You lower your hands and let the magic go away.\n");
        	break;
        case 9:
        	printf("You cast a fireball ! ");
        	printf("Monster : %d HP\n", lifeChangeMonster);
        	break;
        case 10:
        	printf("You cast a shield to protect you.\n");
        	break;
        case 11:
			printf("You attack the monster !");
			printf(" Player : %d SP", lifeChangePlayer);
		    printf(" | Monster : %d HP\n", lifeChangeMonster);
			break;
		case 12:
			printf("You attack the monster ! \033[33mCritical hit !\033[0m");
			printf(" Player : %d SP", lifeChangePlayer);
		    printf(" | Monster : %d HP\n", lifeChangeMonster);
			break;
		case 13:
			printf("You attack the monster ! \033[31mYou miss !\033[0m");
			printf(" Player : %d SP\n", lifeChangePlayer);
			break;
		case 14:
			printf("You heal yourself !");
			printf(" Player : +%d HP | Player's shield : %d SP\n", lifeChangeMonster, lifeChangePlayer);
			break;
		default:
			printf("\n");
	}
}

/**
* @fn void display_monster_ascii(int nMonster)
* @brief Displays the ascci drawing of a monster.
* @param nMonster Reference to the drawing to display.
*/
void display_monster_ascii(int nMonster){
    switch(nMonster)
    {
    case 1:

        printf("  __\n");
        printf("<(o )___\n");
        printf(" ( ._> /\n");
        printf("  `---'\n");

        break;
    case 2:
printf("             \\                  /\n");
printf("    _________))                ((__________\n");
printf("   /.-------./\\\\    \\    /    //\\.--------.\\\n");
printf("  //#######//##\\\\   ))  ((   //##\\\\########\\\\\n");
printf(" //#######//###((  ((    ))  ))###\\\\########\\\\\n");
printf("((#######((#####\\\\  \\\\  //  //#####))########))\n");
printf(" \\##' `###\\######\\\\  \\)(/  //######/####' `##/\n");
printf("  )'    ``#)'  `##\\`->oo<-'/##'  `(#''     `(\n");
printf("          (       ``\\`..'/''       )\n");
printf("                     \\""(\n");
printf("                      `- )\n");
printf("                      / /\n");
printf("                     ( /\\\n");
printf("                     /\\| \\\n");
printf("                    (  \\\n");
printf("                        )\n");
printf("                       /\n");
printf("                      (\n");
printf("                      `\n");
        break;
    case 3:
printf("                .---.\n");
printf("              /       \\\n");
printf("---- _       |  O   O  |       _ ---\n");
printf("\\       ~-.  `.       .'  .-~      /\n");
printf(" \\          ~-_>     <_-~         /\n");
printf("   \\                             /\n");
printf("     \\                         /\n");
printf("       \\                     /\n");
printf("         \\                 /\n");
printf("           \\             /\n");
printf("             \\         /\n");
printf("               \\       \\\n");
printf("                 \\      \\\n");
printf("                   \\     \\\n");
printf("                     \\    \\\n");
printf("                       \\   l\n");
printf("                         \\ /\n");
printf("                          V\n");
        break;
    case 4:
printf("|@|@|@|@|           |@|@|@|@|\n");
printf("|@|@|@|@|   _____   |@|@|@|@|\n");
printf("|@|@|@|@| /\\_T_T_/\\ |@|@|@|@|\n");
printf("|@|@|@|@||/\\ T T /\\||@|@|@|@|\n");
printf(" ~/T~~T~||~\\/~T~\\/~||~T~~T\\~\n");
printf("  \\|__|_| \\(-(O)-)/ |_|__|/\\\n");
printf("  _| _|    \\\\8_8//    |_ |_\n");
printf("|(@)]   /~~[_____]~~\\   [(@)|\n");
printf("  ~    (  |       |  )    ~\n");
printf("      [~` ]       [ '~]\n");
printf("      |~~|         |~~|\n");
printf("      |  |         |  |\n");
printf("     _<\\/>_       _<\\/>_\n");
printf("    /_====_\\     /_====_\\\n");
        break;
    case 5:
printf("        \\\\            //           \\\\\n");
printf("        lo> <<       <o\\          <*l    //\n");
printf("        ll             \\\\          ll   <*l\n");
printf("        llama~         llama~  ^amall    ll\n");
printf("        || ||          \\ \\    || ||    llama~\n");
printf("        '' ''           '' ''   '' ''    // //\n");
printf("                                        '' ''\n");
        break;
    }

    printf("\n");

}