#include<stdio.h>  /* utilisation des entr�es-sorties standard de C */
#include<stdlib.h> /* utilisation des fonctions malloc et free */
#include<string.h> 
#include "contours.h"
#include "image.h"
#include "listes_chaines.h"

/*---- le type Point et la fonction set_point ----*/
/* ou inclure le module de la tache 2             */


/* �crire le contour L � l'�cran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acc�der aux �l�ments d'une
   s�quence de points par indice */
void ecrire_contour(Liste_Point L)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	
	printf("%d points : [", nP);
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k]; /* r�cup�rer le point d'indice k */
		printf(" (%5.1f,%5.1f)", P.x, P.y);
	} 
	printf("]\n");
	
	free(TP.tab); /* supprimer le tableau de point TP */
}

Point trouver_pixel_depart (Image I) {
	UINT L = largeur_image(I);
	UINT H = hauteur_image(I);
	for (double y = 0; y <= H; y++) {
		for (double x = 0; x <= L; x++) {
			if (get_pixel_image(I, x, y) == NOIR && get_pixel_image(I, x, y - 1) == BLANC) return set_point(x,y);
		}
	}
	return set_point(0,0);
}

Point avancer (double x, double y, Orientation orient) {
	switch (orient) {
		case Nord : 
			return set_point(x, y-1);
		case Est :
			return set_point(x+1, y);
		case Sud :
			return set_point(x, y+1);
		case Ouest :
			return set_point(x-1, y);
		default :return set_point(x,y);
	}
}

Orientation nouvelle_orientation (Image I, double x, double y, Orientation orient) {
	Pixel pG;
	Pixel pD;
	
	switch (orient) {
		case Nord : 
			pG = get_pixel_image(I, x, y);
			pD = get_pixel_image(I,x+1,y);
			break;
		case Est :
			pG = get_pixel_image(I, x+1, y);
			pD = get_pixel_image(I,x+1,y+1);
			break;
		case Sud :
			pG = get_pixel_image(I, x+1, y+1);
			pD = get_pixel_image(I,x,y+1);
			break;
		case Ouest :
			pG = get_pixel_image(I, x, y+1);
			pD = get_pixel_image(I,x,y);
			break;
		default : return orient;
	}
	

	if (pG==NOIR){
		return (orient - 1)%4;
	}
	else if(pD==BLANC){
		return (orient + 1)%4;
	}
	return orient;
}

void ecrire_contour_fichier(Contour C1, char **nom)
{
	FILE* f = fopen(*nom, "w");
	int nombre_contours=1;

	fprintf(f,"%d\n",nombre_contours); //pour le moment 1

	fprintf(f,"\n%d\n",C1.taille);

	Tableau_Point TP = sequence_points_liste_vers_tableau(C1);
	int k;
	int nP = TP.taille;
	
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k]; /* r�cup�rer le point d'indice k */
		fprintf(f," %2.1f %2.1f \n", P.x, P.y);
	} 
	
	free(TP.tab); /* supprimer le tableau de point TP */
	
}

Liste_Point calcul_contour(Image I, int x, int y){
    double x0,y0;
    x0=x-1;
    y0=y-1;

    Point position=set_point(x0,y0);
	Contour C1;
	C1 = creer_liste_Point_vide();

    Orientation orient=Est;
	bool boucle=true;

    while (boucle){
		C1 = ajouter_element_liste_Point(C1, set_point(position.x,position.y));
		position=avancer(position.x,position.y,orient);
		orient=nouvelle_orientation(I,position.x,position.y,orient);

		if (position.x==x0 && position.y==y0 && orient==Est) 
			boucle=false;

		
    }
	C1 = ajouter_element_liste_Point(C1, set_point(position.x,position.y));
	printf("Nombre de segments =%d\n",C1.taille-1);

	return C1;
}

Image blanchir(Tableau_Point TP,Image I){
	Image masque=I;
	for(int i=0;i<TP.taille;i++){
		set_pixel_image_ameliore(&masque,TP.tab[i].x,TP.tab[i].y,0);
	}
	ecrire_image(masque);
	return masque;
}

