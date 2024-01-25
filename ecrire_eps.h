#include<stdio.h>  /* utilisation des entr�es-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include<string.h> 
#include "contours.h"
#include "image.h"

void ecrire_eps_stroke(int xmax,int ymax,char **nom,Contour C1);

void ecrire_eps_fill(int xmax,int ymax,char **nom,Contour C1);

void ecrire_eps_stroke_contours(int xmax,int ymax,char **nom,sequence_contours SC);

void ecrire_eps_fill_contours(int xmax,int ymax,char **nom,sequence_contours SC);