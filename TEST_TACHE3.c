#include<stdio.h>  /* utilisation des entr�es-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include<string.h>
#include "image.h"
#include "contours.h"
#include "ecrire_eps.h"
#include "listes_chaines.h"

int main (int argc, char** argv) {
    Image I=lire_fichier_image(argv[1]);
    sequence_contours SC = boucle_parcourir_image(I);
    char *nom =strtok(argv[1],".");
	strcat(nom,".contour");
    ecrire_contours_fichier(SC, &nom);
    
    nom=strtok(argv[1],".");
	strcat(nom,".eps");
    ecrire_eps_fill_contours(I.L,I.H,&nom,SC);
    return 0;
}
