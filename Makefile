CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=bin/DFsearch

all: $(EXEC)

bin/DFsearch: lib/menu.o lib/main.o lib/entree_sortie.o lib/wait.o
	$(CC) -o $@ $^

lib/main.o: src/main.c include/menu.h
	$(CC) -o $@ -c $< $(CFLAGS)

lib/menu.o: src/menu.c include/entree_sortie.h include/wait.h
	$(CC) -o $@ -c $< $(CFLAGS)

lib/entree_sortie.o: src/entree_sortie.c
	$(CC) -o $@ -c $< $(CFLAGS)

lib/wait.o: src/wait.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf lib/*.o

mrproper: clean
	rm -rf $(EXEC)