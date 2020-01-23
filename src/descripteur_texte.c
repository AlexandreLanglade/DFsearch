#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/descripteur_texte.h"
#include <string.h>


/*--------------------------------------------------------------------------------------*/
/*Fonctions sur les termes*/

/*Fonction pour créer un terme "vide"*/
Terme* init_Terme()
{
    Terme *nouveau =(Terme*)malloc(sizeof(struct etTerme));
    assert(nouveau != NULL);
    
    nouveau->mot=NULL;
    nouveau->nbOccurences=0;
    nouveau->termeSuivant=NULL;

    return nouveau;
}

/*--------------------------------------------------------------------------------------*/
/*Fonctions sur les descripteurs*/
Descripteur_texte init_DescripteurTexte()
{
    Descripteur_texte descripteur = (Descripteur_texte)malloc(sizeof(struct descripteur_texte_s));
    assert(descripteur !=NULL);

    descripteur->identifiant = 0;
    descripteur->nbMots = 0; /*au lieu du 0 faire appel à une commande UNIX pour avoir le nombre de mots*/
    descripteur->nbTermes = 0;
    descripteur->listeDesTermes = NULL; /*On l'initialise à NULL on rajoutera des termes au fur et à mesure*/
    descripteur->suivant = NULL;

    return descripteur;
}

/*ajouter un terme à notre descripteur*/
void ajout_terme(Descripteur_texte descripteur, Terme *nouveau)
{
    struct etTerme *aux = descripteur->listeDesTermes;
    struct etTerme *termePrecedent = NULL;
    
    int fini=0;

    if(descripteur->listeDesTermes == NULL ) /*Si le descripteur n'a aucun de terme*/
    {
        descripteur->listeDesTermes = nouveau;
    }
    else if(descripteur->listeDesTermes->nbOccurences >= nouveau->nbOccurences )
    {
        nouveau->termeSuivant = descripteur->listeDesTermes;
        descripteur->listeDesTermes = nouveau;
    }
    else
    {
        while((aux != NULL) && (fini==0)) /* tant qu'on est pas arrivé à la fin de la liste des termes ou qu'on a pas trouvé un terme dont le nombre d'occurence est supérieur*/
        {
            if(aux->nbOccurences >= nouveau->nbOccurences)
            {
                nouveau->termeSuivant = aux;
                termePrecedent->termeSuivant = nouveau;
                fini=1;
            }
            else if (aux->termeSuivant==NULL)
            {
                aux->termeSuivant = nouveau;
                fini = 1;
            }
            
            else
            {
                termePrecedent = aux;
                aux=aux->termeSuivant;
            }
        }
    }

    descripteur->nbTermes ++;
}


/*Fonction pour enlever le premier terme de la liste*/
void deleteTerme(Descripteur_texte descripteur)
{
    Terme *termeDepile = descripteur -> listeDesTermes;

    if (descripteur != NULL && descripteur -> listeDesTermes != NULL)
    {
        descripteur ->listeDesTermes = termeDepile ->termeSuivant;
        free(termeDepile);

        descripteur->nbTermes --;
    }
}

/*Fonction pour savoir si un mot est déjà présent dans la liste des termes*/
int isMotExistant(Descripteur_texte descripteur,char *mot)
{
    int istrue = 0;

    struct etTerme *aux = descripteur->listeDesTermes;
    if (aux != NULL)
    {
        while(istrue == 0 && aux != NULL)
        {
            if(strcmp(mot,aux->mot)==0)
            {
                istrue=1;
            }

            else
            {
                aux = aux->termeSuivant;
            }
            
        }
    }

    return istrue;
}

void setDtSuiv(Descripteur_texte a, Descripteur_texte b) {
    a->suivant = b;
}

/*Permet de lire une structure descripteur et de remplir un fichier .txt descripteur*/
void ecrire_fich_texte(Descripteur_texte descripteur){ 
    struct etTerme *aux;
    FILE *fichier =NULL;
    char nom[5];
    char chemin[50]="../data/Descripteurs/Textes/";
    aux = descripteur->listeDesTermes;

    sprintf(nom, "%d", descripteur->identifiant);
    strcat(chemin,nom);
    
    fichier = fopen(chemin,"w");                                  /*on crée un fichier texte qui a le nom du qu'on lui donne en paramètres*/

    if(fichier != NULL && descripteur != NULL)
    {
        fprintf(fichier,"%d\n",descripteur->identifiant);              /*on écrit dans le fichier texte l'identifiant qu'il y a dans la structure*/
        fprintf(fichier,"%d\n",descripteur->nbMots);                   /*on écrit dans le ficier texte le nombre de mots du texte d'origine*/
        fprintf(fichier,"%d\n",descripteur->nbTermes);                   


        while (aux != NULL)  /*Tant que la liste contient des termes*/
        {
            fprintf(fichier,"%s ",aux->mot);
            fprintf(fichier,"%d\n",aux->nbOccurences);

            aux = aux->termeSuivant;
        }

        
        fclose(fichier);

    }

}

/*Permet de lire un fichier .txt descripteur et de remplir une structure descripteur*/
Descripteur_texte lire_fich_texte(char * chemin){
    int mots,id,occu,termes,i;
    FILE *fichier =NULL;
    Terme *nouveauTerme;                            /*On crée un nouveau terme */

    /*Declaration et initialisaiton d'un descripteur*/
    Descripteur_texte descripteur;
    descripteur = init_DescripteurTexte();

    fichier = fopen(chemin,"r");                                  

    if(fichier != NULL && descripteur != NULL)
    {
        fscanf(fichier,"%d %d %d",&id,&mots,&termes);
    
        descripteur->identifiant = id;
        printf("L'id est : %d\n",id);
        descripteur->nbMots = mots;
        printf("Le nombre de mots est : %d\n",mots);
        /*descripteur->nbTermes=termes;*/
        printf("Le nombre de termes est : %d\n",termes);

       for(i=0; i<termes; i++)
        {
            
            char * motActuel = (char*)malloc(200*sizeof(char));
            fscanf(fichier,"%s %d",motActuel,&occu);
            
            nouveauTerme = init_Terme();

            nouveauTerme ->mot = motActuel;                 /*On rempli la structure avec le mot et le nombre d'occurence du mot*/
            nouveauTerme ->nbOccurences = occu;

            ajout_terme(descripteur,nouveauTerme);              /*On ajoute le nouveau terme à la structure descripteur*/
        }

    }
    fclose(fichier);

    return descripteur;
    
}