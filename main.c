/*************************************************************************
 * 
 * main.c
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
#include <locale.h>
#include "uconio.h"
#include "texteffects.h"
#include "sound.h"
#include "bass.h"
#include "menu.h"
#include "map.h"
#include "cobra.h"

int main(void)
{
	// Finalizar jogo?
	int GAME_QUIT = 0;
	
	// Tecla pressionada
	KEY Keypressed;
	
	// Omite o cursor de posição do terminal
	hidecursor();
	
	// Limpa a tela do terminal
	system("clear");
	
	// Configura para o idioma local
	setlocale(LC_ALL, NULL);
	
	// Inicializa o módulo de áudio
	switch(audio_initialize())
	{
		case BASS_OK:
			puts("[ÁUDIO]: Ok.");
		break;
		
		case BASS_ERROR_VERSION:
			puts("[ÁUDIO]: Versão de biblioteca BASS inválida.");
		break;
		
		case BASS_ERROR_INIT:
			puts("[ÁUDIO]: Erro ao tentar inicializar a biblioteca BASS.");
		break;
		
		default:
			puts("[ÁUDIO]: Houve um erro desconhecido.");
		break;
	}
	
	// Limpa a tela do terminal
	system("clear");
	
	// Exibe animação de introdução
	texteffect_introanim();
	
	// Configura mapa do menu principal
	map_loadfromfile(&mainmap, MAP_X, MAP_Y, "maps/mainmenu.ans");
	map_draw(&mainmap);
	
	// Configura e imprime (1ª vez) o menu principal e reproduz áudio correspondente
	audio_play(audio_mainchannel, AUDIO_MENU_MAIN, TRUE);
	menu_initialize(&mainmenu, mainmenu_items, 25, 15, 1, 1, 5, 5);
	menu_draw(&mainmenu, 0);	
	
	// Loop do menu principal
	while(!GAME_QUIT)
	{
		// Captura tecla pressionada, havendo-a
		Keypressed = getkeypressed();
		
		// Pressionou: SETA DIRECIONAL
		if (Keypressed.x == 27 && Keypressed.y == 91)
		{
			switch(Keypressed.z)
			{
				// Tecla: SETA ACIMA
				case 65: menu_draw(&mainmenu, MENU_REQ_UP_ITEM); break;
				
				// Tecla: SETA ABAIXO
				case 66: menu_draw(&mainmenu, MENU_REQ_DOWN_ITEM); break;
			}
		}
		
		// Tecla: ENTER
		if (Keypressed.x == 10)
		{
			switch(mainmenu.selected)
			{
				// Opção: Novo Jogo
				case 1:
					cobra_initialize(&maincobra);
					cobra_run(&maincobra);
					cobra_terminate(&maincobra);
				break;
				
				// Opção: Lista de Recordes
				case 2:
					/* A FAZER */
				break;
				
				// Opção: Configurar
				case 3:
					/* A FAZER */
				break;
				
				// Opção: Ajuda
				case 4:
					/* A FAZER */
				break;
				
				// Opção: Sair
				case 5:
					GAME_QUIT = 1;
				break;
				
				
			}
		}
	}
	
	// Finaliza corretamente o menu principal
	menu_terminate(&mainmenu);
	
	// Finaliza corretamente o módulo de áudio
	audio_terminate();
	
	// Limpa a tela do terminal
	system("clear");
	
	// Finaliza corretamente a aplicação
	return(EXIT_SUCCESS);
}
