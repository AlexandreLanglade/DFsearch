#ifndef INDEXIMA_H
#define INDEXIMA_H

#include "descripteur_image.h"
#include "quantification.h"
#include "pile.h"



Descripteur_image initDescript();
void remplissage_descripteur_imageNB(Descripteur_image desc_cible, char *cheminimage, Pile p);
void remplissage_descripteur_imageRGB(struct RGBQuantifie_s imageQuantifie, Descripteur_image desc_cible, Pile p);
void index_une_image(Pile p, char * cheminImage, int couleur);
void listing_descripteur (descripteur_image_s descripteur, char * cheminFichierTexte, char * cheminImage);
#endif