#ifndef INDEXATIONAUDIO
#define INDEXATIONAUDIO
#include "structures.h"

/*
	INDEXATION -> DESCRIPTEUR_AUDIO indexationAudio(unsigned int m, unsigned int n, int identifiant);

    ETAPE 1 : RECUPERATION DES VALEURS
        - lectureFichierAudio   : return float valeursFichier[nbrValeurs];
        - getK                  : return unsigned int k;
        - getM                  : return float intervallesM[M];
        - M=m++;

    ETAPE 2 : ECHANTILLONNAGE
        - changementBase        : return float valeursFichier[nbrValeurs];
        - lectureFenetre        : return float valeursFichier[n];
        - histogramme       : return int HISTOGRAMME[1][M];

    ETAPE 3 : DESCRIPTEUR
        - setFormatFichier      : return COURT ou LONG;
        - ecritureDescripteur   : return DESCRIPTEUR_AUDIO;
*/

    /* ETAPE 1 : RECUPERATION DES VALEURS*/

int lectureFichierAudio(char *nomFichierAudio,float **valeursFichierAudio,long *nbrValeurs);
/* renvoie 1 si erreur malloc*/
/* renvoie 2 si erreur ouverture fichier*/

unsigned int getK(unsigned int n,unsigned long nbrValeurs);
/* retourne la valeur calculée de k*/

int getIntervallesM(float **intervallesM,unsigned int m);
/* retourne un tableau dynamique contenant les m intervalles discrets de [-1;1]*/
/* contient m+1 valeurs*/
/* contient m intervalles*/
/* renvoie 1 si erreur malloc*/

void afficherValeurs(float *valeurs,unsigned long nbrValeurs);
/* affiche le tableau de valeurs*/

	/* ETAPE 2 : ECHANTILLONNAGE*/

void changementBase(float **valeurs,unsigned long nbrValeurs);
/* pré-traitement de toutes les valeurs primitives*/
/* post-traitement, les valeurs sont dans [-1;1]*/
/* retourne 1 si erreur malloc*/

int lectureNValeurs(unsigned int n,unsigned int curseur,float *valeursEntree,float **valeursSortie,unsigned long int nbrValeurs);
/* lit les n valeurs primitives à partir de curseur*/
/* stock les n valeurs primitives dans un tableau dynamique*/

int histogramme(float *valeursN,unsigned int n,float *intervallesM,unsigned int M,matrice *mat,unsigned int colonne);
/* créé un histogramme en fct des valeurs et de m*/
/* renvoie 1 si erreur malloc*/
/* renvoie 5 si une valeur de intervallesM n'est pas comprise dans [-1;1]*/

	/* ETAPE 3 : DESCRIPTEUR*/

int setFormatFichier(unsigned long nbrValeurs); 
/* donne au fichier l'étiquette "Fichier court" ou "Fichier long"*/
/* renvoie 0 si fichier court, 1 sinon*/

int ecritureDescripteur(char *nomFichierDescripteur,descripteur des);
/* écrit dans le fichier descripteur existant*/
/* renvoie 2 si erreur ouverture fichier*/

#endif