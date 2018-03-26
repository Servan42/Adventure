#include <stdio.h>
#include <stdlib.h>
#include "display_fight.h"

#define HEALTH_BAR_PLAYER 1
#define XP_BAR 2

void display_header(pplayer P, int lifeChangePlayer){
	printf("--------------------------------------------------\n\n");
	printf("\033[1m%s\033[0m | ",P->playerName);
	printf("Niveau : \033[96m%d\033[0m\n", P->lvl);
	printf("Vie : %d/%d HP\n",P->hp,P->hpMax);
	
	display_bar_player(P, HEALTH_BAR_PLAYER);
	if(lifeChangePlayer > 0){
    	printf("\033[32m +%d\033[0m HP\n", lifeChangePlayer);
    } else if(lifeChangePlayer < 0){
    	printf("\033[31m %d\033[0m HP\n", lifeChangePlayer);
    } else {
    	printf("\n");
    }

	printf("Experience : %0.0lf/%0.0lf XP\n",P->xp,P->xpStage);
	display_bar_player(P, XP_BAR); printf("\n");
	printf("\n--------------------------------------------------\n\n");
}

void display_monster(pmonster M, pplayer P, int lifeChangeMonster){
	display_monster_ascii(M->ascii);
	printf("\n");
    
    if((P->lvl + 1) == M->lvl){
        printf("\nNiveau : \033[33m%d\033[0m\n",M->lvl);
	} else if(P->lvl < M->lvl){
        printf("\nNiveau : \033[31m%d\033[0m\n",M->lvl);
    } else if(P->lvl == M->lvl){
        printf("\nNiveau : \033[32m%d\033[0m\n",M->lvl);
	} else {
        printf("\nNiveau : %d\n",M->lvl);
    }
	
	printf("Vie : %d/%d HP\n", M->hp, M->hpMax);
	
	display_bar_monster(M);
    if(lifeChangeMonster > 0){
    	printf("\033[32m +%d\033[0m HP\n", lifeChangeMonster);
    } else if(lifeChangeMonster < 0){
    	printf("\033[31m %d\033[0m HP\n", lifeChangeMonster);
    } else {
    	printf("\n");
    }


	printf("\n");
	printf("--------------------------------------------------\n");
}

double my_round(double a){
	int b = a - floor(a);
	if(b == 0.5) return floor(a);
	else return round(a);
}

void display_bar_player(pplayer P, int bar){
	int i;
	switch(bar){
		case HEALTH_BAR_PLAYER:
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
			printf("[\033[8m\033[46m");
			for(i = 0; i < round(((P->xp*100)/P->xpStage)/5); i++){
				printf("*");
			}
			printf("\033[0m");
			for(i = 0; i < my_round(20-((P->xp*100)/P->xpStage)/5); i++){
				printf(" ");
			}
			printf("]");
			break;
	}
}

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

void display_appears(){
	printf("\t***************************\n");
	printf("\t*                         *\n");
	printf("\t*  UN MONSTRE APPARAIT !  *\n");
	printf("\t*                         *\n");
	printf("\t***************************\n");
	printf("\n--------------------------------------------------\n");

}

void display_you_lose(){
	printf("\t***************************\n");
	printf("\t*                         *\n");
	printf("\t*        YOU LOSE !       *\n");
	printf("\t*                         *\n");
	printf("\t***************************\n");
	printf("\n--------------------------------------------------\n");

}

void display_run(){
	printf("\t***************************\n");
	printf("\t*                         *\n");
	printf("\t* VOUS PRENEZ LA FUITE !  *\n");
	printf("\t*                         *\n");
	printf("\t***************************\n");
	printf("\n--------------------------------------------------\n");

}

void display_victory(int lvlEarned, int xpEarned){
	printf("\t***************************\n");
	printf("\t*                         *\n");
	printf("\t*        YOU WIN !        *\n");
	printf("\t*                         *\n");
	printf("\t***************************\n");
	printf("\n");
	printf("\033[36m");
	printf("Vous gagnez %d points d'experience.\n", xpEarned);
	if(lvlEarned != 0){
		if(lvlEarned == 1) printf("Vous gagnez %d niveau !\n", lvlEarned);
		else printf("Vous gagnez %d niveaux !\n", lvlEarned);
	}
	printf("\033[0m\n");
	printf("--------------------------------------------------\n");

}


void display_text(int text_id){
	printf("\n");
	switch(text_id){
		case 0:
			printf("Un monstre apparait !\n");
			break;
		case 1:
			printf("Vous attaquez !\n");
			break;
		case 2:
			printf("Vous attaquez ! \033[33mCoup Critique !\033[0m\n");
			break;
		case 3:
			printf("Vous attaquez ! \033[31mEchec critique !\033[0m\n");
			break;
		case 4:
			printf("Vous vous soignez !\n");
			break;
		case 5:
        	printf("La fuite a echouee ! Le monstre vous rattrape et vous attaque !\n");
        	break;
		default:
			printf("\n");
	}
	printf("\n--------------------------------------------------\n");

}

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