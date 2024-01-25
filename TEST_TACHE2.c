#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "geom2d.h"

int main(){
    Point A, B ,C; Vecteur U, V;
    A = set_point (1.0, -3.0);
    printf("A:");
    afficher_point (A);
    B = set_point (4.0, 1.0);
    printf("B:");
    afficher_point (B);
    C = add_point (A,B);
    printf("C:");
    afficher_point (C);
    U = vect_bipoint (C,A);
    printf("U:");
    afficher_vecteur (U);
    V = vect_bipoint (B,A);
    printf("V:");
    afficher_vecteur (V);
    Point P = produit_point (A, 5);
    printf("P:");
    afficher_point (P);
    double ps = produit_scalaire (U,V);
    double n = norme (U);
    double d = distance (A,C);
    printf("ps:%f \nn:%f \nd:%f\n",ps,n,d);
}