/*************************************************************************
 * 
 * menu.c
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
#include "uconio.h"
#include "texteffects.h"
#include "sound.h"
#include "menu.h"

/* Menu principal */
MENU mainmenu;
char *mainmenu_items[] = {
	"          Novo Jogo           ",
	"      Lista de Recordes       ",
	"         Configurar           ",
	"           Ajuda              ",
	"            Sair              "
};

/* Inicializa o menu segundo os parâmetros fornecidos */
void menu_initialize(MENU *menu, char *items[], int x, int y,
	int selected, int toprow, int nvisible, int nitems)
{
	int i;
	menu->x = x;
	menu->y = y;
	menu->selected	= selected;
	menu->toprow	= toprow;
	menu->nvisible	= nvisible;
	menu->nitems	= nitems;
	menu->items		= (char **)malloc(menu->nitems * sizeof(char *));
	for (i = 0; i < menu->nitems; i++) {menu->items[i] = items[i];}
}

/* Finaliza o menu corretamente */
void menu_terminate(MENU *menu)
{
	free(menu->items);
}

/* Imprime menu */
void menu_draw(MENU *menu, int req)
{
	int i;
	// Verifica requisição...
	switch(req)
	{
		case MENU_REQ_UP_ITEM:
			menu->selected--;
			if (menu->selected < 1)
			{
				menu->selected = menu->nitems;
				menu->toprow = menu->nitems - menu->nvisible + 1;
			}
			if (menu->selected < menu->toprow)
			{
				menu->toprow--;
			}
		break;
		
		case MENU_REQ_DOWN_ITEM:
			menu->selected++;
			if (menu->selected > menu->nitems)
			{
				menu->selected = 1;
				menu->toprow = 1;
			}
			if (menu->selected > menu->toprow + menu->nvisible - 1)
			{
				menu->toprow++;
			}
		break;
	}
	// Imprime menu...
	for (i = menu->toprow - 1; i < menu->toprow + menu->nvisible - 1; i++)
	{
		// Não é o item selecionado atualmente? Então..., senão...
		if (i != menu->selected - 1)
		{
			textattr(RESETATTR);
			textcolor(GREEN);
		}
		else
		{
			textattr(RESETATTR);
			textcolor(DARKGREY);
		}
		gotoxy(menu->x, menu->y + i - menu->toprow + 1);
		printf("%s", menu->items[i]);
	}
	
	// Imprime item atualmente selecionado e reproduz áudio correspondente
	audio_play(audio_mainchannel, AUDIO_TEFX_SLIDINGTOC, FALSE);
	texteffect_scrollHD(
		menu->x,
		menu->y + menu->selected - 1 - menu->toprow + 1, /* :o) -1 + 1 */
		menu->items[menu->selected - 1],
		0,
		YELLOW,
		BLUE
	);
	
	// Reconfigura atributos padrão de texto
	textattr(RESETATTR);
}

