/*************************************************************************
 * 
 * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
 * 
 * uconio.c, 
 * based on the file conio.h by Joachim Nilsson <troglobit@gmail.com>
 * 
 * getch and getche - Niko and J.F. Sebastian
 * https://stackoverflow.com/questions/7469139/what-is-equ
 * ivalent-to-getch-getche-in-linux
 * 
 * kbhit - Alan Cox, Porting DOS Applications to Linux
 * http://www.linuxjournal.com/article/1138
 * http://forums.fedoraforum.org/showthread.php?t=172337
 * 
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

#include "uconio.h"

static struct termios old, new;

/* Initialize new terminal I/O settings */
void initTermios(int echo)
{
	// grab old terminal IO settings
	tcgetattr(0, &old);
	// make new settings same as old settings
	new = old;
	// disable buffered I/O
	new.c_lflag &= ~ICANON;
	// set echo mode
	new.c_lflag &= echo ? ECHO : ~ECHO;
	// use these new terminal I/O settings now
	tcsetattr(0, TCSANOW, &new);
}

/* Restore old terminal I/O settings */
void resetTermios(void)
{
	tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return(ch);
}

/* Read 1 character without echo */
char getch(void)
{
	return(getch_(0));
}

/* Read 1 character with echo */
char getche(void)
{
	return(getch_(1));
}

/* Used to determine if a key has been pressed or not 
 * Code stolen from:
 * http://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
 * */

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

/* Wait for <ms> milliseconds */
void delay(int ms)
{
	struct timespec time;
	time.tv_sec = ms / 1000;
	time.tv_nsec = (ms % 1000) * (1000 * 1000);
	nanosleep(&time, NULL);
	fflush(stdout);
}

/* Return keypressed code x, y, z */
KEY getkeypressed(void)
{
	KEY tmp;
	tmp.x = tmp.y = tmp.z = 0;
	tmp.x = getch();
	if (tmp.x == 27)
	{
		tmp.y = getch();
		tmp.z = getch();
	}
	return(tmp);
}

/* Print at (X,Y) position on terminal. */
void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}
