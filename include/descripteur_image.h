#ifndef H_DESCIMAGE
#define H_DESCIMAGEs

typedef struct etcouleurs {
    int intensite;
    int occurence;
}   couleurs;

/*structure du descripteur */
typedef struct descripteurIM {
    /*data*/
    int ID;
    couleurs listeIntensite [256];
    /*pointeur vers descripteur suivant*/
    struct descripteurIM * desc_suiv;
} descripteur_image_s ;

/*pointeur vers un descripteur*/
typedef descripteur_image_s * Descripteur_image;

/*----------------------- fonctions -------------------------------*/

void ecriture_descripteur_image (descripteur_image_s descripteur, int couleur);
void lecture_descripteur_image (descripteur_image_s descripteur, char *chemindescripteurtxt);
void setDiSuiv(Descripteur_image a, Descripteur_image b);


#endif