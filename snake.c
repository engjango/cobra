/*************************************************************************
 * 
 * snake.c
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
#include <stdint.h>
#include "uconio.h"
#include "map.h"
#include "food.h"
#include "snake.h"

/* Movimenta a cobrinha em um passo de acordo com a nova direção */
int snake_move(Snake *snake, Direction dir, Map *map)
{
	int i; // variável auxiliar	
	
	// verifica qual a nova direção
	switch(dir) {
		case DIRECTION_UP: // movimenta a cobrinha um passo para cima
			if (snake->dir != DIRECTION_DOWN) // impede que a cobrinha colapse sob si mesma
			{
				snake->body[snake->length].x = snake->body[snake->length-1].x;
				snake->body[snake->length].y = snake->body[snake->length-1].y - 1;
				snake->dir = DIRECTION_UP;
			} else {return(1);}
		break;
		
		case DIRECTION_DOWN: // movimenta a cobrinha um passo para baixo
			if (snake->dir != DIRECTION_UP) // impede que a cobrinha colapse sob si mesma
			{		
				snake->body[snake->length].x = snake->body[snake->length-1].x;
				snake->body[snake->length].y = snake->body[snake->length-1].y + 1;
				snake->dir = DIRECTION_DOWN;
			} else {return(1);}
		break;
		
		case DIRECTION_RIGHT: // movimenta a cobrinha um passo à direita
			if (snake->dir != DIRECTION_LEFT) // impede que a cobrinha colapse sob si mesma
			{		
				snake->body[snake->length].x = snake->body[snake->length-1].x + 1;
				snake->body[snake->length].y = snake->body[snake->length-1].y;
				snake->dir = DIRECTION_RIGHT;
			} else {return(1);}
		break;
		
		case DIRECTION_LEFT: // movimenta a cobrinha um passo à esquerda
			if (snake->dir != DIRECTION_RIGHT) // impede que a cobrinha colapse sob si mesma
			{		
				snake->body[snake->length].x = snake->body[snake->length-1].x - 1;
				snake->body[snake->length].y = snake->body[snake->length-1].y;
				snake->dir = DIRECTION_LEFT;
			} else {return(1);}
		break;
	}
	
	// insere caractere ESPAÇO no final da cobrinha para apagar o rastro
	textattr(RESETATTR); // redefine atributos do texto
	//gotoxy(snake->body[0].x, snake->body[0].y);
	//puts("-");
	map_drawobject(snake->body[0].x - map->x, snake->body[0].y - map->y, map);
	
	// atualiza as coordenadas de cada um dos segmentos da cobrinha	
	for (i = 1; i <= snake->length; i++)
	{				
		snake->body[i-1] = snake->body[i];
	}
	
	return(0);
}

/* Movimenta a cobrinha para uma nova posição (x, y) */
int snake_movexy(Snake *snake, Coord newpos, Map *map)
{
	int i; // variável auxiliar	
	
	// verifica qual a nova direção
	snake->body[snake->length].x = newpos.x;
	snake->body[snake->length].y = newpos.y;
	
	// ...
	
	// insere caractere ESPAÇO no final da cobrinha para apagar o rastro
	textattr(RESETATTR); // redefine atributos do texto
	//gotoxy(snake->body[0].x, snake->body[0].y);
	//puts("-");
	map_drawobject(snake->body[0].x - map->x, snake->body[0].y - map->y, map);
	
	// atualiza as coordenadas de cada um dos segmentos da cobrinha	
	for (i = 1; i <= snake->length; i++)
	{				
		snake->body[i-1] = snake->body[i];
	}
	
	return(0);
}

