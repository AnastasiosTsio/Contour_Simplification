#ifndef _SIMPLIFICATION_H_
#define _SIMPLIFICATION_H_

#include<stdio.h>  
#include<stdlib.h> 
#include<string.h>
#include<math.h>
#include "geom2d.h"
#include "image.h"
#include "contours.h"
#include "listes_chaines.h"

Contour simplification_douglas_peucker (Contour C,int j1,int j2,float d);

sequence_contours simplification_contours(sequence_contours SC,float d);

#endif