Liste_Point calcul_contour_blanchi(Image I,Image *masque){
    double x,y,x0,y0;
    x=trouver_pixel_depart(I).x;
	y=trouver_pixel_depart(I).y;
    x0=x-1;
    y0=y-1;

    Point position=set_point(x0,y0);
	Contour C1;
	C1 = creer_liste_Point_vide();

    Orientation orient=Est;
	bool boucle=true;

    while (boucle){
		C1 = ajouter_element_liste_Point(C1, set_point(position.x,position.y));
		position=avancer(position.x,position.y,orient);
		orient=nouvelle_orientation(I,position.x,position.y,orient);
		

		if (position.x==x0 && position.y==y0 && orient==Est) 
			boucle=false;

    }
	C1 = ajouter_element_liste_Point(C1, set_point(position.x,position.y));
	printf("Nombre de segments =%d\n",C1.taille-1);
	set_pixel_image(*masque,C1.first->data.x,C1.first->data.y,0);
	return C1;
}

void ajout_sequence(sequence_contours *seq, Tableau_Point tab){

    cellule_contours *c = (cellule_contours*)malloc(sizeof(cellule_contours));
	if (c==NULL){
		fprintf(stderr,"ajout_sequence : allocation impossible\n");
		exit(-1);
	}
    c->T = tab;
    c->suiv = NULL;

    cellule_contours *cbouge = seq->tete;
    if (cbouge == NULL) { 
        seq->tete = c; 
        return; 
    	}
    while(cbouge->suiv != NULL){
        cbouge = cbouge->suiv;
    }
    cbouge->suiv = c;
    seq->taille++;
}

void ecrire_tableau_fichier(sequence_contours S, char **nom)
{
	FILE* f = fopen(*nom, "w");
	int nombre_contours=S.taille;

	fprintf(f,"%d\n",nombre_contours); //pour le moment 1

	// fprintf(f,"\n%d\n",C1.taille);
	int k;
	
	
	for(int j=0;j<nombre_contours;j++) {
		Tableau_Point TP=S.tete->T;
		int nP = TP.taille;
		for (k = 0; k < nP; k++)
		{	
			Point P = TP.tab[k]; /* r�cup�rer le point d'indice k */
			fprintf(f," %2.1f %2.1f \n", P.x, P.y);
		} 
		S.tete=S.tete->suiv;
	}
	// free(TP.tab); /* supprimer le tableau de point TP */
	
}

sequence_contours extraire_contours (Image I){
	Image masque = calculer_masque_image (I);
	Point P = trouver_pixel_depart (masque);
	Tableau_Point TP;
	Liste_Point LP;
	sequence_contours SC;
	SC.taille=0;
	SC.tete=NULL;
	int i =0;
	ecrire_image(masque);
	while (get_pixel_image(I,P.x,P.y) != 0 && i < 1) {
		LP=calcul_contour_blanchi(I,&masque);  
		ecrire_image(masque);
		TP=sequence_points_liste_vers_tableau(LP);
		// int w = 0;
		// while (w < TP.taille) {
		// 	printf("x:%f et y:%f\n",TP.tab[w].x,TP.tab[w].y);
		// 	w++;
		// }
		// masque=blanchir(TP,masque);
		// ecrire_image(masque);
		ajout_sequence(&SC, TP);							//A finir
		P = trouver_pixel_depart (masque);
		//printf("Point de depart:%f,%f\n",P.x,P.y);
		i++;
	}
	return SC;
}

void update_masque(Image* masque, int x, int y, Orientation orient)
{
	if (orient == Est)
    	set_pixel_image(*masque, x + 1, y + 1, 0);
}



