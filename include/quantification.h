#ifndef QUANTIF_H
#define QUANTIF_H

#include "configuration.h"

typedef struct RGBQuantifie_s {
    int IDS[3];
    int  ** tab;
}RGBQuantifie;


 int* IntToBinaire (int entier);
 int binaireToInt (int * binaire);
 int * quantifier_binaires (int * r, int * g, int * b);
 int** quantif_3_matrices (int** R, int** G, int** B, int lignes, int colonnes);
 struct RGBQuantifie_s quantification (char *adresse_img);

#endif