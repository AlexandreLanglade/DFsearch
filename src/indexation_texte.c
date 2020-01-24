#include "../include/indexation_texte.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

/*Liste des mots vides */
char *stoplist[689]={"a","abord","absolument","afin","ah","ai","aie","aient","aies","ailleurs","ainsi","ait","allaient","allo","allons","allô","alors","anterieur","anterieure","anterieures","apres","après","as","assez","attendu","au","aucun","aucune","aucuns","aujourd","aujourd'hui","aupres","auquel","aura","aurai","auraient","aurais","aurait","auras","aurez","auriez","aurions","aurons","auront","aussi","autre","autrefois","autrement","autres","autrui","aux","auxquelles","auxquels","avaient","avais","avait","avant","avec","avez","aviez","avions","avoir","avons","ayant","ayez","ayons","b","bah","bas","basee","bat","beau","beaucoup","bien","bigre","bon","boum","bravo","brrr","c","car","ce","ceci","cela","celle","celle-ci","celle-là","celles","celles-ci","celles-là","celui","celui-ci","celui-là","celà","cent","cependant","certain","certaine","certaines","certains","certes","ces","cet","cette","ceux","ceux-ci","ceux-là","chacun","chacune","chaque","cher","chers","chez","chiche","chut","chère","chères","ci","cinq","cinquantaine","cinquante","cinquantième","cinquième","clac","clic","combien","comme","comment","comparable","comparables","compris","concernant","contre","couic","crac","d","da","dans","de","debout","dedans","dehors","deja","delà","depuis","dernier","derniere","derriere","derrière","des","desormais","desquelles","desquels","dessous","dessus","deux","deuxième","deuxièmement","devant","devers","devra","devrait","different","differentes","differents","différent","différente","différentes","différents","dire","directe","directement","dit","dite","dits","divers","diverse","diverses","dix","dix-huit","dix-neuf","dix-sept","dixième","doit","doivent","donc","dont","dos","douze","douzième","dring","droite","du","duquel","durant","dès","début","désormais","e","effet","egale","egalement","egales","eh","elle","elle-même","elles","elles-mêmes","en","encore","enfin","entre","envers","environ","es","essai","est","et","etant","etc","etre","eu","eue","eues","euh","eurent","eus","eusse","eussent","eusses","eussiez","eussions","eut","eux","eux-mêmes","exactement","excepté","extenso","exterieur","eûmes","eût","eûtes","f","fais","faisaient","faisant","fait","faites","façon","feront","fi","flac","floc","fois","font","force","furent","fus","fusse","fussent","fusses","fussiez","fussions","fut","fûmes","fût","fûtes","g","gens","h","ha","haut","hein","hem","hep","hi","ho","holà","hop","hormis","hors","hou","houp","hue","hui","huit","huitième","hum","hurrah","hé","hélas","i","ici","il","ils","importe","j","je","jusqu","jusque","juste","k","l","la","laisser","laquelle","las","le","lequel","les","lesquelles","lesquels","leur","leurs","longtemps","lors","lorsque","lui","lui-meme","lui-même","là","lès","m","ma","maint","maintenant","mais","malgre","malgré","maximale","me","meme","memes","merci","mes","mien","mienne","miennes","miens","mille","mince","mine","minimale","moi","moi-meme","moi-même","moindres","moins","mon","mot","moyennant","multiple","multiples","même","mêmes","n","na","naturel","naturelle","naturelles","ne","neanmoins","necessaire","necessairement","neuf","neuvième","ni","nombreuses","nombreux","nommés","non","nos","notamment","notre","nous","nous-mêmes","nouveau","nouveaux","nul","néanmoins","nôtre","nôtres","o","oh","ohé","ollé","olé","on","ont","onze","onzième","ore","ou","ouf","ouias","oust","ouste","outre","ouvert","ouverte","ouverts","o|","où","p","paf","pan","par","parce","parfois","parle","parlent","parler","parmi","parole","parseme","partant","particulier","particulière","particulièrement","pas","passé","pendant","pense","permet","personne","personnes","peu","peut","peuvent","peux","pff","pfft","pfut","pif","pire","pièce","plein","plouf","plupart","plus","plusieurs","plutôt","possessif","possessifs","possible","possibles","pouah","pour","pourquoi","pourrais","pourrait","pouvait","prealable","precisement","premier","première","premièrement","pres","probable","probante","procedant","proche","près","psitt","pu","puis","puisque","pur","pure","q","qu","quand","quant","quant-à-soi","quanta","quarante","quatorze","quatre","quatre-vingt","quatrième","quatrièmement","que","quel","quelconque","quelle","quelles","quelqu'un","quelque","quelques","quels","qui","quiconque","quinze","quoi","quoique","r","rare","rarement","rares","relative","relativement","remarquable","rend","rendre","restant","reste","restent","restrictif","retour","revoici","revoilà","rien","s","sa","sacrebleu","sait","sans","sapristi","sauf","se","sein","seize","selon","semblable","semblaient","semble","semblent","sent","sept","septième","sera","serai","seraient","serais","serait","seras","serez","seriez","serions","serons","seront","ses","seul","seule","seulement","si","sien","sienne","siennes","siens","sinon","six","sixième","soi","soi-même","soient","sois","soit","soixante","sommes","son","sont","sous","souvent","soyez","soyons","specifique","specifiques","speculatif","stop","strictement","subtiles","suffisant","suffisante","suffit","suis","suit","suivant","suivante","suivantes","suivants","suivre","sujet","superpose","sur","surtout","t","ta","tac","tandis","tant","tardive","te","tel","telle","tellement","telles","tels","tenant","tend","tenir","tente","tes","tic","tien","tienne","tiennes","tiens","toc","toi","toi-même","ton","touchant","toujours","tous","tout","toute","toutefois","toutes","treize","trente","tres","trois","troisième","troisièmement","trop","très","tsoin","tsouin","tu","té","u","un","une","unes","uniformement","unique","uniques","uns","v","va","vais","valeur","vas","vers","via","vif","vifs","vingt","vivat","vive","vives","vlan","voici","voie","voient","voilà","vont","vos","votre","vous","vous-mêmes","vu","vé","vôtre","vôtres","w","x","y","z","zut","à","â","ça","ès","étaient","étais","était","étant","état","étiez","étions","été","étée","étées","étés","êtes","être","ô"};

