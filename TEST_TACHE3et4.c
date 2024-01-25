#include<stdio.h>  /* utilisation des entr�es-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include<string.h> 
#include "image.h"
#include "contours.h"
#include "listes_chaines.h"
#include "ecrire_eps.h"
/*---- le type Point et la fonction set_point ----*/
/* ou inclure le module de la tache 2             */

int main(int argc,char **argv){
	Image I=lire_fichier_image(argv[1]);
	Point p=trouver_pixel_depart(I);
	printf("Point depart de %s, x:%f et y%f \n",argv[1],p.x,p.y);
	
	Contour C1=calcul_contour(I);
	char *nom=strtok(argv[1],".");
	strcat(nom,".contour");
	printf("%s\n",nom);
	ecrire_contour_fichier(C1,&nom);
	nom=strtok(argv[1],".");
	strcat(nom,".eps");
	printf("%s\n",nom);
	ecrire_eps_fill(I.L,I.H,&nom,C1);
} // fin du programme
