CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=bin/DFsearch

all: $(EXEC)

bin/DFsearch: lib/menu.o lib/main.o lib/entree_sortie.o lib/wait.o lib/descripteur_image.o lib/descripteur_texte.o lib/pile.o lib/configuration.o lib/quantification.o lib/indexation_image.o lib/indexation_texte.o -lm
	$(CC) -g -o $@ $^

lib/main.o: src/main.c include/menu.h include/pile.h include/configuration.h include/descripteur_image.h include/descripteur_texte.h
	$(CC) -o $@ -c $< $(CFLAGS)

lib/menu.o: src/menu.c include/entree_sortie.h include/wait.h include/pile.h include/configuration.h
	$(CC) -o $@ -c $< $(CFLAGS)

lib/entree_sortie.o: src/entree_sortie.c
	$(CC) -o $@ -c $< $(CFLAGS)

lib/wait.o: src/wait.c include/pile.h
	$(CC) -o $@ -c $< $(CFLAGS)

lib/pile.o: src/pile.c include/descripteur_texte.h include/descripteur_image.h
	$(CC) -o $@ -c $< $(CFLAGS)

lib/descripteur_image.o: src/descripteur_image.c
	$(CC) -o $@ -c $< $(CFLAGS)

lib/descripteur_texte.o: src/descripteur_texte.c
	$(CC) -o $@ -c $< $(CFLAGS)

lib/configuration.o : src/configuration.c include/indexation_image.h
	$(CC) -o $@ -c $< $(CFLAGS)

lib/quantification.o : src/quantification.c include/configuration.h
	$(CC) -o $@ -c $< $(CFLAGS)

lib/indexation_image.o : src/indexation_image.c include/descripteur_image.h include/quantification.h include/pile.h
	$(CC) -o $@ -c $< $(CFLAGS)

lib/indexation_texte.o : src/indexation_texte.c include/descripteur_texte.h include/pile.h include/configuration.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf lib/*.o

mrproper: clean
	rm -rf $(EXEC)