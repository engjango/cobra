/*************************************************************************
 * 
 * cobra.c
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
#include "texteffects.h"
#include "food.h"
#include "snake.h"
#include "sound.h"
#include "cobra.h"

/* Partida do jogo */
COBRA maincobra;

/* Inicializa uma partida de jogo */
void cobra_initialize(COBRA *cobra)
{
	int i; // variável auxiliar
	
	// Inicializa cobrinha principal	
	cobra->snake.speed = 30;
	cobra->snake.dir = DIRECTION_DOWN;
	cobra->snake.mode = SNAKE_MODE_NORMAL;
	cobra->snake.colorA = LIGHTRED;
	cobra->snake.colorB = LIGHTBLUE;
	cobra->snake.colorptrn = COLOR_PATTERN_AAB;
	cobra->snake.x = 24;
	cobra->snake.y = 7;
	cobra->snake.length = 3;
	cobra->snake.lifes = 4;
	cobra->snake.score = 0;
	
	// Inicia a cobrinha concorrente
	cobra->snakeA.speed = 30;
	cobra->snakeA.dir = DIRECTION_DOWN;
	cobra->snakeA.mode = SNAKE_MODE_NORMAL;
	cobra->snakeA.colorA = LIGHTMAGENTA;
	cobra->snakeA.colorB = BLUE;
	cobra->snakeA.colorptrn = COLOR_PATTERN_AB;
	cobra->snakeA.x = 28;
	cobra->snakeA.y = 7;
	cobra->snakeA.length = 3;
	cobra->snakeA.lifes = 4;
	cobra->snakeA.score = 0;
	
	// "Reseta" as coordenadas de ambas as cobrinhas
	for (i = 0; i <= cobra->snake.length; i++)
	{
		cobra->snake.body[i].x = cobra->snake.x;
		cobra->snake.body[i].y = cobra->snake.y;
		cobra->snakeA.body[i].x = cobra->snakeA.x;
		cobra->snakeA.body[i].y = cobra->snakeA.y;
	}
}

/* Finaliza uma partida de jogo */
void cobra_terminate(COBRA *cobra)
{
	free(&cobra->snake);
	free(&cobra->snakeA);
	free(&cobra->food);
}

