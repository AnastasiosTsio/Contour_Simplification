#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"

int main(){
    Image A,Aneg;
    printf("Poisitof\n");
    A = creer_image(4,2);
    set_pixel_image(A,3,1, NOIR);
    set_pixel_image(A,2,2, NOIR);
    set_pixel_image(A,4,2, NOIR);
    ecrire_image(A);

    printf("Negatof\n");
    Aneg=negatif_image(A);
    ecrire_image(Aneg);

    supprimer_image(&A);
    supprimer_image(&Aneg);
    return 0;
}