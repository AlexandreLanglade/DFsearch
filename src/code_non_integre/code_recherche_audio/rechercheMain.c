# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "rechercheAudio.h"



int main(){//(unsigned int nombreDescripteurBase, char* nomFichierBase, char* nomFichiersComparaisons) {

    /*
        /////////// ATTENTION \\\\\\\\\\\

        Il faut mettre le fichier de base de comparaison (le fichier qu'on recherche) en nomFichierBase.
        nomFichiersComparaisons représente le point d'entrée des chemins des fichiers de la base de données.

        C'est bien les 10 premiers résultats qu'on renvoie aussi ?

        J'ai aussi un (*** stack smashing detected ***) en compilation, mais je sais pas où c'est et cela n'empêche pas le fonctionnement ...

    */

    // valeurs initiales de test

    unsigned int nombreDescripteurBase=2;
    char* nomFichierBase={"descripteur_court.txt"};
    char* nomFichierComparaison1={"descripteur_long.txt"};
    char* nomFichierComparaison2={"descripteur_court.txt"};

    // initialisation des variables locales
    
    float similarite;
    int test;
    char *nomFichierComparaison,*nomFichierSimilaire;
    
    unsigned int idFichierSimilaire,idTemp;

    listeFichier resultat[10]={0}, listemp;

    /*
    for(unsigned int i=0;i<10;i++){
        printf("listeFichier[%d] = {%s ; %d ; %f}\n",i,resultat[i].nomFichier,resultat[i].idFichier,resultat[i].dataFichier.DKL);
    }
    */

    // lecture des valeurs du fichier descripteur base de comparaison

    unsigned int id,k,M;
    int place;
    matrice valeurs;
    descripteur desBase=initialiserDescripteur(id,k,M,valeurs);
    //descripteur desLong=initialiserDescripteur(id,format,k,M,valeurs);
    test=lectureDescripteur(nomFichierBase,&desBase);
    //resultat=lectureDescripteur(nomFichierDesLong,&desLong);

    curseur index;

    // détermination des seuils de similarité avec les fichiers comparer

    for(unsigned int compt=0;compt<nombreDescripteurBase;compt++){
        // Ici on fait boucler les descripteurs à tester
        switch(compt){
            case 0:
            nomFichierComparaison=nomFichierComparaison1;break;
            case 1:
            nomFichierComparaison=nomFichierComparaison2;break;
        }
        // Ici on test les descripteurs
        index=rechercheMain(desBase,nomFichierComparaison,&idTemp);
        if(index.precisionDKL!=0){
            float precision=index.DKL/index.precisionDKL;
            index.precisionDKL=precision;
        }
        // Ici, on stocke les résultats
        if(compt==0){
            similarite=index.DKL;
            listemp.idFichier=idTemp;
            listemp.nomFichier=nomFichierComparaison;
            listemp.dataFichier=index;
            resultat[0]=listemp;
        }
        else{
            if(index.DKL<similarite){
                similarite=index.DKL;
                listemp.idFichier=idTemp;
                listemp.nomFichier=nomFichierComparaison;
                listemp.dataFichier=index;
                place=0;
                for(unsigned int i=0;i<10 && !place;i++){
                    if(index.DKL<resultat[i].dataFichier.DKL && resultat[i].nomFichier!=NULL){
                        unsigned int index=i;
                        for(unsigned int j=10;j>i;j--){
                            resultat[j]=resultat[j-1];
                        }
                        resultat[i]=listemp;
                        place++;
                    }
                }
            }
        }
    }

    printf("RESULTATS\n");
    for(unsigned int i=0;i<10;i++){
        if(resultat[i].nomFichier!=NULL){
            printf("    - %d : nom fichier : %s / n°id : %d .Divergence KL (précision %f)) %f : lancement à %f * durée du fichier (s).\n"
            ,i+1,resultat[i].nomFichier,resultat[i].idFichier,resultat[i].dataFichier.precisionDKL,resultat[i].dataFichier.DKL,resultat[i].dataFichier.instant);
        }
    }

    // fin fonction

    return 0;
}