/*Permet de savoir si un mot est un mot outil grâce à la stoplist */
int isMotOutil(char *mot)
{
    int isOutil =0, compteur=0;

    while (isOutil!=1 && compteur<689)
    {
        if(strcmp(mot,stoplist[compteur])==0)
        {
            isOutil=1;
        }

        compteur++;
    }
    

    return isOutil;
}

/*Prend le fichier retranscription et crée un fichier retranscriptionTri qui est un fichier sans mot outil */
void tri()
{
    char mot[200];

    FILE *F=fopen("titi.txt","r");
    FILE *F2=fopen("retranscriptionTri.txt","w");
    assert(F!=NULL && F2!=NULL);

    fprintf(F2," ");

    
    while(!feof(F))
    {
        if(fscanf(F,"%s",mot)==1)
        {
            if(isMotOutil(mot)==0)
            {
                fprintf(F2,"%s ",mot);
            }
        }
    }
    
    fclose(F);
    fclose(F2);

}

/*--------------------------------------------------------------------------------------------------------------------------------------------------*/

/*Permet de retranscrire le fichier .xml dont le chemin est passé en paramètres dans le fichier retranscriptionTri.txt en enlevant les balises, les mots outils, les s en fin de mot et de transformer les majuscules en minuscules */
void deleteBalises(char *chemin)
{
    char commande[200] = "iconv -f 'ISO-8859-1' -t 'UTF8' ";
    strcat(commande,chemin); 
    strcat(commande," > tata.txt"); 
    system(commande);


    /*On enleve toutes les balises */
    system("sed -i '1d' tata.txt ");
    system("sed -i 's/<[\\/]*phrase>//g' tata.txt");
    system("sed -i 's/<[\\/]*texte>//g' tata.txt");
    system("sed -i 's/<[\\/]*auteur>//g' tata.txt");
    system("sed -i 's/<[\\/]*resume>//g' tata.txt");
    system("sed -i 's/<[\\/]*article>//g' tata.txt");
    system("sed -i 's/<[\\/]*date>//g' tata.txt");
    system("sed -i 's/<[\\/]*titre>//g' tata.txt");



    /*On enleve tous les caracteres speciaux */
    system("sed -i 's/\\./ /g' tata.txt");
    system("sed -i 's/\\-/ /g' tata.txt");
    system("sed -i 's/\\,/ /g' tata.txt");
    system("sed -i 's/\\:/ /g' tata.txt");
    system("sed -i 's/\\?/ /g' tata.txt");
    system("sed -i 's/\\;/ /g' tata.txt");
    system("sed -i \"s/'/ /g\" tata.txt");
    system("sed -i 's/\\\"/ /g' tata.txt");
    system("sed -i 's/(//g' tata.txt");
    system("sed -i 's/)//g' tata.txt");
    system("sed -i 's/\\%/ /g' tata.txt");
    system("sed -i 's/[0123456789]/ /g' tata.txt");


    system("cat tata.txt |tr  A-Z a-z > titi.txt"); /*On transforme les majuscules en minuscules */


    tri(); /*On enleve les mots outils et on cree retranscriptionTri.txt */
    system("sed -i 's/s / /g' retranscriptionTri.txt"); /*pernet d'enlever tous les s en fin de mot */

    system("rm tata.txt");
    system("rm titi.txt");
   
}

