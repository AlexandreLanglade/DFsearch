test_indexation.out : indexationAudio.c indexationMain.c structures.c
	gcc -c indexationAudio.c
	gcc -c indexationMain.c
	gcc -c structures.c
	gcc -o test_indexation.out -lm indexationAudio.o -lm indexationMain.o structures.o

test_recherche.out : rechercheAudio.c rechercheMain.c structures.c
	gcc -c rechercheAudio.c
	gcc -c rechercheMain.c
	gcc -c structures.c
	gcc -o test_recherche.out -lm rechercheAudio.o -lm rechercheMain.o structures.o

clean : 
	rm -rf *.o
	rm -rf *.out