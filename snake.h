/*************************************************************************
 * 
 * snake.h
 * 
 * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
 * 
 * "Snake game written in C - animations, retro menu, smart snake 
 * enemies, sound effects."
 * 
 * last modification: 2021-01-07
 * 
 ************************************************************************/
 
#ifndef SNAKE_H
#define SNAKE_H

/* Comprimento máximo permitido da cobrinha */
#define SNAKE_MAX_LENGTH 100

#include "map.h"
#include "food.h"

/* Modo de jogo da cobrinha */
typedef enum tagSnakeMode {
	SNAKE_MODE_NORMAL,
	SNAKE_MODE_ZOMBIE,
	SNAKE_MODE_IMORTAL,
} SnakeMode;

/* Padrão de cores da cobrinha */
typedef enum tagColorPattern {
	COLOR_PATTERN_AA,
	COLOR_PATTERN_BB,
	COLOR_PATTERN_AB,
	COLOR_PATTERN_AAB,
	COLOR_PATTERN_AAAB,
} ColorPattern;

/* Direções permitidas de movimento */
typedef enum tagDirection {
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_RIGHT,
	DIRECTION_LEFT
} Direction;

/* Cobrinha */
typedef struct tagSnake {
	int x;	// Coordenada X de referência
	int y;	// Coordenada Y de referência
	Coord body[SNAKE_MAX_LENGTH]; 
	int speed;	
	int length; 
	Direction dir;
	SnakeMode mode;
	int colorA; // cor primária
	int colorB; // cor secundária
	ColorPattern colorptrn; // padrão de cores
	int lifes;
	int score;
} Snake;

int snake_move(Snake *snake, Direction dir, Map *map);
int snake_movexy(Snake *snake, Coord newpos, Map *map);
void snake_draw(Snake *snake);
int snake_collide_self(Snake *snake);
int snake_collide_object(Snake *snake, Map *map);
int snake_collide_food(Snake *snake, Food *food);

#endif /* SNAKE_H */
