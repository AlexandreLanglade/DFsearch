#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "recherche_texte.h"
#include "descripteur_texte.h"


Element* initElement()
{
    Element *nouveau =(Element*)malloc(sizeof(Element));
    assert(nouveau != NULL);

    nouveau->id = 0;
    nouveau->nbOccu = 0;
    nouveau->elementSuivant = NULL;

    return nouveau;
}


void ajoutElement(Liste* liste,Element* element)
{
    int fini=0;
    Element *aux=*liste;
    Element *precedent=NULL;

    if(*liste == NULL || (*liste)->nbOccu <= element->nbOccu)    /*Si la liste est vide ou si le premier element de la liste a un nombre d'occurence plus petit */
    {
        element->elementSuivant=*liste;
        *liste = element;
    }
    else
    {
        while (aux != NULL && fini==0)
        {
            if(aux->nbOccu <= element->nbOccu)
            {
                element->elementSuivant= aux;
                precedent->elementSuivant = element;
                fini = 1;
            }
            else if (aux->elementSuivant == NULL)
            {
                aux->elementSuivant = element;
                fini = 1;
            }
            else
            {
                precedent = aux;
                aux = aux->elementSuivant;
            }
            
            
        }
        
    }
}


int getNbOccu(Descripteur_texte descripteur,char *mot)
{
    Terme *aux = descripteur->listeDesTermes;


    while (strcmp(aux->mot,mot) != 0)
    {
        aux = aux->termeSuivant;
    }

    return aux->nbOccurences;
}

char* getChemin(int id)
{
    char *chemin=(char*)malloc(100*sizeof(char));
    int i,fini=0;
    FILE *f=NULL;

    f=fopen("../data/links_txt","r");

    while (fini==0 && fscanf(f,"%d %s",&i,chemin)==2)
    {
        if(i==id)
        {
            fini=1;
        }
    }

    fclose(f);
    /*printf("%s\n",chemin);*/
    return chemin;
}

void ouvertureTexte(char* path){
    char* arg[] = {path, NULL};
    if (execlp("gedit", "gedit", path, NULL) == -1) {
        perror("error gedit");
        exit(1);
    }
 }

char** recherche_mot_cle(Pile pile, char * mot)
{
    int i;
    char **resultat=(char**)malloc(10*sizeof(char*));
    for(i=0;i<10;i++)
    {
        resultat[i]=(char*)malloc(200*sizeof(char));
    }

    Descripteur_texte descripteurAux;
    Liste liste=NULL;
    Element *aux;
    descripteurAux = (Descripteur_texte)top_pile(pile,1);

    while (descripteurAux != NULL) /*Tant qu'on a pas fini de lire tous les descripteurs */
    {
        if(isMotExistant(descripteurAux,mot)) /* Si le mot est present dans le descripteur */
        {
            Element *element=initElement(); /*On cree un element */

            element->id=descripteurAux->identifiant; 
            element->nbOccu=getNbOccu(descripteurAux,mot); /*On recupere le nombre d'occurence du mot dans le descripteur */

            ajoutElement(&liste,element);    /*On ajoute le nouvel element a la liste en fonction de son nombre d'occurence */
        }

        descripteurAux=descripteurAux->suivant; /*On passe au descripteur suivant */
    }
    
    for(i=0,aux=liste;i<10 && aux!=NULL;i++,aux=aux->elementSuivant)    /*Tant qu'on a pas depasse 10 ou qu'il n'y a plus d'eements dans la liste */
    {
        strcpy(resultat[i], getChemin(aux->id)); /*On recupere le chemin associe a l'identifiant et on le mets dans le tableau de resultat */
    }
    if (i<10)
    {
        strcpy(resultat[i], "fin");
    }
    
    return resultat; /*On retourne le tableau de resultat */
}