#ifndef STRUCTURES
#define STRUCTURES
#include "constantes.h"

typedef struct {
  unsigned int nbLig;
  unsigned int nbCol;
  unsigned long int **val;
} matrice;

typedef struct {
  unsigned int identifiant;
  unsigned int k;
  unsigned int M;
  matrice valeurs;
} descripteur;

typedef struct {
  unsigned int ligne;
  unsigned int colonne;
  float instant;
  float DKL;
  float precisionDKL;
} curseur;

typedef struct {
  char *nomFichier;
  unsigned int idFichier;
  curseur dataFichier;
} listeFichier;

/*  descripteurAudio initialiserDescripteurAudio (unsigned k, unsigned M);*/

int creerMatrice(unsigned int nbCol, unsigned int nbLig, matrice *mat); 
/* creer une matrice de taille k*m vide*/
/* renvoie 1 si erreur malloc*/

int charEstInt(char c); 
/* renvoie vrai si le char entré en paramètre représente un int*/

matrice initialiserMatrice(matrice mat); 
/* remplir une matrice pour les tests de fonctionnement*/

void afficherMatrice(matrice mat); 
/* afficher le contenu de la matrice*/

descripteur initialiserDescripteur(unsigned int id,unsigned int k,unsigned int M,matrice valeurs);
/* cree et renvoie un descripteur initialisé avec les paramètres indiqués*/

void afficherDescripteur(descripteur des);
/* affiche le contenu du descripteur*/

void freeMatrice(matrice mat);
/* libère la mémoire allouée à la matrice*/

#endif