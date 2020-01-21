#include "../include/descripteur_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/*------------------------------------ fonction d'ecriture de descripteurs ----------------------------------------*/

void ecriture_descripteur_image (descripteur_image_s descripteur, int couleur){
    char * aux0;
    char * aux;
    int num;
    char snum[5];
    int i;
    FILE * fileDescripteurImage = NULL;
    if (couleur == 1)
    {
        aux0 = "../data/Descripteurs/ImagesRGB/";
    }
    else
    {
        aux0 = "../data/Descripteurs/Images/";
    }  
    aux = (char *)malloc(50*sizeof(char));
    strcpy(aux, aux0);
    num = descripteur.ID;
    sprintf(snum, "%d", num);
    strcat(aux, snum);
    fileDescripteurImage = fopen(aux, "w");
    if (fileDescripteurImage==NULL) printf("impossible de créer ce fichier");

/*on ecrit l'ID*/
    fprintf(fileDescripteurImage,"%d \n", descripteur.ID);

/*on ecrit le tableau d'intensité et d'occurences*/
    for (i=0; i<512; i++){
        fprintf(fileDescripteurImage, "%d  ",descripteur.listeIntensite[i].intensite);
        fprintf(fileDescripteurImage, "%d \n",descripteur.listeIntensite[i].occurence);
    }
    fclose(fileDescripteurImage);
    free(aux);
}


/*-------------------- fonction de lecture de descripteur et remplissage de la structure -------------------*/

void lecture_descripteur_image (descripteur_image_s descripteur, char *chemindescripteurtxt){
    FILE * fileDescripteurImage = NULL;
    int i;
    fileDescripteurImage = fopen(chemindescripteurtxt, "r");
    if (fileDescripteurImage==NULL) printf("impossible de lire ce fichier");

    /*on vient remplir la structure ID puis boucle pour le tableau d'occurence*/

    fscanf(fileDescripteurImage, "%d", &descripteur.ID);

    for(i = 0; i<512; i++){
        fscanf(fileDescripteurImage, "%d", &descripteur.listeIntensite[i].intensite);
        fscanf(fileDescripteurImage, "%d", &descripteur.listeIntensite[i].occurence);
    }
    fclose(fileDescripteurImage);
}

void setDiSuiv(Descripteur_image a, Descripteur_image b) {
    a->desc_suiv = b;
}