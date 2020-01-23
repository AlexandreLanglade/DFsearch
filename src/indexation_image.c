#include <stdio.h>
#include <stdlib.h>
#include "../include/indexation_image.h"




/*------------------ fonction d'initialisation du descripteur (cas:NB) ---------------------------*/

Descripteur_image initDescript(){
    int i;
    Descripteur_image descripteur = (Descripteur_image)malloc(sizeof(descripteur_image_s));
    descripteur->ID = 0;
    for(i=0; i<512; i++){
        descripteur->listeIntensite[i].intensite=i;
        descripteur->listeIntensite[i].occurence=0;
        
    }
    return descripteur;
}



/*------------------- fonction de remplissage de la structure descripteur (indexation) pour NB -----------------------------------*/

void remplissage_descripteur_imageNB(Descripteur_image desc_cible ,char *cheminimage, Pile p){ 
    int lignes, colonnes, valeur, i, j;
    
    
    /* on ouvre le fichier texte contenant les infos de l'image*/
    FILE * txtImage = NULL;
    txtImage = fopen(cheminimage, "r");
    if (txtImage==NULL) printf("impossible d'ouvrir ce fichier");
    fscanf(txtImage, "%d %d", &lignes, &colonnes);
   
    /* implementation du int occurence pour chaque couleurs */
    fscanf(txtImage, "%d", &valeur); /*on place le curseur à la deuxieme ligne*/
    for (i=0; i<lignes; i++){
        for(j=0; j<colonnes; j++){
            fscanf(txtImage, "%d", &valeur);
            desc_cible->listeIntensite[valeur].occurence++;
        }
    }
    fclose(txtImage);


    /*Rajout de l'ID*/
    if(estVide_pile(p)){
        desc_cible->ID=0;
    }
    else {
        Descripteur_image inter = (Descripteur_image)top_pile(p, 2);
        desc_cible->ID=(inter->ID)+1;
    }

}

/*------------------- fonction de remplissage de la structure descripteur (indexation) pour RGB -----------------------------------*/

void remplissage_descripteur_imageRGB(struct RGBQuantifie_s imageQuantifie, Descripteur_image desc_cible, Pile p){ 
    int lignes, colonnes;
    int i, j;
    lignes=imageQuantifie.IDS[0];
    colonnes=imageQuantifie.IDS[1];
    /* implementation du int occurence pour chaque couleurs */
    
    for (i=0; i<lignes; i++){
        for(j=0; j<colonnes; j++){
            desc_cible->listeIntensite[imageQuantifie.tab[i][j]].occurence++;
        }
    }
    
    /*Rajout de l'ID*/
    if(estVide_pile(p)){
        desc_cible->ID=0;
    }
    else {
        Descripteur_image inter = (Descripteur_image)top_pile(p, 2);
        desc_cible->ID=(inter->ID)+1;
    }
}

/*------------------------ fonctions d'ecriture dans le fichier central des descripteurs -------------------------------------*/
void listing_descripteur (descripteur_image_s descripteur, char * cheminFichierTexte, char * cheminImage){
    FILE * file_listing = NULL;
    file_listing = fopen(cheminFichierTexte, "a");
    if (file_listing==NULL) printf("impossible d'acceder au listing des descripteurs ce fichier");
    fprintf(file_listing, "%d  %s \n",descripteur.ID, cheminImage);
    fclose(file_listing);
}




void index_une_image(Pile p , char * cheminImage, int couleur){
    Descripteur_image newDescripteur;
    RGBQuantifie imageQuantifie;
    
    if(couleur==1){
        newDescripteur=initDescript();
        remplissage_descripteur_imageNB(newDescripteur, cheminImage, p);
        empiler_pile(p, newDescripteur, 2);
        listing_descripteur(*newDescripteur,"../data/listing_desc_imageNB.txt", cheminImage);
    }
    if(couleur==3){
        newDescripteur=initDescript();
        imageQuantifie = quantification(cheminImage);
        remplissage_descripteur_imageRGB(imageQuantifie, newDescripteur, p);
        empiler_pile(p, newDescripteur, 2);
        listing_descripteur(*newDescripteur,"../data/listing_desc_imageRGB.txt", cheminImage);
    }
    
}

