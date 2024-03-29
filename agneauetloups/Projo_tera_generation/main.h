#ifndef MAINH
#define MAINH

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <gdk/gdkkeysyms.h>

#include "constants.h"
#include "structures.h"
#include "prototypes.h"

/** \file main.h
*  \brief Biblioth�ue principale
*
* Biblioth�ue principale
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
* S'occupe de g�er les diff�ence entre plateformes
*/

/** \file init.c
*  \brief Contient les initialisations
*
* S'occupe de cr�r et remplir les donn�s de jeu
*/

/** \file GDK.c
*  \brief Contient les gestions d'image
*
* S'occupe de travailler les pixbufs
*/

/** \file game.c
*  \brief Contient la gestion du jeu
*
* S'occupe de g�er les clicks, les changements de tours, les appels d'IA...
*/

/** \file IA.c
*  \brief Contient l'IA
*
* S'occupe de d�inir les d�lacements de l'IA
*/

/** \file IA_utilities.c
*  \brief Contient les outils de l'IA
*
* S'occupe de sous-traiter des fonctions de l'IA
*/

/** \file history.c
*  \brief Contient les outils de gestion d'historique
*
* Contient les fonctions pour cr�r et remettre en place l'historique
*/

/** \file menu.c
*  \brief Contient les fonctions associ�s aux boutons du menu
*
* Contient les fonctions associ�s aux boutons du menu (onabout, onquit ...)
*/

/** \file tests.c
*  \brief Contient les fonctions de tests
*
* Contient les fonctions non pr�entes/utiles en version finale
*/

#endif
