#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/quantification.h"



/*--------------------------- Fonction entree entier sortie tableau d'entier binaire -----------------------------*/
int * IntToBinaire (int entier){
    int * tab = malloc(8*sizeof(int));
    int i;
    for(i=0; i<8; i++)  {  
        tab[i] = entier%2;  
        entier = entier/2;
    }
    return tab;
    
}


/*-------------------------------- fonction de passage de binaire à entier --------------------------------------*/
 int binaireToInt (int * binaire){
    int entier=0;
    int i;
    int bits=getConfig_image_NbBits();
    for (i=0; i<bits*3; i++){
        entier+=(binaire[i])*(pow(2,(bits*3)-i-1));
    }
    return entier;
}




/*---------------------------------- fonction de quantification  d'une valeur----------------------------------------*/
/*dans cette fonctions, les paramètres sont des tableaux représentants les valeurs d'intensité de r g et b en binaire*/
int * quantifier_binaires (int * r, int * g, int * b){
    int bits=getConfig_image_NbBits(); 
    int j=0;
    int i;
    int * nouveauTab = (int *)malloc(9*sizeof(int));
    for(i=0; i<bits; i++){
        nouveauTab[j]=r[8-i];
        j++;
    }
    
    for(i=0; i<bits; i++){
        nouveauTab[j]=g[8-i];
        j++;
    }
    for(i=0; i<bits; i++){
        nouveauTab[j]=b[8-i];
        j++;
    }
    return nouveauTab;
}
/*--------------------------------- fonction de creation de la matrice quantifiee ---------------------------------------*/
/*elle appelle en boucle la quantification de 3 valeurs grâce à (fusinner_binaires)*/

int** quantif_3_matrices (int** R, int** G, int** B, int lignes, int colonnes){
    int * binaire_quantifie;
    int * binR, * binG, * binB;
    int ** test = malloc(lignes * sizeof(int *));
    int i;
    int j;
    for (i = 0; i < lignes; i++)
    {
        *(test+i) = malloc(colonnes*sizeof(int)) ;
    }
      
    for(i=0; i<lignes; i++){
        for(j=0; j<colonnes; j++){
            binR = IntToBinaire(R[i][j]);
            binG = IntToBinaire(G[i][j]);
            binB = IntToBinaire(B[i][j]);
            binaire_quantifie =quantifier_binaires(binR, binG, binB);
            test[i][j]=binaireToInt(binaire_quantifie);
        
        }
    }
    return test;
}







struct RGBQuantifie_s quantification (char * adresse_img){
    int ** R, ** G, ** B;
    int i, j;
    int a1, a2, a3, lignes, colonnes, valeur;
    struct RGBQuantifie_s imageQuantifie;

    FILE * txtImage = NULL;
    txtImage=fopen(adresse_img, "r");
    if (txtImage==NULL) printf("impossible d'ouvrir ce fichier");
    fscanf(txtImage, "%d %d", &lignes, &colonnes);
    
    
    imageQuantifie.IDS[0]=lignes;
    imageQuantifie.IDS[1]=colonnes;
        

/*  Allocation des mémoires pour les tableaux 2D */


    R =  (int**)malloc(lignes * sizeof(int *)) ;
    if(R==NULL){
        printf("%s \n", "MALLOC R1 FAIL");
    }
    
    for (a1=0; a1<lignes; a1++){
        *(R+a1) = (int *)malloc(colonnes * sizeof(int));
    }
        if(*R==NULL){
            printf("%s \n", "MALLOC R2 FAIL ");
        }



    G = (int**)malloc(lignes * sizeof(int *)) ;
        if(G==NULL){
            printf("%s \n", "MALLOC G FAIL");
        }
    
    for (a2=0; a2<lignes; a2++){
        *(G+a2) = (int*)malloc(colonnes * sizeof(int));}
        if(*G==NULL){
            printf("%s \n", "MALLOC G2 FAIL");
        }
        


    B = (int**)malloc(lignes * sizeof(int *)) ;
        if(B==NULL){
            printf("%s \n", "MALLOC B FAIL");
        }
        
        for (a3=0; a3<lignes; a3++){
            *(B+a3) = (int *)malloc(colonnes * sizeof(int));}
            if(*B==NULL){
                printf("%s \n", "MALLOC B2 FAIL");
            }
            



    
/* on rempli le tableau R */
    fscanf(txtImage,"%d", &valeur); /*on place le curseur à la deuxieme ligne*/
    for (i=0; i<lignes;i++){
        for(j=0; j<colonnes; j++){
            fscanf(txtImage, "%d", &R[i][j]);
        }
    }

/* on rempli le tableau G */
    for (i=0; i<lignes;i++){
        for(j=0; j<colonnes; j++){
            fscanf(txtImage, "%d", &G[i][j]);
        }
    }

/* on rempli le tableau B */
    for (i=0; i<lignes;i++){
        for(j=0; j<colonnes; j++){
            fscanf(txtImage, "%d", &B[i][j]);
        }
    }
 
/*remplissage du nouveau tab 2D (calculs)*/
/*on quantif_3_matrices nos R, G et B. ordre : boucle qui pour chaque entier du *tab, transforme en binaire, quantifie, puis reconvertie chaque valeurs en entier*/
    imageQuantifie.tab= quantif_3_matrices(R, G, B,lignes, colonnes);
    
    return imageQuantifie;
}

