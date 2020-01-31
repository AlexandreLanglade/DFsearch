# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "indexationAudio.h"

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
        - echantillonnage       : return int HISTOGRAMME[1][M];
        - assemblageEchantillon : return int HISTOGRAMME[k][M];

    ETAPE 3 : DESCRIPTEUR
        - setFormatFichier      : return COURT ou LONG;
        - ecritureDescripteur   : return DESCRIPTEUR_AUDIO;
*/

unsigned int m=15, n=8192, id=0;

int resultat;

char* fichierEntreeCourt={"jingle_fi.txt"};
char* fichierEntreeLong={"corpus_fi.txt"};
char* fichierSortieCourt={"descripteur_court.txt"};
char* fichierSortieLong={"descripteur_long.txt"};

int indexationAudio(char* nomFichierEntree,char* nomFichierSortie){ //(unsigned int n,unsigned int m,int id) {

    //  ETAPE 0 : INITIALISATION DES VALEURS LOCALES

    int resultat;
    unsigned int k, M;
    unsigned long int nbrValeurs;

    float *valFichier=NULL,*valTemp=NULL,*intervallesM=NULL;

    descripteur des;
    matrice matEchantillon;

    // ETAPE 1 : RECUPERATION DES VALEURS

        // RECUPERE VALEURS FICHIER AUDIO + TAILLE FICHIER AUDIO

    resultat=lectureFichierAudio(nomFichierEntree,&valFichier,&nbrValeurs);

        // CALCULE K, FCT (N,TAILLE FICHIER AUDIO)

    k=getK(n,nbrValeurs);

        // CALCULE ET STOCK LES INTERVALLES D'ECHANTILLONNAGE DE M

    resultat=getIntervallesM(&intervallesM,m);

        // CALCULE M = NOMBRE ELEMENTS INTERVALLE D'ECHANTILLONNAGE

    M=m+1;

    //  ETAPE 2 : ECHANTILLONNAGE

        // TRANSFORMATION VALEURS PRIMITIVES POUR OBTENIR [-1;1]

    changementBase(&valFichier,nbrValeurs);

        // CREE LA MATRICE DE STOCKAGE K*M

    resultat=creerMatrice(k,M,&matEchantillon);

        // BOUCLE K FOIS : ECHANTILLONNAGE

    for(unsigned long int i=0;i<k;i++){

        // LECTURE FENETRE DE VALEURS FICHIER AUDIO

        resultat=lectureNValeurs(n,i*n,valFichier,&valTemp,nbrValeurs);

        // CALCULE L'HISTOGRAMME DE LA K-IEME FENETRE ET LES STOCKE DANS MATRICE STOCKAGE

        resultat=histogramme(valTemp,n,intervallesM,M,&matEchantillon,i);

    }

    // ETAPE 3 : ECRITURE DU DESCRIPTEUR

        // CREE LE DESCRIPTEUR
    
        des=initialiserDescripteur(id,k,M,matEchantillon);
        resultat=ecritureDescripteur(nomFichierSortie,des);

    // fin fonction

    free(valFichier);
    free(valTemp);
    free(intervallesM);
    freeMatrice(matEchantillon);
    
    return 0;
}

int main(){
    resultat=indexationAudio(fichierEntreeLong,fichierSortieLong);
    resultat=indexationAudio(fichierEntreeCourt,fichierSortieCourt);
    return 0;
}
