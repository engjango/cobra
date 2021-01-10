/*************************************************************************
 * 
 * map.c
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
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <libastar/astar.h>
#include "uconio.h"
#include "snake.h"
#include "map.h"

/* Grid da seção de jogo atual */
Map mainmap;

/* Grid simplificado da seção do jogo atual */
uint8_t simplemap[MAP_COLUMNS * MAP_ROWS];

#define set_simplemap(x, y, val) simplemap[(y) * MAP_COLUMNS + (x)] = (val)
#define get_simplemap(x, y) simplemap[(y) * MAP_COLUMNS + (x)]

uint8_t get_simplemap_cost(const uint32_t x, const uint32_t y)
{
	return(get_simplemap(x, y) == SIMPLE_MAP_WALL ? COST_BLOCKED : 1);
}

/* Desenha apenas "UM" objeto do cenário, segundo os parâmetros */
void map_drawobject(int x, int y, Map *map)
{
	// move cursor para posição do objeto
	gotoxy(x + map->x, y + map->y);
	// desenha objeto
	switch(map->grid[y][x])
			{
				// Desenha texto exibido no mapa
				case 'a' ... 'z':
					textbackground(BLACK);
					textcolor(WHITE);
					printf("%c", map->grid[y][x]);
				break;				
				case 'A' ... 'Z':
					textbackground(BLACK);
					textcolor(WHITE);
					printf("%c", map->grid[y][x]);
				break;
				
				// Desenha espaço vazio
				case OBJECT_BLANK: 
					textbackground(BLACK); 
					textcolor(BLUE); 
					puts(" "); 
				break;
				
				// Desenha obstáculo
				case OBJECT_OBSTACLE: 
					textbackground(RED); 
					puts(" "); 
				break;
				
				default:
					textbackground(BLACK);
					textcolor(BLUE);
					printf("%c", map->grid[y][x]);
				break;
			}
}

/* Desenha mapa fornecido como parâmetro */
void map_draw(Map *map)
{
	int i, j; // variáveis auxiliáres
	textattr(RESETATTR); // redefine atributos de texto
	for (i = 0; i < MAP_ROWS; i++)
	{
		for (j = 0; j < MAP_COLUMNS; j++)
		{			
			map_drawobject(j, i, map);
		}
	}
	textattr(RESETATTR); // redefine atributos de texto
}

/* Carrega mapa a partir de um arquivo dado */
void map_loadfromfile(Map *map, const int x, const int y, const char *filename)
{
	int i, j; // variáveis auxiliares
	FILE *mapfile;	
	
	// Limpa mapa simples
	for (i = 0; i < MAP_ROWS * MAP_COLUMNS; i++)
	{
		simplemap[i] = SIMPLE_MAP_FLOOR;
	}
	
	// Define mapa de acordo com o arquivo correspondente
	mapfile = fopen(filename, "r");
	
	// configura a posição inicial de referência
	map->x = x;
	map->y = y;
	
	// configura o mapa correspondente
	for (i = 0; i < MAP_ROWS; i++)
	{
		for (j = 0; j < MAP_COLUMNS; j++)
		{
			// adiciona os objetos ao picadeiro, inclusive espaço vazio			
			//screen->grid[i][j] = map_default[i][j];
			fscanf(mapfile, "%c", &map->grid[i][j]);
			
			if (map->grid[i][j] == OBJECT_OBSTACLE)
			{
				set_simplemap(j, i, SIMPLE_MAP_WALL);
				//set_simplemap(j + 1, i, SIMPLE_MAP_WALL);
			}
		}
	}
	
	// fecha arquivo de mapa
	fclose(mapfile);
}

/* Exibe informações acerca da seção de jogo atual */
void map_drawinfo(const int lifes, const int score)
{
	textbackground(RED); textcolor(WHITE);
	gotoxy(4, 4);
	printf("Vidas: %d\tPontos: %d" , lifes, score);
	textattr(RESETATTR);
}


Coord map_findaway(const int x0, const int y0, const int x1, 
	const int y1)
{
	astar_t *as;
	//int x, y;
	int result;
	Coord tmp;
	
	as = astar_new(MAP_COLUMNS, MAP_ROWS, get_simplemap_cost, NULL);
	
	astar_set_origin(as, 0, 0);
	
	//astar_set_movement_mode(as, DIR_8WAY);
	astar_set_movement_mode(as, DIR_CARDINAL);
	
	result = astar_run(as, x0, y0, x1, y1);	
	
	gotoxy(1, 23);textbackground(RED);textcolor(YELLOW);
	//printf("[ASTAR] Resultado: %s (%d)\n", as->str_result, result);
	textattr(RESETATTR);
	
	if (result == ASTAR_TRIVIAL) {
		tmp.x = -1;//x1 + MAP_X;
		tmp.y = -1;//y1 + MAP_Y;
		return(tmp);
	}
	
	if (astar_have_route(as))
	{
		direction_t * directions, * dir;
		uint32_t i, num_steps;
		int x, y;

		num_steps = astar_get_directions (as, &directions);		
		
		// The directions start at our (x0, y0) and give us
		// step-by-step directions (e.g. N, E, NE, N) to
		// either our (x1, y1) in the case of a full route, or
		// the best compromise.
		x = x0;
		y = y0;
		dir = directions;
		
		for (i = 0; i < num_steps; i++, dir++) {

			// Convince ourselves that A* never made us go through walls.
			assert (get_simplemap (x, y) != SIMPLE_MAP_WALL);
			
			// Mark the route on the map.
			set_simplemap (x, y, SIMPLE_MAP_ROUTE);

			// Get the next (x, y) co-ordinates of the map.
			x += astar_get_dx (as, *dir);
			y += astar_get_dy (as, *dir);
			
			break;
			
		}
		
		tmp.x = x + MAP_X;
		tmp.y = y + MAP_Y;

		// Mark the starting and ending squares on the map. Do this last.
		set_simplemap (x0, y0, SIMPLE_MAP_START);
		set_simplemap (x1, y1, SIMPLE_MAP_END);

		// VERY IMPORTANT: MEMORY LEAKS OTHERWISE!
		astar_free_directions (directions);
	}
	return(tmp);
}
