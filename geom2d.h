/****************************************************************************** 
  Interface géométrique en 2 dimensions
******************************************************************************/

#ifndef _GEOM2D_H_
#define _GEOM2D_H_

typedef struct Vecteur {
    double x,y;
} Vecteur;

typedef struct Point {
    double x,y;
} Point;

typedef struct Segment{
    Point A,B;
} Segment;

Point set_point(double x, double y);

Point add_point(Point P1, Point P2);

Point sub_point(Point P1, Point P2);

Point produit_point(Point P1,double a);

Vecteur vect_bipoint(Point A, Point B);

Vecteur add_vecteur(Vecteur V1, Vecteur V2);

Vecteur produit_vecteur(Vecteur V1,double a);

double produit_scalaire(Vecteur V1, Vecteur V2);

double norme (Vecteur V);

double distance (Point P1, Point P2);

void afficher_point (Point P);

void afficher_vecteur (Vecteur V);

Segment creer_segment(Point A, Point B);

double distance_point_segment(Point P, Segment S);

#endif