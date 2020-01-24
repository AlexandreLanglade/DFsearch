# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "../include/structures.h"

int creerMatrice(unsigned int nbLig, unsigned int nbCol, matrice *mat){

  /* initialisation de la matrice*/
  unsigned int i;
  unsigned long int **dimension;
  mat->nbLig=nbLig;
  mat->nbCol=nbCol;
  dimension=(unsigned long int **)malloc(sizeof(unsigned long int *)*nbLig);
  if(dimension==NULL){return 1;}
  for(i=0;i<nbLig;i++){
    dimension[i]=(unsigned long int *)malloc(sizeof(unsigned long int)*nbCol);
    if(dimension[i]==NULL){return 1;}
  }
  mat->val=dimension;
  *mat=initialiserMatrice(*mat);

  /* fin fonction*/

  return 0;
}

int charEstInt(char c){
  /* '0' = 48, '9' = 57, x = 'x'-'0';*/
  int temp=(int)c-'0';
  if((temp<0)||(temp>9)){return false;}
  return true;
}

matrice initialiserMatrice(matrice mat){
  unsigned int i;
  unsigned int j;
  for(i=0;i<mat.nbLig;i++){
    for(j=0;j<mat.nbCol;j++){
      mat.val[i][j]=0; /*(double)(i+j);*/
    }
  }
  return mat;
}

void afficherMatrice(matrice mat){
  unsigned int i;
  unsigned int j;
  for(i=0;i<mat.nbLig;i++){
    for(j=0;j<mat.nbCol;j++){
      printf("%5ld | ",mat.val[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

descripteur initialiserDescripteur(unsigned int id,unsigned int k,unsigned int M,matrice valeurs){
  descripteur des;
  des.identifiant=id;
  des.k=k;
  des.M=M;
  des.valeurs=valeurs;
  return des;
}

void afficherDescripteur(descripteur des){
  printf("Descripteur - identifiant : %d\n",des.identifiant);
  printf("Descripteur - k : %d\n",des.k);
  printf("Descripteur - M : %d\n",des.M);
  printf("Histogramme k*M : \n");
  afficherMatrice(des.valeurs);
}

void freeMatrice(matrice mat){
  unsigned int i;
  for(i=0;i<mat.nbLig;i++){
      free(mat.val[i]);
  }
  free(mat.val);
}