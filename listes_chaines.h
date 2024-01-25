#ifndef _LISTES_CHAINES_H_
#define _LISTES_CHAINES_H_

#include<stdio.h>  /* utilisation des entr�es-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include<string.h> 
#include "geom2d.h"
#include "image.h"


//typedef struct Point_ { double x,y; } Point;

//Point set_point(double x, double y);

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
	Point data;    /* donn�e de l'�l�ment de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'�l�ment suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;        /* nombre d'�l�ments dans la liste */
	Cellule_Liste_Point *first; /* pointeur sur le premier �l�ment de la liste */
	Cellule_Liste_Point *last;  /* pointeur sur le dernier �l�ment de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
	unsigned int taille; /* nombre d'�l�ments dans le tableau */
	Point *tab;          /* (pointeur vers) le tableau des �l�ments */
} Tableau_Point;

typedef enum {Nord, Est, Sud, Ouest} Orientation;


/* cr�er une cellule de liste avec l'�l�ment v 
   renvoie le pointeur sur la cellule de liste cr��e
   la fonction s'arrete si la cr�ation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v);
/* cr�er une liste vide */
Liste_Point creer_liste_Point_vide();

/* ajouter l'�l�ment e en fin de la liste L, renvoie la liste L modifi�e */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

/* suppression de tous les �l�ments de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L);

/* concat�ne L2 � la suite de L1, renvoie la liste L1 modifi�e */

Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);
/* cr�er une s�quence de points sous forme d'un tableau de points 
   � partir de la liste de points L */
Liste_Point sequence_tableau_vers_contours(Tableau_Point TP);

Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

Tableau_Point concatener_Tableau_Point(Tableau_Point L1, Tableau_Point L2);

#endif
