#ifndef _CONTOURS_H_
#define _CONTOURS_H_

#include<stdio.h>  /* utilisation des entr�es-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include<string.h> 
#include "image.h"
#include "listes_chaines.h"

/*---- le type Point et la fonction set_point ----*/
/* ou inclure le module de la tache 2             */

typedef struct cellule_contours{
   Tableau_Point T;
   struct cellule_contours *suiv;
}cellule_contours;

typedef struct sequence_contours{
   int taille;
   cellule_contours *tete;
}sequence_contours;

/* �crire le contour L � l'�cran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acc�der aux �l�ments d'une
   s�quence de points par indice */
void ecrire_contour(Liste_Point L);

Point trouver_pixel_depart (Image I) ;

Point avancer (double x, double y, Orientation orient);

Orientation nouvelle_orientation (Image I, double x, double y, Orientation orient);

void ecrire_contour_fichier(Contour C1, char **nom);

Liste_Point calcul_contour(Image I, int x, int y);

Image blanchir(Tableau_Point TP,Image I);

void ajout_sequence(sequence_contours *seq, Tableau_Point tab);

void ecrire_tableau_fichier(sequence_contours S, char **nom);

sequence_contours extraire_contours (Image I);

int nombre_segments(sequence_contours SC);

int blanc(Image I);

void update_masque(Image* masque, int x, int y, Orientation orient); 

Contour parcourir_image2(Image I, Image* masque, int x, int y);

sequence_contours boucle_parcourir_image(Image I);

void ecrire_contours_fichier(sequence_contours SC, char **nom);

sequence_contours supprimer_sequence_contours(sequence_contours SC);

Tableau_Point supprimer_tableau_Point(Tableau_Point L);

#endif




