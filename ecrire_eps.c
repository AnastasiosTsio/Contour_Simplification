#include<stdio.h>  /* utilisation des entr�es-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include<string.h> 
#include "contours.h"
#include "image.h"

void ecrire_eps_stroke(int xmax,int ymax,char **nom,Contour C1){
	FILE *f=fopen(*nom,"w");
	Cellule_Liste_Point *el=C1.first;

	fprintf(f,"%%!PS-Adobe-3.O EPSF-3.0\n%%%%BoundingBox: 0 0 %d %d\n/l {lineto} def\n/m {moveto} def\n/s {stroke} def\n",xmax,ymax);
	if(el->suiv)
		fprintf(f,"%f %f m %f %f l\n",el->data.x, ymax-el->data.y,el->suiv->data.x,ymax-el->suiv->data.y);
	el=el->suiv->suiv;
	while (el->suiv){
		fprintf(f,"%f %f l ",el->data.x, ymax-el->data.y);
		el=el->suiv;
	}
	fprintf(f,"%f %f l ",el->data.x, ymax-el->data.y);
	fprintf(f,"\n0.1 setlinewidth s\n");
	fprintf(f,"\nshowpage\n");
}

void ecrire_eps_fill(int xmax,int ymax,char **nom,Contour C1){
	FILE *f=fopen(*nom,"w");
	Cellule_Liste_Point *el=C1.first;

	fprintf(f,"%%!PS-Adobe-3.O EPSF-3.0\n%%BoundingBox: 0 0 %d %d\n/l {lineto} def\n/m {moveto} def\n/f {fill} def\n",xmax,ymax);
	if(el->suiv)
		fprintf(f,"%f %f m %f %f l\n",el->data.x, ymax-el->data.y,el->suiv->data.x,ymax-el->suiv->data.y);
	el=el->suiv->suiv;
	while (el->suiv){
		fprintf(f,"%f %f l ",el->data.x, ymax-el->data.y);
		el=el->suiv;
	}
	fprintf(f,"%f %f l ",el->data.x, ymax-el->data.y);
	fprintf(f,"\n0.1 setlinewidth f\n");
	fprintf(f,"\nshowpage\n");
}


void ecrire_eps_stroke_contours(int xmax,int ymax,char **nom,sequence_contours SC){
	FILE *f=fopen(*nom,"w");
	int nombre_contours=SC.taille;
	Tableau_Point TP=SC.tete->T;
	Point P;

	fprintf(f,"%%!PS-Adobe-3.O EPSF-3.0\n%%%%BoundingBox: 0 0 %d %d\n/l {lineto} def\n/m {moveto} def\n/s {stroke} def\n",xmax,ymax);

	for (int j=0;j<nombre_contours;j++){
		fprintf(f,"%f %f m %f %f l\n",TP.tab[TP.taille-1].x, ymax-TP.tab[TP.taille-1].y,TP.tab[1].x,ymax-TP.tab[1].y);
		//
		for(int i=2;i<TP.taille;i++){
			P=TP.tab[i];
			fprintf(f,"%f %f l ",P.x, ymax-P.y);
		}
		fprintf(f,"\n\n");
		SC.tete=SC.tete->suiv;
		TP=SC.tete->T;
	}
	fprintf(f,"\n0.1 setlinewidth s\n");
	fprintf(f,"\nshowpage\n");
}

// void ecrire_eps_fill_contours(int xmax,int ymax,char **nom,sequence_contours SC){
// 	FILE *f=fopen(*nom,"w");
// 	int nombre_contours=SC.taille;
// 	Tableau_Point TP=SC.tete->T;
// 	Point P;

// 	fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n%%%%BoundingBox: 0 0 %d %d\n/l {lineto} def\n/m {moveto} def\n/f {fill} def\n",xmax,ymax);

// 	for (int j=0;j<nombre_contours;j++){
// 		fprintf(f,"%f %f m %f %f l\n",TP.tab[TP.taille-1].x, ymax-TP.tab[TP.taille-1].y,TP.tab[1].x,ymax-TP.tab[1].y);
// 		for(int i=2;i<TP.taille;i++){
// 			P=TP.tab[i];
// 			fprintf(f,"%f %f l ",P.x, ymax-P.y);
// 			}
// 		fprintf(f,"\n\n");
// 		SC.tete=SC.tete->suiv;
// 		TP=SC.tete->T;
// 	}
// 	fprintf(f,"\n0.1 setlinewidth f\n");
// 	fprintf(f,"\nshowpage\n");
//}

void ecrire_eps_fill_contours(int xmax,int ymax,char **nom,sequence_contours SC)
{
	FILE* f = fopen(*nom, "w");
	int nombre_contours=SC.taille;
	cellule_contours *voyage = SC.tete;

	fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n%%%%BoundingBox: 0 0 %d %d\n/l {lineto} def\n/m {moveto} def\n/f {fill} def\n",xmax,ymax);

	Tableau_Point TP = voyage->T;
	
	int k;
	int nP = TP.taille;
	int nombre_segments=0;
	for (int i = 0; i < nombre_contours; i++) {

		nP = TP.taille;
		nombre_segments+=nP;
		Point P = set_point(TP.tab[0].x,TP.tab[0].y);
 		Point P1 = set_point(TP.tab[1].x,TP.tab[1].y);
		fprintf(f,"%f %f m %f %f l\n",P.x, ymax-P.y,P1.x,ymax-P1.y);
		for (k = 2; k < nP; k++)
		{	
			P = set_point(TP.tab[k].x,TP.tab[k].y); 
			fprintf(f," %2.1f %2.1f l ", P.x, ymax-P.y);
		} 
		fprintf(f,"\n\n");
		if(voyage->suiv==NULL)break;
		voyage=voyage->suiv;
		TP = voyage->T;
	}
	// printf("Nombre de segments:%d\n",nombre_segments/2);
	fprintf(f,"\n0.1 setlinewidth f\n");
 	fprintf(f,"\nshowpage\n");
	// free(TP.tab); /* supprimer le tableau de point TP */
}