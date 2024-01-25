#include<stdio.h>  /* utilisation des entr�es-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include<string.h>
#include "listes_chaines.h" 
#include "image.h"


// Point set_point(double x, double y)
// {
// 	Point P = {x,y}; return P;
// }

/* cr�er une liste vide */
Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;
	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	if (el==NULL){
		fprintf(stderr,"creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

/* ajouter l'�l�ment e en fin de la liste L, renvoie la liste L modifi�e */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
	Cellule_Liste_Point *el;
	
	el = creer_element_liste_Point(e);
	if (L.taille == 0)
	{
		/* premier �l�ment de la liste */
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv = el;
		L.last = el;
	}
	L.taille++;
	return L;
}

/* suppression de tous les �l�ments de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el=L.first;
	Cellule_Liste_Point *suiv;
	
	while (el) 
	{		
		suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}

/* concat�ne L2 � la suite de L1, renvoie la liste L1 modifi�e */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier �l�ment de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

// Tableau_Point concatener_Tableau_Point(Liste_Point L1, Liste_Point L2)
// {
// 	/* cas o� l'une des deux listes est vide */
// 	if (L1.taille == 0) return L2; 
// 	if (L2.taille == 0) return L1;
	
// 	/* les deux listes sont non vides */
// 	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
// 	L1.last = L2.last;        /* le dernier �l�ment de L1 est celui de L2 */
// 	L1.taille += L2.taille;   /* nouvelle taille pour L1 */

// 	Tableau_Point TP;
// 	TP=sequence_points_liste_vers_tableau(L1);
// 	return TP;
// }

Tableau_Point concatener_Tableau_Point(Tableau_Point L1, Tableau_Point L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;

	Liste_Point L;
	L.first=NULL;
	L.last=NULL;
	L.taille=0;

	for(int i=0;i<L1.taille;i++){
		L=ajouter_element_liste_Point(L,L1.tab[i]);
	}

	for(int j=L1.taille;j<L2.taille;j++){
		L=ajouter_element_liste_Point(L,L2.tab[j-L1.taille]);
	}

	Tableau_Point TP;
	TP.tab=NULL;
	TP.taille=0;
	TP=sequence_points_liste_vers_tableau(L);
	return TP;
}


Liste_Point sequence_tableau_vers_contours(Tableau_Point TP){
	Liste_Point LP;
	LP.first=NULL;
	LP.last=NULL;
	LP.taille=0;

	Point P;
	for(int i=0;i<TP.taille;i++){
		P=set_point(TP.tab[i].x,TP.tab[i].y);
		LP=ajouter_element_liste_Point(LP,P);
		}
	
	return LP;
}

// /* cr�er une s�quence de points sous forme d'un tableau de points 
//    � partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0; /* indice de l'�l�ment dans T.tab */
	Cellule_Liste_Point *el = L.first; /* pointeur sur l'�l�ment dans L */
	while (el) 
	{
		T.tab[k] = el->data;
		k++; /* incr�menter k */
		el = el->suiv; /* passer � l'�lement suivant dans la liste chainee */
	}
	
	return T;
}