Contour  parcourir_image2(Image I, Image* masque, int x, int y){
    Contour contour_ret = creer_liste_Point_vide();
    Point tempPoint ;
    
	Point position=set_point(x,y);
    int k = 0;
	Orientation orient=Est;
    short loop = 1 ;
    while (loop) {

        
        update_masque(masque,position.x,position.y,orient);

        
        tempPoint = set_point(position.x, position.y) ;
        contour_ret = ajouter_element_liste_Point(contour_ret, tempPoint) ;
        position=avancer(position.x,position.y,orient);
        orient=nouvelle_orientation(I,position.x,position.y,orient);
        if (position.x == x && position.y == y && orient == Est) {
            tempPoint = set_point(position.x, position.y) ;
            contour_ret = ajouter_element_liste_Point(contour_ret, tempPoint) ;
            loop = 0 ;        
        }
        k++;
    }
    return contour_ret ;
}

int blanc(Image I){
	int res=0;
	for(int i=0;i<I.H;i++){
		for(int j=0;j<I.L;j++){
			res+=get_pixel_image(I,j,i);
		}
	}
	return res;
}

sequence_contours boucle_parcourir_image(Image I){
	Contour C;
	C.first=NULL;
	C.last=NULL;
	C.taille=0;
	
	sequence_contours SC;
	SC.tete = NULL;
	SC.taille = 0;

    Image masque=calculer_masque_image(I);
    Point P=trouver_pixel_depart(masque);

	Tableau_Point TP;
	TP.tab=NULL;
	TP.taille=0;

	int i=0;
	while (P.x != 0 || P.y != 0 || get_pixel_image(I, 0, 0) == 1){
	// while (blanc(masque) != 0){
		// ecrire_image(masque);
		// printf("\n");
		C=parcourir_image2(I, &masque, P.x-1, P.y-1);
		TP = sequence_points_liste_vers_tableau(C);
		C=supprimer_liste_Point(C);
		ajout_sequence(&SC, TP);	
		P=trouver_pixel_depart(masque);
		i++;
	}
	//ecrire_image(masque);
	// //printf("\n");
	// C=parcourir_image2(I, &masque, P.x-1, P.y-1);
	TP = sequence_points_liste_vers_tableau(C);
	C=supprimer_liste_Point(C);
	ajout_sequence(&SC, TP);
	free(masque.tab);
	
	return SC;
}

Tableau_Point supprimer_tableau_Point(Tableau_Point L)
{
	//if (L.tab!=NULL) 
		//free(L.tab);
	Tableau_Point TP;
	TP.tab = NULL; TP.taille = 0;
	return TP;
}


int nombre_segments(sequence_contours SC){
	int nombre_contours=SC.taille;
	cellule_contours *voyage = SC.tete;
	int nP = voyage->T.taille;
	int nombre_segments=0;
	for (int i = 0; i < nombre_contours; i++) {

		nP = voyage->T.taille;
		nombre_segments+=nP;
		if(voyage->suiv==NULL)break;
		voyage = voyage->suiv;
	}
	return nombre_segments;
}

void ecrire_contours_fichier(sequence_contours SC, char **nom)
{
	FILE* f = fopen(*nom, "w");
	int nombre_contours = SC.taille;
	cellule_contours *voyage = SC.tete;

	fprintf(f,"%d\n",nombre_contours); 

	Tableau_Point TP = voyage->T;
	
	int k;
	int nP = TP.taille;
	for (int i = 0; i < nombre_contours; i++) {

		nP = TP.taille;

		fprintf(f,"\n%d\n",voyage->T.taille);

		for (k = 0; k < nP; k++)
		{	
			Point P = TP.tab[k]; /* r�cup�rer le point d'indice k */
			fprintf(f," %2.1f %2.1f \n", P.x, P.y);
		} 

		voyage=voyage->suiv;
		TP = voyage->T;
	}
}

sequence_contours supprimer_sequence_contours(sequence_contours SC)
{
	cellule_contours *el=SC.tete;
	
	while (el) 
	{		
		
		cellule_contours *temp=el->suiv;
		free(el->T.tab);
		free(el);
		el = temp;
	}
	// if(el->T.tab!=NULL){
	// 	free(el->T.tab);
	// 	}
	SC.tete=NULL; SC.taille=0;
	return SC;
}