/* Roda o jogo */
void cobra_run(COBRA *cobra)
{
	int i; // variável auxiliar
	int blink = 0;
	
	Coord newpos; // novas posições
	
	// Retornar ao menu principal do jogo? 
	int GAME_BACKTOMAINMENU = 0;
	
	// Tecla pressionada
	KEY Keypressed;
	
	// Variáveis utilizada para controlar a velocidade do jogo
	clock_t clock_endwait;
	int clock_waitmili = CLOCKS_PER_SEC - (9) * (CLOCKS_PER_SEC / 10);
	
	// Configura e imprime mapa 1
	map_loadfromfile(&mainmap, MAP_X, MAP_Y, "maps/map1.ans");
	map_draw(&mainmap);
	
	// Inicia áudio do mapa
	audio_stop(); audio_resume();
	audio_play(audio_mainchannel, AUDIO_MAP1, TRUE);
					
	// Inicia animação de contagem regressiva
	texteffect_countdownanim(&mainmap);
	
	// Define uma nova posição para o objeto de coleta
	food_newposition(&cobra->food, &mainmap);
					
	// Inicia clock de controle de velocidade do loop
	clock_endwait = clock() + clock_waitmili;
					
	// Loop principal da seção de jogo
	while(!GAME_BACKTOMAINMENU)
	{
		// Captura a	 tecla pressionda, havendo-a
		if (kbhit())
		{
			Keypressed = getkeypressed();
		}
						
		// Pressionou: SETA DIRECIONAL
		if (Keypressed.x == 27 && Keypressed.y == 91)
		{
			switch(Keypressed.z)
			{
				// Tecla: ACIMA
				case 65: cobra->snake.dir = (cobra->snake.dir != DIRECTION_DOWN) ? DIRECTION_UP : DIRECTION_DOWN; break;
						
				// Tecla: ABAIXO
				case 66: cobra->snake.dir = (cobra->snake.dir != DIRECTION_UP) ? DIRECTION_DOWN : DIRECTION_UP; break;
								
				// Tecla: DIREITA
				case 67: cobra->snake.dir = (cobra->snake.dir != DIRECTION_LEFT) ? DIRECTION_RIGHT : DIRECTION_LEFT; break;
						
				// Tecla: ESQUERDA
				case 68: cobra->snake.dir = (cobra->snake.dir != DIRECTION_RIGHT) ? DIRECTION_LEFT : DIRECTION_RIGHT; break;
			}
		}
		
		if (Keypressed.x == 10)
		{
			//map_findaway();
		}
						
		// Verifica contador do relógio
		if (clock() >= clock_endwait)
		{
			// Movimenta a cobrinha principal secundo a direção atual
			snake_move(&cobra->snake, cobra->snake.dir, &mainmap);
			
			// Verifica colisões da cobrinha principal
			switch (snake_collide_object(&cobra->snake, &mainmap))
			{
				// Colidiu contra: Obstáculo
				case OBJECT_OBSTACLE:
					// Decrementa 1 (uma) vida
					cobra->snake.lifes -= 1;
					// Reposiciona a cobrinha no local de origem
					for (i = 0; i < cobra->snake.length; i++)
					{
						cobra->snake.body[i].x = cobra->snake.x;
						cobra->snake.body[i].y = cobra->snake.y;
					}
					cobra->snake.dir = DIRECTION_RIGHT;
				break;
			}
			
			// Colidiu contra si mesma
			if (snake_collide_self(&cobra->snake))
			{
				// Ativa Modo Zombie
				cobra->snake.mode = SNAKE_MODE_ZOMBIE;
				// Decrementa seu comprimento em 1 (uma) unidade
				cobra->snake.length -= 1;
			}
			
			// Colidiu contra objeto de coleta
			if (snake_collide_food(&cobra->snake, &cobra->food))
			{
				// Incrementa pontuação em 1 (uma) unidade
				cobra->snake.score += 1;
				// Incrementa o comprimento em 1 (uma) unidade
				cobra->snake.length += 1;
				// Reproduz áudio correspondente
				audio_play(audio_mainchannel, AUDIO_FOOD1, FALSE);
				// Define nova posição para o objeto de coleta
				food_newposition(&cobra->food, &mainmap);
				//map_findaway(
				//	cobra->snake.body[cobra->snake.length - 1].x - MAP_X, 
				//	cobra->snake.body[cobra->snake.length - 1].y - MAP_Y, 
				//	cobra->food.x - MAP_X, cobra->food.y - MAP_Y);
			}
			
			// Encontra uma nova posição (x, y) para a cobrinha concorrente			
			newpos = map_findaway(
				cobra->snakeA.body[cobra->snakeA.length - 1].x - MAP_X,
				cobra->snakeA.body[cobra->snakeA.length - 1].y - MAP_Y,
				cobra->food.x - MAP_X,
				cobra->food.y - MAP_Y
			);

			// Movimenta a cobrinha concorrente para a nova posição (x, y)
			if (newpos.x >= 0 && newpos.y >= 0)
			{
				snake_movexy(&cobra->snakeA, newpos, &mainmap);
			} else
			{
				// Incrementa pontuação em 1 (uma) unidade
				cobra->snakeA.score += 1;
				// Incrementa o comprimento em 1 (uma) unidade
				cobra->snakeA.length += 1;
				// Reproduz áudio correspondente
				audio_play(audio_mainchannel, AUDIO_FOOD1, FALSE);
				// Define nova posição para o objeto de coleta
				food_newposition(&cobra->food, &mainmap);
				//map_findaway(
				//	cobra->snake.body[cobra->snake.length - 1].x - MAP_X, 
				//	cobra->snake.body[cobra->snake.length - 1].y - MAP_Y, 
				//	cobra->food.x - MAP_X, cobra->food.y - MAP_Y);
			};
			
			// Imprime ambas as cobrinhas
			snake_draw(&cobra->snake);
			snake_draw(&cobra->snakeA);
			
			// Imprime objetos de coleta
			food_draw(&cobra->food);
			
			// Imprime informações da seção de jogo atual
			map_drawinfo(cobra->snake.lifes, cobra->snake.score);
			
			//blink += 1;
			switch(blink)
			{
				case 0: textcolor(LIGHTRED); 
						gotoxy(24, 7); printf("o"); 
						textcolor(YELLOW); 
						gotoxy(28, 7); printf("O"); 
						blink = 1;
				break;
				
				case 1: textcolor(YELLOW); 
						gotoxy(24, 7); printf("o");
						textcolor(LIGHTRED); 
						gotoxy(28, 7); printf("O"); 
						blink = 0;
				break;
			}
						
			/* BUG:
			 * (1) Texto desnecessário é impresso
			 * na tela, por exemplo, ^[[A.
			 * (2) Deve-se trocar o método de contagem
			 * de tempo atual por um que reset a
			 * variável contador, de modo a não haver
			 * o estouro da memória. */
			textcolor(DARKGREY); gotoxy(1, 24);
							
			// Incrementa contagem do relógio
			clock_endwait = clock() + clock_waitmili;
		}
	}
}
