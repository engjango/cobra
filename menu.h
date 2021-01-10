/*************************************************************************
 * 
 * menu.h
 * 
 * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
 * 
 * "Snake game written in C - animations, retro menu, smart snake 
 * enemies, sound effects."
 * 
 * last modification: 2021-01-07
 * 
 ************************************************************************/
 
#ifndef MENU_H
#define MENU_H

/* Requisições de navegação aceitas pelo menu */
#define MENU_REQ_UP_ITEM	1 // Seleciona o item acima
#define MENU_REQ_DOWN_ITEM	2 // Seleciona o item abaixo

/* Definição do menu como estrutura */
typedef struct tagMenu {
	int x;			// Linha X de referência para impressão do menu
	int y;			// Coluna Y de referência para impressão do menu
	int selected;	// Indentificação do item atualmente selecionado
	int toprow;		// Identificação do item no topo da lista a ser exibido
	int nvisible;	// Número de items visíveis no menu
	int nitems;		// Número total de items do menu
	char **items;	// Items do menu
} MENU;

extern MENU mainmenu;
extern char *mainmenu_items[];

void menu_initialize(MENU *menu, char *items[], int x, int y,
	int selected, int toprow, int nvisible, int nitems);
void menu_terminate(MENU *menu);
void menu_draw(MENU *menu, int req);

#endif /* MENU_H */
