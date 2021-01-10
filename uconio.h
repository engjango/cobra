/**************************************************************************
 * 
 * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
 * 
 * uconio.h, 
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
 *************************************************************************/

#ifndef __UCONIO_H
#define __UCONIO_H

/* Text attributes */
#define RESETATTR    0
#define BRIGHT       1
#define DIM          2
#define UNDERSCORE   4
#define BLINK        5           		/* May not work on all displays. */
#define REVERSE      7
#define HIDDEN       8

/* Colors for text and background */
#define BLACK        0x0
#define RED          0x1
#define GREEN        0x2
#define BROWN        0x3
#define BLUE         0x4
#define MAGENTA      0x5
#define CYAN         0x6
#define LIGHTGREY    0x7

#define DARKGREY     0x10
#define LIGHTRED     0x11
#define LIGHTGREEN   0x12
#define YELLOW       0x13
#define LIGHTBLUE    0x14
#define LIGHTMAGENTA 0x15
#define LIGHTCYAN    0x16
#define WHITE        0x17

/* Esc[2JEsc[1;1H - Clear screen and move cursor to 1,1 (upper left) 
 * pos. */
#define clrscr() puts ("\e[2J\e[1;1H")

/* Esc[K - Erases from the current cursor position to the end of the 
 * current line. */
#define clreol() puts ("\e[K")

/* Esc[2K - Erases the entire current line. */
#define delline() puts ("\e[2K")

/* Esc[Line;ColumnH - Moves the cursor to the specified position 
 * (coordinates) */
//#define gotoxy(x,y) printf ("\e[%d;%dH", y, x)

/* Esc[?25l - Hides the cursor. */
#define hidecursor() puts ("\e[?25l")

/* Esc[?25h - Shows the cursor. */
#define showcursor() puts ("\e[?25h")

/* Esc[Value;...;Valuem - Set Graphics Mode */
#define __set_gm(attr,color,val)                                        \
        if (!color)                                                     \
                printf("\e[%dm", attr);                                 \
        else                                                            \
                printf("\e[%d;%dm", color & 0x10 ? 1 : 0, (color & 0xF) + val)

/* Set text attributes */
#define textattr(attr) __set_gm(attr, 0, 0)

/* Set text color */
#define textcolor(color) __set_gm(RESETATTR, color, 30);

/* Set text background color */
#define textbackground(color) __set_gm(RESETATTR, color, 40)

/* Key pressed code */
typedef struct tagKeypressed {
	int x;
	int y;
	int z;
} KEY;

char getch(void);
char getche(void);
int kbhit(void);
void delay(int ms);
KEY getkeypressed(void);
void gotoxy(int x,int y);
 
#endif /* __UCONIO_H */
