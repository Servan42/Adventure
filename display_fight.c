#include <stdio.h>
#include <stdlib.h>
#include "display_fight.h"

#define HEALTH_BAR_PLAYER 1
#define XP_BAR 2

void display_header(pplayer P){
	printf("--------------------------------------------------\n");
	printf("\033[1m%s\033[0m | ",P->playerName);
	printf("Niveau : \033[96m%d\033[0m\n", P->lvl);
	printf("Vie : %d/%d HP\n",P->hp,P->hpMax);
	display_bar_player(P, HEALTH_BAR_PLAYER); printf("\n");
	printf("Experience : %0.0lf/%0.0lf XP\n",P->xp,P->xpStage);
	display_bar_player(P, XP_BAR); printf("\n");
	printf("--------------------------------------------------\n\n");
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

			for(i = 0; i < ((P->hp*100)/P->hpMax)/5; i++){
				printf("*");
			}
			printf("\033[0m");
			for(i = 0; i < 20-((P->hp*100)/P->hpMax)/5; i++){
				printf(" ");
			}
			printf("]");
			break;
		case XP_BAR:
			printf("[\033[8m\033[46m");
			for(i = 0; i < ((P->xp*100)/P->xpStage)/5; i++){
				printf("*");
			}
			printf("\033[0m");
			for(i = 0; i < 20-((P->xp*100)/P->xpStage)/5; i++){
				printf(" ");
			}
			printf("]");
			break;
	}
}

void display_bar_monster(pmonster M){
	int i;
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
}

void display_monster(int nMonster){
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