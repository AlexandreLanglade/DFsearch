# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "../include/indexationAudio.h"

    /* ETAPE 1 : RECUPERATION DES VALEURS*/

int lectureFichierAudio(char *nomFichierAudio,float **valeursFichierAudio,long *nbrValeurs){
    
    /* ouverture fichier audio*/
    unsigned long compteur=0;
    float *valTemp=NULL;
    
    FILE *fichierAudio=NULL;
    fichierAudio=fopen(nomFichierAudio,"r");
    if(fichierAudio==NULL){return 2;}

    /* lecture fichier audio*/

        /* initialisation lecture*/

    rewind(fichierAudio);
    *valeursFichierAudio=(float*)malloc(sizeof(*valeursFichierAudio));if(valeursFichierAudio==NULL){return 1;}

        /* boucle lecture*/

    while(!feof(fichierAudio)){
        valTemp=(float *)realloc(*valeursFichierAudio,(compteur+1)*sizeof(**valeursFichierAudio));
        if(valTemp==NULL){return 1;}
        *valeursFichierAudio=valTemp;
        fscanf(fichierAudio,"   %f\n",&(*valeursFichierAudio)[compteur]);
        compteur++;
    }

        /* mise à jour pointeurs + fin fonction*/
    
    *nbrValeurs=compteur;
    fclose(fichierAudio);
    return 0;
}

unsigned int getK(unsigned int n,unsigned long nbrValeurs){
    unsigned int k = nbrValeurs/n;
    if(nbrValeurs%n!=0){return k+1;} /* nécessaire pour ne pas perdre d'information*/
    return k;
}

int getIntervallesM(float **intervallesM,unsigned int m){

    /* initialisation des variables locales*/
    int i;
    int nbrValeurs=m+1;
    float ecart=2.0/(float)m;
    *intervallesM=malloc(nbrValeurs*sizeof(**intervallesM));
    if(*intervallesM==NULL){return 1;}

    /* remplissage du tableau de valeur*/

    (*intervallesM)[0]=-1.0;
    (*intervallesM)[nbrValeurs-1]=1.0;
    for(i=1;i<nbrValeurs-1;i++){
        (*intervallesM)[i]=-1.0+ecart*i;
    }

    /* fin fonction*/

    return 0;
}

void afficherValeurs(float *valeurs,unsigned long nbrValeurs){
    /*unsigned int i = 0;
    for(i=0;i<nbrValeurs;i+=10){
        printf("valeur %d = %f\n",i,valeurs[i]);
    }*/
}

	/* ETAPE 2 : ECHANTILLONNAGE*/

void changementBase(float **valeurs,unsigned long nbrValeurs){

    /* initialisation variables locales*/

    float valMax=*valeurs[0],valMin=valMax,centre;
    float temp;unsigned long indiceMax,indiceMin;
    unsigned long i;
    /* Détermination du centre de l'intervalle primitif*/

    for(i=0;i<nbrValeurs;i++){
        temp=(*valeurs)[i];
        if(temp>valMax){
            valMax=temp;
            indiceMax=i;
        }
        if(temp<valMin){
            valMin=temp;
            indiceMin=i;
        }
    }
    centre=(valMax+valMin)/2;
    
    /* TRAITEMENT*/
        /* Décalage de l'intervalle primitif tq centre = 0*/
        /* Division de l'intervalle primitif par l'amplitude*/
        valMax-=centre;valMin-=centre;
        for(i=0;i<nbrValeurs;i++){
            (*valeurs)[i]-=centre;
            (*valeurs)[i]/=valMax;
        }
    
    /* fin fonction*/
}

int lectureNValeurs(unsigned int n,unsigned int curseur,float *valeursEntree,float **valeursSortie,unsigned long int nbrValeurs){

    /* initialisation variables locales*/
    unsigned int i;
    *valeursSortie=malloc(n*sizeof(*valeursSortie));
    if(valeursSortie==NULL){return 1;}

    /* lecture valeurs*/

    for(i=0;i<n;i++){
        (*valeursSortie)[i]=valeursEntree[i+curseur];
        if(i+curseur==nbrValeurs){return 0;}
    }

    /* fin fonction*/

    return 0;
}

/* TODO -> Recherche dichotomique de valeur plutôt que boucle de comptage pour optimiser*/
int histogramme(float *valeursN,unsigned int n,float *intervallesM,unsigned int M,matrice *mat,unsigned int colonne){

    /* initialisation variables locales*/
    float tempM;
    int trouve;
    unsigned int compteur;
    unsigned int i;

    /* boucle de comptage : parcours boucle *valeurs!n*/

    for(i=0;i<n;i++){
        if((valeursN[i]<-1)||(valeursN[i]>1)){return 5;}
        trouve=false;
        compteur=1;
        while((compteur<M)&(!trouve)){
            /* on codera plus tard la recherche dichotomique pour optimiser la recherche*/
            /* parcours boucle intervallesM, 1 to max-1*/
            tempM=intervallesM[compteur];
            if(valeursN[i]<tempM){
                mat->val[colonne][compteur-1]++;
                trouve=true;
            }
            else{
                compteur++;
            }
        }
    }

    /* fin fonction*/

    return 0;
}

	/* ETAPE 3 : DESCRIPTEUR*/

int ecritureDescripteur(char *nomFichierDescripteur,descripteur des){
  
  /* ouvrir fichier descripteur*/
  int i;
  unsigned int r;
  unsigned int j;
  FILE *fichierDescripteur=NULL;
  fichierDescripteur=fopen(nomFichierDescripteur,"w");
  if(fichierDescripteur==NULL){return 2;}
  /* ecriture fichier descripteur*/
  for(i=0;i<nbr_parametres_ecriture_audio;i++){
    switch(i){
      /* ecriture de l'ID*/
      case 0 : fprintf(fichierDescripteur,"ID_FICHIER : %d\n",des.identifiant);break;
      /* ecriture du type de fichier*/
      /* ecriture de k*/
      case 1 : fprintf(fichierDescripteur,"k : %d\n",des.k);break;
      /* ecriture de M*/
      case 2 : fprintf(fichierDescripteur,"M : %d\n",des.M);break;
      /* ecriture des valeurs de la matrice k*M*/
      case 3 : 
        for(r=0;r<des.valeurs.nbLig;r++){
            for(j=0;j<des.valeurs.nbCol;j++){
                fprintf(fichierDescripteur," %ld\n",des.valeurs.val[r][j]);
            }
            /*fprintf(fichierDescripteur,"\n");*/
        }
    }
  }
  /* fin fonction*/

  fclose(fichierDescripteur);
  return 0;
}