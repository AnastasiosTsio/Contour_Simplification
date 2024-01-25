#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = TEST_TACHE6


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c


%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules

image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

listes_chaines.o :listes_chaines.c listes_chaines.h geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module listes_chaines"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contours.o:contours.c contours.h listes_chaines.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contours"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

ecrire_eps.o:ecrire_eps.c ecrire_eps.h contours.h listes_chaines.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module ecrire_eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification.o:simplification.c simplification.h contours.h listes_chaines.h geom2d.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

geom2d.o : geom2d.c geom2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

TEST_TACHE6.o : TEST_TACHE6.c geom2d.h simplification.h contours.h image.h ecrire_eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module TEST_TACHE6"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
		
########################################################
# regles explicites de creation des executables

TEST_TACHE6 : TEST_TACHE6.o geom2d.o simplification.o contours.o image.o listes_chaines.o ecrire_eps.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
