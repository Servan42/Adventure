/*
* @author CHARLOT Servan
*/

#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <math.h>

/**
* @struct _player global.h player
* @brief Player attributes.
*/
typedef struct _player {
	int hp; /*!< Current health points */
	unsigned int hpMax; /*!< Maximum health points */
	unsigned int lvl; /*!< Level */
	double xpTotal; /*!< Total of experience earned from the beginning */
	double xp; /*!< Experience in the current level */
	double xpStage; /*!< Experience value tu reach in order to level up */
	char playerName[100]; /*!< Name of the player */
	} player, *pplayer;

/**
* @def CC
* @brief Over this percentage, perform a critical hit.
*/
#define CC 95

/**
* @def EC
* @brief Under this percentage, miss the attack.
*/
#define EC 5

/**
* @def FUITE
* @brief Under this percentage, the player fails to run away.
*/
#define FUITE 25

#endif