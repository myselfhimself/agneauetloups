#Start Makefile
#
# Pour ceux qui n'ont jamais compiler sous linux: dans le répertoire de 
# votre projet, tapez `make`
#

# EXEC: Le nom de l'exécutable,
EXEC= Projo_giga_generation

# SRC: vos fichiers sources (seulement les .c) séparés par un espace
# Ou SRC= $(wildcard *.c) pour prendre tout les .c du répertoire ...
#
#SRC= main.c
SRC= $(wildcard *.c)

# Les Librairie 
#
LIBS =	`pkg-config --cflags --libs gtk+-2.0`

#
# Les options du compilateur
#
#
#
#CFLAGS=			-Wall -ansi -g
CFLAGS=                        -Wall -g
CC = 			gcc
STD = 			_GNU_SOURCE


#
# La suite devrait convenir pour la plus part des compils ...
#
.c.o:
	@$(CC) -c $(CFLAGS) -D$(STD) $(LIBS) $<

all: project

project:$(SRC)
	@echo "--- Compilation ---"
	$(CC) $(SRC) -o $(EXEC) $(CFLAGS) -D$(STD) $(LIBS)
	
clean:
	@rm -f *.o core
	@echo "--- Grand Netoyage ---"

execute:
	./$(EXEC)

# End Makefile
