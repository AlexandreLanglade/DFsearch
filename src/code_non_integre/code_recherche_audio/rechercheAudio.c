# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <assert.h>
# include "rechercheAudio.h"

int lectureDescripteur(char *nomDescripteur,descripteur *des){

    // initialisation variable locale

    unsigned int id,k,M,valTemp;
    matrice histogramme;
    int erreur;

    // ouverture du descripteur

    FILE *fichierDescripteur=NULL;
    fichierDescripteur=fopen(nomDescripteur,"r");
    if(fichierDescripteur==NULL){return 2;}

    // lecture Id, formatFichier, k, M

    rewind(fichierDescripteur);
    fscanf(fichierDescripteur,"ID_FICHIER : %d\n",&id);
    fscanf(fichierDescripteur,"k : %d\n",&k);
    fscanf(fichierDescripteur,"M : %d\n",&M);

    // lecture Histogramme

    erreur=creerMatrice(k,M,&histogramme);

    for(unsigned int i=0;i<k;i++){ // nbr ligne
        for(unsigned int j=0;j<M;j++){ // nbr colonne
            fscanf(fichierDescripteur," %d\n",&valTemp);
            histogramme.val[i][j]=valTemp;
        }
    }

    // fin fonction

    des->identifiant=id;
    des->k=k;
    des->M=M;
    des->valeurs=histogramme;

    fclose(fichierDescripteur);
    return erreur;
}

curseur comparerDescripteur(descripteur des1,descripteur des2){

    // Initialisation des variables locales

    unsigned int nbLig1=des1.k,nbLig2=des2.k,nbCol=des1.M;
    matrice mat1=des1.valeurs,mat2=des2.valeurs;
    descripteur desTemp;

    float DKL,op1,op2,op3;
    unsigned int val1,val2,compt;

    curseur c,index;
    index.DKL=SEUIL_DKL;
    index.precisionDKL=0;

    /*
    INITIALISATION DU CURSEUR
        PARCOURS PARALLELE MAT1 MAT2
        COMPARAISON VALEURS
        CALCUL SIMILARITE QUAND MAT1 PARCOURU DANS MAT2
    */
   
   if(des1.k!=des2.k){
    // Cas où les descripteurs ne font pas la même taille
    // On place le plus petit descripteur en mode actif (des1)
    
        if(des1.k>des2.k){
            desTemp=des2;
            des2=des1;
            des1=desTemp;
        }
        
        unsigned int nbLig1=des1.k,nbLig2=des2.k,nbCol=des1.M;
        matrice mat1=des1.valeurs,mat2=des2.valeurs;

        c.ligne=0;

        while(c.ligne<nbLig2-nbLig1){
        // parcours du décalage vertical
        // printf("Initialisation c.ligne / limite = %d / %d\n",c.ligne,nbLig2-nbLig1+1);
        c.colonne=0;
            while(c.colonne<nbCol){
                // parcours du décalage horizontal
                DKL=0;
                compt=0;
                for(unsigned int i=0;i<nbLig1;i++){
                    // parcours vertical sans décalage
                    // printf("ligne mat2 = %d, ligne mat1 = %d <=> %d, dépassement %d\n",c.ligne,i,c.ligne+i,c.ligne+i+1);
                    for(unsigned int j=0;j<nbCol;j++){
                        // parcours horizontal sans décalage
                        // printf("pos mat1 (%d,%d) pos mat2 (%d,%d)\n",i,j,c.ligne+i,c.colonne+j);
                        val1=mat1.val[i][j];
                        //printf("val1[%d][%d]=%d\n",i,j,val1);
                        if(c.colonne+j<nbCol){
                            val2=mat2.val[c.ligne+i][c.colonne+j];
                            // printf("pos mat1 (%d,%d) pos mat2 (%d,%d)\n",i,j,c.ligne+i,c.colonne+j);
                            // printf("    val2[%d][%d]=%d\n",c.ligne+i,c.colonne+j,val2);
                        }
                        if(c.colonne+j>=nbCol){
                            val2=mat2.val[c.ligne+i+1][c.colonne+j-nbCol];
                            // printf("pos mat1 (%d,%d) pos mat2 (%d,%d)\n",i,j,c.ligne+i+1,c.colonne+j-nbCol);
                            // printf("    val2[%d][%d]=%d\n",c.ligne+i+1,c.colonne+j-nbCol,val2);
                        }

                        /*
                            *** Divergence / Distance de Kullback-Leibler ***

                            DKL(P,Q)=Somme(P(i)*log(P(i)/Q(i)));
                        */

                        if(val2!=0){
                            op1=val1/val2;
                            if(op1!=0){
                                op2=logf(op1);
                                op3=op2*val1;
                                DKL+=op3;
                                compt++;
                            }
                        }                    
                    }
                }
                // calcul du DKL moyen
                DKL/=compt;

                // Stockage des données : DKL min, DKL max
                if(DKL<=SEUIL_DKL && DKL<=index.DKL){
                    index.DKL=DKL;
                    index.ligne=c.ligne;
                    index.colonne=c.colonne;
                }
                else if(DKL>=index.precisionDKL){
                    index.precisionDKL=DKL;
                }   
                c.colonne++;
            }
        c.ligne++;
        }
        float rapTsCol=(float)index.colonne/(float)nbCol;
        float ligne=(float)index.ligne+rapTsCol;
        index.instant=ligne/nbLig2;
        //printf("rapport temps total = %f\n",index.instant);
    }
   
   else{
       compt=0;
       DKL=0;
       for(unsigned int i=0;i<nbLig1;i++){
           for(unsigned int j=0;j<nbCol;j++){
               val1=mat1.val[i][j];
               val2=mat2.val[i][j];
                if(val2!=0){
                    op1=val1/val2;
                    if(op1!=0){
                        op2=logf(op1);
                        op3=op2*val1;
                        DKL+=op3;
                        compt++;
                    }
                }     
            compt++;
            }
        }
        // calcul du DKL moyen
                DKL/=compt;

                // Stockage des données : DKL min, DKL max
                if(DKL<SEUIL_DKL && DKL<index.DKL){
                    index.DKL=DKL;
                }
                else if(DKL>index.precisionDKL){
                    index.precisionDKL=DKL;
                }    
        index.ligne=0;index.colonne=0;index.instant=0;
        //printf("rapport temps total = %f\n",index.instant);
    }

    return index;
}

curseur rechercheMain(descripteur desBase, char* nomFichierComparaison,unsigned int *idFichier){ 

    //  ETAPE 0 : INITIALISATION DES VALEURS LOCALES

    int resultat;
    unsigned int idBase=desBase.identifiant,
    kBase=desBase.k,
    MBase=desBase.M;
    matrice valeursBase=desBase.valeurs;

    // ETAPE 1 : LECTURE DESCRIPTEUR COMPARAISON

    unsigned int idTest,kTest,Mtest;
    matrice valeursTest;
    descripteur test=initialiserDescripteur(idTest,kTest,Mtest,valeursTest);
    resultat=lectureDescripteur(nomFichierComparaison,&test);
    *idFichier=test.identifiant;

    // ETAPE 2.1 : COMPARAISON DESCRIPTEURS

    curseur index=comparerDescripteur(desBase,test);

    return index;
}
