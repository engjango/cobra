/*************************************************************************
 * 
 * texteffects.h
 * 
 * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
 * 
 * "Snake game written in C - animations, retro menu, smart snake 
 * enemies, sound effects."
 * 
 * last modification: 2021-01-07
 * 
 ************************************************************************/
 
#ifndef TEXTEFFECTS_H
#define TEXTEFFECTS_H

#include "map.h"

/*void texteffect_scrollH(char *text[], int refcol);*/
void texteffect_scrollHD(const int x, const int y, char *text,
	char direction, int txtcolor, int bkgcolor);
void texteffect_addchar(const int x, const int y, char *text,
	int txtcolor, int bkgcolor);
	
void texteffect_introanim();
void texteffect_countdownanim(Map *map);

void texteffect_bigscrollH(char *_str[], const int l, int _length);
char **converttexttoarray(char *path, int *n);

#endif /* TEXTEFFECTS_H */
