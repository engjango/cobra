/*************************************************************************
 * 
 * food.h
 * 
 * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
 * 
 * "Snake game written in C - animations, retro menu, smart snake 
 * enemies, sound effects."
 * 
 * last modification: 2021-01-07
 * 
 ************************************************************************/
 
#ifndef FOOD_H
#define FOOD_H

#include "map.h"

#define OBJECT_FOOD (char)'*'

/* Comida */
typedef struct tagFood {
	int x;	// Coordenada X de referência
	int y;	// Coordenada Y de referência
} Food;

void food_newposition(Food *food, Map *map);
void food_draw(Food *food);

#endif /* FOOD_H */
