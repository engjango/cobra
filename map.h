/*************************************************************************
 * 
 * map.h
 * 
 * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
 * 
 * "Snake game written in C - animations, retro menu, smart snake 
 * enemies, sound effects."
 * 
 * last modification: 2021-01-07
 * 
 ************************************************************************/
 
#ifndef MAP_H
#define MAP_H

// Linha/Coluna de referência para impressão
#define MAP_X	2
#define MAP_Y	4

// Número de linhas e colunas do mapa
#define MAP_COLUMNS	78
#define MAP_ROWS	20

// Identificação simbólica dos items contidos no en
//#define OBJECT_ORIGIN		(char)'O'
#define OBJECT_BLANK		(char)' '
#define OBJECT_OBSTACLE		(char)'#'
//#define OBJECT_WORMHOLE		(char)'W'

#define SIMPLE_MAP_FLOOR 0
#define SIMPLE_MAP_WALL  1
#define SIMPLE_MAP_ROUTE 2 // We use this to mark the route on the map.
#define SIMPLE_MAP_START 3
#define SIMPLE_MAP_END   4

/* Tipos de dados para representação de coordenadas cartesianas 
 * (0,0) (1,0) (2,0) ... (c,0)
 * (0,1) (1,1) (2,1) ... (c,1)
 * (0,2) (1,2) (2,2) ... (c,2)
 *  ...   ...   ...  ...  ...
 * (0,l) (1,l) (2,l) ... (c,l) */
typedef struct tagCoordinates {
	int x; // Coordenada no eixo x (→): 0 até "número máximo de colunas"
	int y; // Coordenada no eixo y (↓): 0 até "númeo máximo de linhas"
} Coord;

/* Mapa */
typedef struct tagMap {
	int x;	// Coordenada X de referência
	int y;	// Coordenada Y de referência
	char grid[MAP_ROWS][MAP_COLUMNS];
} Map;

extern Map mainmap;

void map_drawobject(int x, int y, Map *map);
void map_draw(Map *map);
void map_loadfromfile(Map *map, const int x, const int y, const char *filename);
void map_drawinfo(const int lifes, const int score);
Coord map_findaway(const int x0, const int y0, const int x1, const int y1);

#endif /* MAP_H */
