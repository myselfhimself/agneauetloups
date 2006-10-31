CC=cc
OPTIONS=`pkg-config --cflags --libs gtk+-2.0` -I. 

jeu.bin : main.o outils.o projet.h
	$(CC) $(OPTIONS) main.o outils.o -o jeu.bin

main.o : main.c main.h
	$(CC) $(OPTIONS) -c main.c

outils.o: outils.c outils.h main.h
	$(CC) $(OPTIONS) -c outils.c

clean:
	rm *.o
	rm *.out 
