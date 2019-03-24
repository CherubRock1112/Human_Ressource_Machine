CC = g++
CFLAGS = -std=c++14 -Wall
CFLAGS2 = -ltgui -lsfml-graphics -lsfml-window -lsfml-system
FILES = main.o interface.o jeu.o

all: main

main: $(FILES)
	$(CC) $(CFLAGS) $(FILES) $(CFLAGS2) -o sfml-app
	DISPLAY=:0 ./sfml-app
	
%.o : %.cpp
	$(CC) $(CFLAGS) $(CFLAGS2) -c $<



interface.cpp : interface.h	

jeu.cpp : interface.h jeu.h instruction.h addition.h soustraction.h increment.h decrement.h saut.h sautsinul.h sautsinegatif.h entree.h sortie.h sauvegarde.h charge.h niveau.h

main.cpp : interface.h jeu.h interface.h instruction.h niveau.h

clean:
	rm -rf $(FILES) sfml-app

.PHONY: all clean