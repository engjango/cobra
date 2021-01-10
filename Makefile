#*************************************************************************
# * 
# * Makefile
# * 
# * (c) 2021 J. G. Silva (django) <dparicarana@gmail.com>
# * 
# * "Snake game written in C - animations, retro menu, smart snake 
# * enemies, sound effects."
# * 
# * last modification: 2021-01-07
# * 
# ************************************************************************
 

VERSION   = 1.0.0
CC       ?= gcc
#CFLAGS   += -W -Wall -Werror -DVERSION=\"$(VERSION)\"
CFLAGS    += -W -Wall -DVERSION=\"$(VERSION)\"
LIBPATH	  = /lib
LFLAGS	 += -L LIBPATH -lbass -lastar
#LFLAGS	 += -L LIBPATH -lbass
TARGET	  = cobra

all:
	$(CC) $(CFLAGS) -c uconio.c sound.c texteffects.c menu.c map.c food.c snake.c cobra.c
	$(CC) $(CFLAGS) uconio.o sound.o texteffects.o menu.o map.o food.o snake.o cobra.o main.c -o $(TARGET) $(LFLAGS)

clean:
	-@$(RM) $(TARGET) *.o *.gch
