all: liste.c truc.c abr.c ligne.c connexion.c aqrtopo.c dijkstra.c test.c
	gcc -o test liste.c truc.c abr.c ligne.c connexion.c aqrtopo.c dijkstra.c -Wall test.c -g -lm

clean:
	$(RM) myprog
