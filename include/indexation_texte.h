#ifndef H_INDEXTXT
#define H_INDEXTXT

#include "descripteur_texte.h"
#include "pile.h"
#include "configuration.h"


/*----------------------------------------------------------------------------------------------*/
int isMotOutil(char *mot);
void tri();
void deleteBalises(char *chemin);
void deletemot(char *mot);
int nbOccurence(char *mot);
int nombreMots();
void deleteLast(Descripteur_texte descripteur);
int getId(Pile pile);
void index_un_texte(char *chemin, Pile pile);



#endif