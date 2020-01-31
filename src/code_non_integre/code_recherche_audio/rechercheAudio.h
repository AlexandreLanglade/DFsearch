#ifndef RECHERCHEAUDIO
#define RECHERCHEAUDIO
#include "structures.h"

/*
RECHERCHE -> DESCRIPTEUR_AUDIO rechercheAudio(DESCRIPTEUR_AUDIO);

    ETAPE 1 : RECUPERATION DES VALEURS
        - getId                 : return identifiant
        - getFormatFichier      : return COURT ou LONG;
        - getTaille             : return unsigned long int k, M;
        - getHistogramme        : return int histogramme;

    ETAPE 2.1 : FICHIER LONG -> COMPARER DESCRIPTEUR
        - comparerHistogramme   : return float %similarite (%difference valeurs)

    ETAPE 2.2 : FICHIER COURT -> CHERCHER DESCRIPTEUR
        - lectureFenetre        : return int valeurs (taille fichier court)
        - occurenceFenetre      : return int nbrOccurence et première occurence fichier court
                                # fct du %similarite à determiner
*/

    // ETAPE 1 : RECUPERATION DES VALEURS

int lectureDescripteur(char *nomDescripteur,descripteur *des);

    // ETAPE 2.1 : COMPARAISON DES DESCRIPTEURS

curseur comparerDescripteur(descripteur des1,descripteur des2);

curseur rechercheMain(descripteur desBase, char* nomFichierComparaison,unsigned int *idFichier);

#endif