#include<stdio.h>  
#include<stdlib.h> 
#include<string.h>
#include<math.h>
#include "geom2d.h"
#include "image.h"
#include "contours.h"
#include "listes_chaines.h"

Contour simplification_douglas_peucker (Contour C,int j1,int j2,float d){
    Tableau_Point TP=sequence_points_liste_vers_tableau(C);
    Segment S=creer_segment(TP.tab[j1],TP.tab[j2]);
    Contour L;
    L.first=NULL;
    L.taille=0;
    L.last=NULL;

    double dmax=0;
    int k=j1;

    for(int j=k+1;j<j2;j++){
        double dj=distance_point_segment(TP.tab[j],S);
        if (dmax<dj){
            dmax=dj;
            k=j;
        }
    }
    if (dmax<=d){
        L=ajouter_element_liste_Point(L,S.A);
        L=ajouter_element_liste_Point(L,S.B);
    }else{
        Contour C1=simplification_douglas_peucker(C,j1,k,d);
        Contour C2=simplification_douglas_peucker(C,k,j2,d);
        L=concatener_liste_Point(C1,C2);
    }
    free(TP.tab);
    return L;
}

sequence_contours simplification_contours(sequence_contours SC,float d){

    if(SC.tete==NULL)return SC;

    sequence_contours res;
    res.taille=0;
    res.tete=NULL;

    cellule_contours *voyage=SC.tete;

    Tableau_Point TP=voyage->T;

    for(int i=0;i<SC.taille;i++){
        // printf("i:%d && SC.taille:%d\n",i,SC.taille);

        Contour L=sequence_tableau_vers_contours(TP);
        Contour L2;
        L2=simplification_douglas_peucker(L,0,L.taille-1,d);
        supprimer_liste_Point(L);
        Tableau_Point TP2=sequence_points_liste_vers_tableau(L2);
        supprimer_liste_Point(L2);
        ajout_sequence(&res,TP2);
        res.taille++;
        voyage=voyage->suiv;
        TP=voyage->T;
    }

    // free(voyage);
    //supprimer_sequence_contours(SC);
    // printf("Simp taille:%d, 0x:%f, 0y:%f\n",res.taille,res.tete->T.tab[0].x,res.tete->T.tab[0].y);
    return res;
}
