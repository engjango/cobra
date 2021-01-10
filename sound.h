/*************************************************************************
 * 
 * sound.h
 * 
 * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
 * 
 * "Snake game written in C - animations, retro menu, smart snake 
 * enemies, sound effects."
 * 
 * last modification: 2021-01-07
 * 
 ************************************************************************/
 
#ifndef SOUND_H
#define SOUND_H

#define	SOUND

#define FALSE	0
#define TRUE	1

#define AUDIO_INTRO				"audio/intro.mp3"
#define AUDIO_MENU_MAIN 		"audio/mainmenu.mp3"
#define AUDIO_DJANGO			"audio/django.mp3"
#define AUDIO_TEFX_ADDCHAR		"audio/addchar.mp3"
#define AUDIO_TEFX_SLIDING		"audio/sliding.mp3"
#define AUDIO_TEFX_SLIDINGTOC	"audio/slidingtoc.mp3"
#define AUDIO_FOOD1				"audio/food1.mp3"
#define AUDIO_MAP1				"audio/map1.mp3"

extern long int audio_mainchannel;

int audio_initialize();
void audio_terminate();
int audio_play(unsigned long int audiochannel, char *filename, short repeat);
void audio_stop();
void audio_resume();

#endif /* SOUND_H */
