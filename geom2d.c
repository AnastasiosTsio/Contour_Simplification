#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "geom2d.h"

Point set_point(double x, double y) {
    Point P = {x,y};
    return P;
}

Point add_point(Point P1, Point P2) {
    return set_point(P1.x+P2.x,P1.y+P2.y);
}

Point sub_point(Point P1, Point P2) {
    return set_point(P1.x-P2.x,P1.y-P2.y);
}

Point produit_point(Point P1, double a) {
    return set_point(P1.x*a,P1.y*a);
}

Vecteur vect_bipoint(Point A, Point B) {
    Vecteur V = {B.x-A.x,B.y-A.y};
    return V;
}

Vecteur add_vecteur (Vecteur V1, Vecteur V2) {
    Vecteur V={V1.x+V2.x,V1.y+V2.y};
    return V;
}

Vecteur produit_vecteur (Vecteur V1, double a) {
    Vecteur V={V1.x*a,V1.y*a};
    return V;
}

double produit_scalaire (Vecteur V1, Vecteur V2) {
    return V1.x*V2.x+V1.y*V2.y;
}

double norme (Vecteur V){
    return sqrt(V.x*V.x+V.y*V.y);
}

double distance (Point P1, Point P2) {
    return sqrt(pow(P1.x-P2.x,2)+pow(P1.y-P2.y,2));
}

void afficher_point (Point P) {
    printf("Le point a pour coordonnées : %f, %f\n", P.x, P.y);
}

void afficher_vecteur (Vecteur V) {
    printf("Le vecteur a pour coordonnées : %f, %f\n", V.x, V.y);
}

Segment creer_segment(Point A, Point B){
    Segment S;
    S.A=A;
    S.B=B; 
    return S;
}

double distance_point_segment(Point P, Segment S){
    Vecteur AP = vect_bipoint(S.A, P);
    Vecteur AB = vect_bipoint(S.A, S.B);
    Vecteur BP = vect_bipoint(S.B, P);
    double dp = -1;
    if (S.A.x == S.B.x && S.A.y == S.B.y) return norme(AP);
    double l = produit_scalaire(AP, AB)/produit_scalaire(AB,AB);
    if (l < 0) {
        dp = norme(AP);
    } else if (l > 1) {
        dp = norme(BP);
    } else {
        Point Q = add_point(S.A, produit_point(sub_point(S.B,S.A), l));
        Vecteur QP = vect_bipoint(Q, P);
        dp = norme(QP);
    }
    return dp;
}