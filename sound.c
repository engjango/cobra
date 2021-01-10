/*************************************************************************
 * 
 * sound.c
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
#include "bass.h"

/* Canal principal do dispositivo de áudio (áudios principais do jogo) */
long int audio_mainchannel;

/* Reproduz o áudio correspondente ao arquivo dado */
int audio_play(unsigned long int audiochannel, char *filename,
	short repeat)
{
	BASS_ChannelStop(audiochannel);
	if(!(audiochannel = BASS_StreamCreateFile(
		FALSE, filename, 0, 0, BASS_SAMPLE_LOOP * repeat)))
//	&&if(!(audiochannel = BASS_MusicLoad(
//		FALSE, filename, 0, 0, BASS_MUSIC_RAMP | BASS_SAMPLE_FLOAT | (BASS_SAMPLE_LOOP && repeat), 1)))
	{
		// Erro ao carregar arquivo...
		return(EXIT_FAILURE);
	} else {
		// Inicia reprodução do áudio...
		BASS_ChannelPlay(audiochannel, FALSE);
	}
	return(EXIT_SUCCESS);
}

/* Desabilita reprodução de áudio */
void audio_stop()
{
	BASS_Stop();
}

/* Habilita reprodução de áudio */
void audio_resume()
{
	BASS_Start();
}

/* Inicializa o módulo de áudio com as configurações padrão */
int audio_initialize()
{
	// Verifica se foi carregada uma versão correta da biblioteca BASS
	if (HIWORD(BASS_GetVersion()) != BASSVERSION)
	{
		return(BASS_ERROR_VERSION);
	}
	// Inicializa a biblioteca BASS
	if (!BASS_Init(-1, 44100, 0, NULL, NULL)) 
	{
		return(BASS_ERROR_INIT);
	}
	return(BASS_OK);
}

/* Finaliza o módulo de áudio corretamente */
void audio_terminate()
{
	BASS_Free();
}
