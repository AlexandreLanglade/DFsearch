#ifndef H_RECHTEXTE
#define H_RECHTEXTE

#include "pile.h"

typedef struct Element_s
{
    int id;
    int nbOccu;
    struct Element_s *elementSuivant;

}Element;

typedef struct Element_s * Liste;

Element* initElement();

void ajoutElement(Liste *liste,Element* element);

int getNbOccu(Descripteur_texte descripteur,char *mot); /*Renvoie 0 si le descripteur n'a pas le mot et l'id du descripteur si le mot est present  */

char** recherche_mot_cle(Pile pile, char * mot); 

void ouvertureTexte(char* path);


#endif