/*Permet de supprimer un mot dans le fichier retranscriptionTri.txt */
void deletemot(char *mot)
{
    char commande[100]="sed -i 's/";
    strcat(commande,mot);
    strcat(commande,"//' retranscriptionTri.txt");

    system(commande);
}

/*Permet d'avoir le nombre d'occurences d'un mot */
int nbOccurence(char *mot)
{
    FILE * f;
    int nboccu=0;
    char commande[200]="grep -o '";
    strcat(commande,mot);
    strcat(commande," ' retranscriptionTri.txt | wc -l > miljyjp");
    system(commande);
    f = fopen("miljyjp", "r");
    fscanf(f,"%d",&nboccu);
    fclose(f);
    system("rm miljyjp");

    return nboccu;
}

/*Retourne le nombre de mots dans retranscriptionTri.txt */
int nombreMots()
{
    FILE *f;
    int nombreMots;
    system("wc -w retranscriptionTri.txt > afgaegreg");
    f = fopen("afgaegreg","r");
    fscanf(f,"%d",&nombreMots);
    fclose(f);
    system("rm afgaegreg");
    return nombreMots;
}

/*enleve le dernier terme de la liste */
void deleteLast(Descripteur_texte descripteur)
{
    Terme *aux = descripteur->listeDesTermes;
    Terme *aux2;
    
    if(aux != NULL)
    {
        while(aux->termeSuivant->termeSuivant != NULL)
        {
            aux = aux->termeSuivant;
        }
        aux2 = aux->termeSuivant->termeSuivant;
        aux->termeSuivant=NULL;
        free(aux2);
    }
}

/*Indexation d'un fichier texte */
int getId(Pile pile)
{
    Descripteur_texte descripteur;

    if(estVide_pile(pile))
    {
        return 1;
    }
    else
    {
        descripteur = (Descripteur_texte)top_pile(pile,1);
        return descripteur->identifiant + 1;
    }
    
}


void index_un_texte(char *chemin, Pile pile)
{
    int seuil, valeurLimite;
    char * motLu;
    Descripteur_texte descripteur; 
    Terme *aux2;
    FILE *f=NULL, *f2=NULL;

    aux2=init_Terme();
    
    deleteBalises(chemin);
    descripteur=init_DescripteurTexte(); 
    descripteur->nbMots = nombreMots();
    descripteur->identifiant= getId(pile);

    aux2 = descripteur->listeDesTermes;     

    /*Recuperation de la configuration */
    seuil = getConfig_texte_Seuil();
    valeurLimite = getConfig_texte_ValeurLimite();
     
    motLu = (char*)malloc(200*sizeof(char));
    f=fopen("retranscriptionTri.txt","r");

    while (fscanf(f,"%s",motLu)==1)
    {
        
        
        if (!isMotExistant(descripteur,motLu))
        {
            Terme *terme;
            terme = init_Terme();
            
            terme->mot=motLu;
            terme->nbOccurences=nbOccurence(motLu);

            ajout_terme(descripteur,terme);
        }
        motLu = (char*)malloc(200*sizeof(char));
    }
    fclose(f);
 
    deleteLast(descripteur); /*Supprime le dernier terme du descripteur qui est ajoute en plus */

    /*Permet de supprimer les termes dont le nombre d'occurences est en dessous du seuil */
    aux2=descripteur->listeDesTermes; 
    if(seuil != -1)
    {
        while(aux2 != NULL && aux2->nbOccurences < seuil)
        {
            deleteTerme(descripteur);
            aux2=aux2->termeSuivant;
        }
    }

    /*Permet de supprimer les termes pour avoir un nombre inferieur ou egal a la valeur limite */
    if(valeurLimite != -1)
    {
        while (descripteur->nbTermes > valeurLimite)
        {
            deleteTerme(descripteur);
        }
    }

    empiler_pile(pile,descripteur,1);

    system("rm retranscriptionTri.txt");

    f2=fopen("../data/links_txt","a");
    fprintf(f2,"%d %s \n",descripteur->identifiant,chemin);
    fclose(f2);
}
