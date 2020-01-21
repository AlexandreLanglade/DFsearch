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