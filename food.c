/*************************************************************************
 * 
 * food.c
 * 
 * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
 * 
 * "Snake game written in C - animations, retro menu, smart snake 
 * enemies, sound effects."
 * 
 * last modification: 2021-01-07
 * 
 ************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "uconio.h"
#include "map.h"
#include "snake.h"
#include "food.h"

/* Define uma nova posição no grid para o objeto de coleta 
 * 
 * Defeito: atualmente a nova posição da comida é qualquer uma
 * das posições limpas do GRID, as quais também podem "incluir
 * a atual posição das cobrinhas". */
void food_newposition(Food *food, Map *map)
{
	int hasfounded = 0;	
	do
	{
		srand(time(NULL));
		food->x = (rand() % MAP_COLUMNS) + map->x;
		food->y = (rand() % MAP_ROWS) + map->y;		
		if (map->grid[food->y - map->y][food->x - map->x] == OBJECT_BLANK)
			{
				hasfounded = 1;
			}
		
	} while (!hasfounded);
}

/* Imprime objeto de coleta */
void food_draw(Food *food)
{
	textbackground(BLACK);textcolor(YELLOW);
	gotoxy(food->x, food->y);
	printf("%c", OBJECT_FOOD);
}

