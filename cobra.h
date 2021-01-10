/*************************************************************************
 * 
 * cobra.h
 * 
 * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
 * 
 * "Snake game written in C - animations, retro menu, smart snake 
 * enemies, sound effects."
 * 
 * last modification: 2021-01-07
 * 
 ************************************************************************/
 
#ifndef COBRA_H
#define COBRA_H

#include "snake.h"
#include "food.h"

/* Estrutura Geral do Jogo */
typedef struct tagCobra {
	Snake snake;
	Snake snakeA;
	Food food;
} COBRA;

extern COBRA maincobra;

void cobra_initialize(COBRA *cobra);
void cobra_terminate(COBRA *cobra);
void cobra_run(COBRA *cobra);

#endif /* COBRA_H */