/* Imprime a cobrinha segundo suas características */
void snake_draw(Snake *snake)
{
	int i; // variável auxiliar
	textbackground(BLACK); // altera cor do plano de fundo do texto			
	for (i = 0; i < snake->length; i++)
	{		
		// define cor do segmento segundo padrão de cores pré-definido
		switch(snake->colorptrn)
		{
			case COLOR_PATTERN_AA:
				if (i != snake->length - 1) // padrão: XOOOOOOOOO
				{		
					if (snake->mode == SNAKE_MODE_NORMAL) 
					{
						textcolor(snake->colorA);
					} else if (snake->mode == SNAKE_MODE_ZOMBIE)
					{
						textcolor(LIGHTGREY);
					}			
				} else {
					if (snake->mode == SNAKE_MODE_NORMAL) 
					{
						textcolor(snake->colorB);
					} else if (snake->mode == SNAKE_MODE_ZOMBIE)
					{
						textcolor(DARKGREY);
					}
				}				
			break;
			
			case COLOR_PATTERN_BB:
				if (i != snake->length - 1) // padrão: X000000000
				{		
					if (snake->mode == SNAKE_MODE_NORMAL) 
					{
						textcolor(snake->colorB);
					} else if (snake->mode == SNAKE_MODE_ZOMBIE)
					{
						textcolor(DARKGREY);
					}			
				} else {
					if (snake->mode == SNAKE_MODE_NORMAL) 
					{
						textcolor(snake->colorA);
					} else if (snake->mode == SNAKE_MODE_ZOMBIE)
					{
						textcolor(LIGHTGREY);
					}
				}		
			break;
			
			case COLOR_PATTERN_AB:
				if (i % 2 == 0) // padrão: XO0O0O0O0O
				{		
					if (snake->mode == SNAKE_MODE_NORMAL) 
					{
						textcolor(snake->colorA);
					} else if (snake->mode == SNAKE_MODE_ZOMBIE)
					{
						textcolor(LIGHTGREY);
					}			
				} else {
					if (snake->mode == SNAKE_MODE_NORMAL) 
					{
						textcolor(snake->colorB);
					} else if (snake->mode == SNAKE_MODE_ZOMBIE)
					{
						textcolor(DARKGREY);
					}
				}		
			break;
			
			case COLOR_PATTERN_AAB:
				if (i % 3 == 0 || i % 6 == 0) // padrão: XOO0OO0OO0
				{		
					if (snake->mode == SNAKE_MODE_NORMAL) 
					{
						textcolor(snake->colorB);
					} else if (snake->mode == SNAKE_MODE_ZOMBIE)
					{
						textcolor(LIGHTGREY);
					}			
				} else {
					if (snake->mode == SNAKE_MODE_NORMAL) 
					{
						textcolor(snake->colorA);
					} else if (snake->mode == SNAKE_MODE_ZOMBIE)
					{
						textcolor(DARKGREY);
					}
				}
			break;
			
			case COLOR_PATTERN_AAAB:
				if (i != snake->length - 1 && i != 0) // padrão: XOOOOOOOO0
				{		
					if (snake->mode == SNAKE_MODE_NORMAL) 
					{
						textcolor(snake->colorA);
					} else if (snake->mode == SNAKE_MODE_ZOMBIE)
					{
						textcolor(LIGHTGREY);
					}			
				} else {
					if (snake->mode == SNAKE_MODE_NORMAL) 
					{
						textcolor(snake->colorB);
					} else if (snake->mode == SNAKE_MODE_ZOMBIE)
					{
						textcolor(DARKGREY);
					}
				}
			break;
			
			default:
				/* NOP */
			break;
		}		
		// imprime segmento da cobrinha
		gotoxy(snake->body[i].x, snake->body[i].y);
		if(i != snake->length-1) {puts("O");} else {puts("X");}		
		/* CORREÇÃO DE BUG */
		gotoxy(0, 0);
	}	
	textattr(RESETATTR); // redefine atributos do texto	
}

/* Cobrinha colidiu consigo mesma */
int snake_collide_self(Snake *snake)
{
	int i; // variável auxiliar
	Coord snake_head_pos = snake->body[snake->length-1]; // posição da cabeça da cobrinha
	for (i = 0; i < snake->length-1; i++) // ...para cada segmento da cobrinha faz...
	{
		Coord snake_seg_pos = snake->body[i]; // coordenada do segmento atual
		// verifica se a posição da cabeça é a mesma posição do segmento 
		// atual, uma vez que sim, então houve colisão.
		if (snake_head_pos.x == snake_seg_pos.x 
		&&  snake_head_pos.y == snake_seg_pos.y)
		{			
			snake->mode = snake->mode == SNAKE_MODE_ZOMBIE ? SNAKE_MODE_NORMAL : SNAKE_MODE_ZOMBIE;
			
			return(1); // houve colisão
		}
	}
	return(0); // não houve colisão
}

/* Cobrinha colide com objeto. Uma vez que houve colisão,
 * retorna o valor correspondente ao objeto com o qual houve colisão,
 * do contrário, retorna 0 */
int snake_collide_object(Snake *snake, Map *map)
{
	int i, j; // variável auxiliar
	Coord snake_head_pos = snake->body[snake->length-1]; // posição da cabeça da cobrinha
	
	// para cada item do grid[x,y]
	for (i = 0; i < MAP_ROWS; i++)
	{
		for (j = 0; j < MAP_COLUMNS; j++)
		{						
			if (map->grid[i][j] != OBJECT_BLANK) // se objeto não é objeto vazio
			{
				// se cobrinha colidiu com tal objeto
				if (snake_head_pos.x == j + map->x 
				&&  snake_head_pos.y == i + map->y)
				{			
					return(map->grid[i][j]); // retorna a colisão
				}				
			}
		}
	}
	return(0); // não houve colisão
}

/* 
 * Cobrinha colide com objeto de coleta. 
 * '*' → incrementa 1 segmento em seu corpo
 *
 * */
int snake_collide_food(Snake *snake, Food *food)
{
	
	int i; // variável auxiliar
	for (i = 0; i < snake->length-1; i++) // ...para cada segmento da cobrinha faz...
	{
		Coord snake_seg_pos = snake->body[i]; // coordenada do segmento atual
		// verifica se a posição da cabeça é a mesma posição do segmento 
		// atual, uma vez que sim, então houve colisão.
		if (food->x == snake_seg_pos.x 
		&&  food->y == snake_seg_pos.y)
		{						
			return(OBJECT_FOOD); // houve colisão
		}
	}
	return(0); // não houve colisão
}
