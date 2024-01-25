#include<stdio.h>  
#include<stdlib.h> 
#include<string.h>
#include<math.h>
#include "image.h"
#include "geom2d.h"
#include "contours.h"
#include "simplification.h"
#include "ecrire_eps.h"

int main (int argc,char **argv) {

    Image I = lire_fichier_image(argv[1]);
    printf("Ouverture du fichier:%s\n",argv[1]);
    sequence_contours SC = boucle_parcourir_image(I);
    printf("Nombre de contours: %d\n",SC.taille);
    int n=nombre_segments(SC);
    printf("Nombre de segments au debut: %d\n",n);
    
    sequence_contours simp=simplification_contours(SC,1);
    n=nombre_segments(simp)/2;
    printf("Nombre de segments avec d=1: %d\n",n);
    

    sequence_contours SC2 = boucle_parcourir_image(I);
    sequence_contours simp2=simplification_contours(SC2,2);
    n=nombre_segments(simp2)/2;
    printf("Nombre de segments avec d=2: %d\n",n);
    // simp2=supprimer_sequence_contours(simp2);

    char *nom=argv[1];
    nom[strlen(nom)-4]='\0';
	strcat(nom,".contour");
    printf("\nCreation du fichier%s\n",nom);
    ecrire_contours_fichier(SC,&nom);

    nom=argv[1];
    nom[strlen(nom)-8]='\0';
	strcat(nom,"_1.eps");
    printf("Creation du fichier%s\n",nom);
    ecrire_eps_fill_contours(I.L,I.H,&nom,simp);

    nom=argv[1];
    nom[strlen(nom)-6]='\0';
	strcat(nom,"_2.eps");
    printf("Creation du fichier:%s\n",nom);
    ecrire_eps_fill_contours(I.L,I.H,&nom,simp2);
    

    SC=supprimer_sequence_contours(SC);
    SC2=supprimer_sequence_contours(SC2);
    simp=supprimer_sequence_contours(simp);
    simp2=supprimer_sequence_contours(simp2);
    free(I.tab);
    return 0;
}
