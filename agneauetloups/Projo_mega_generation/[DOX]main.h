#ifndef MAINH
#define MAINH

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

#include "[DOX]constants.h"
#include "[DOX]structures.h"
#include "[DOX]prototypes.h"

/** \file main.h
*  \brief Bibliothèque principale
*
* Bibliothèque principale
*/

/** \file main.c
*  \brief Fichier principal
*
* Fichier principal
*/

/** \file structures.h
*  \brief Contient les structures
*
* Contient toutes les structures du projet
*/

/** \file prototypes.h
*  \brief Contient les prototypes
*
* Contient tout les prototypes du projet
*/

/** \file constants.h
*  \brief Contient les constantes
*
* Contient toutes les constantes du projet
*/

/** \file OS.c
*  \brief Contient la gestion multiplateforme
*
* S'occupe de gérer les différence entre plateformes
*/

/** \file init.c
*  \brief Contient les initialisations
*
* S'occupe de créer et remplir les données de jeu
*/

/** \file GDK.c
*  \brief Contient les gestions d'image
*
* S'occupe de travailler les pixbufs
*/

/** \file game.c
*  \brief Contient la gestion du jeu
*
* S'occupe de gérer les clicks, les changements de tours, les appels d'IA...
*/

/** \file IA.c
*  \brief Contient l'IA
*
* S'occupe de définir les déplacements de l'IA
*/

/** \file IA_utilities.c
*  \brief Contient les outils de l'IA
*
* S'occupe de sous-traiter des fonctions de l'IA
*/

/** \file history.c
*  \brief Contient les outils de gestion d'historique
*
* Contient les fonctions pour crééer et remettre en place l'historique
*/

/** \file tests.c
*  \brief Contient les fonctions de tests
*
* Contient les fonctions non présentes/utiles en version finale
*/

#endif
